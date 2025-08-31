#include <bits/stdc++.h>
using namespace std;

bool IsDebug = false;
const string kEnter = "\n";
const string kSpace = " ";


class TextEditor {
private:
    // 文件本身
    vector<string> mLines;
    // 粘贴板
    vector<string> mPasteBin;
    // 选中内容暂存，处理选区时使用
    vector<string> mSelBin;

    // 光标位置结构体，行和列从1开始计数
    struct Position {
        int row = 1, col = 1;
        // 位置比较运算符，用于选区处理
        bool operator<(const Position& other) const {
            if (row == other.row) return col < other.col;
            return row < other.row;
        }
        // 位置相等判断
        bool operator==(const Position& other) const {
            return row == other.row && col == other.col;
        }
        // 构造函数
        Position(int r = 1, int c = 1) : row(r), col(c) {}
    };

    Position mCursor;          // 当前光标位置
    bool mShiftPressed = false; // Shift键是否按下（用于选择模式）
    bool mInSelection = false;  // 是否处于选区模式
    Position mSelectionStart;   // 选区起始位置
    Position mSelectionEnd;     // 选区结束位置

    // 获取行索引（从0开始），参数是Position结构体，返回row-1
    int getLineIndex(const Position& pos) const { return pos.row - 1; }
    // 获取字符索引（行内从0开始），col-2是因为显示列从1开始，实际字符串索引从0开始
    int getCharIndex(const Position& pos) const { return pos.col - 2; }
    // 获取行可见长度（不包含末尾换行符）
    int getLineVisibleLength(const Position& pos) const {
        auto& line = mLines[getLineIndex(pos)];
        // 如果行末是换行符，长度减一
        if (!line.empty() && line.back() == '\n')
            return line.length() - 1;
        else
            return line.length();
    }
    // 获取光标左侧子串，从行首到光标前一个位置
    string getLeftSubstring(const Position& pos) const {
        return mLines[getLineIndex(pos)].substr(0, pos.col - 1);
    }
    // 获取光标右侧子串，从光标位置到行末
    string getRightSubstring(const Position& pos) const {
        return mLines[getLineIndex(pos)].substr(pos.col - 1);
    }
    // 获取可见行内容（不包含换行符）
    string getVisibleLine(const Position& pos) const {
        int len = getLineVisibleLength(pos);
        return mLines[getLineIndex(pos)].substr(0, len);
    }

    // 移动光标函数，type参数表示移动方向
    void moveCursor(int moveType) {
        mInSelection = false; // 移动光标时退出选区模式
        bool adjustCol = false; // 是否需要调整列位置

        switch (moveType) {
            case 1:  // 移动到行首
                mCursor.col = 1;
                break;
            case 2:  // 移动到行尾
                mCursor.col = getLineVisibleLength(mCursor) + 1;
                break;
            case 3: { // 上一行
                if (mCursor.row == 1) return; // 已经是第一行，不能再上移
                Position prevPos(mCursor.row - 1, mCursor.col);
                // 如果上一行的可见长度小于当前列数-1，需要调整列到行尾
                if (getLineVisibleLength(prevPos) < mCursor.col - 1)
                    adjustCol = true;
                --mCursor.row;
                if (adjustCol) moveCursor(2); // 调整到行尾
                break;
            }
            case 4: { // 下一行
                if (mCursor.row == static_cast<int>(mLines.size())) return; // 已经是最后一行
                Position nextPos(mCursor.row + 1, mCursor.col);
                // 如果下一行可见长度小于当前列数-1，调整到行首
                if (getLineVisibleLength(nextPos) < mCursor.col - 1)
                    adjustCol = true;
                ++mCursor.row;
                if (adjustCol) moveCursor(1); // 调整到行首
                break;
            }
            case 5: // 左移一个字符
                if (mCursor.row == 1 && mCursor.col == 1) return; // 已经在最左上角
                if (mCursor.col == 1) { // 当前在行首，移动到上一行行尾
                    moveCursor(3);
                    moveCursor(2);
                } else {
                    --mCursor.col; // 直接左移
                }
                break;
            case 6: // 右移一个字符
                int lineCount = static_cast<int>(mLines.size());
                if (mCursor.row == lineCount &&
                    mCursor.col == getLineVisibleLength(mCursor) + 1)
                    return; // 已经在最后一行行尾
                if (mCursor.col == getLineVisibleLength(mCursor) + 1) { // 当前在行尾，移动到下一行行首
                    moveCursor(4);
                    moveCursor(1);
                } else {
                    ++mCursor.col; // 直接右移
                }
                break;
        }
        // cout << "Move Cursor to: (" << mCursor.row << ", " << mCursor.col << ")" << endl;
    }

    // 创建新行并插入内容，在当前行之后插入新行
    void createNewLine(const string& content) {
        int idx = getLineIndex(mCursor); // 当前行索引
        auto it = mLines.begin() + idx;
        mLines.insert(it + 1, content); // 插入到当前行之后
        moveCursor(4); // 移动到新行
        moveCursor(2); // 移动到新行行尾
        // cout << "New line created, lines count: " << mLines.size() << endl;
    }

    // 复制
    void copyToBuffer(vector<string>& buffer) {
        buffer.clear(); // 先清空缓冲区
        if (mInSelection) { // 处理选区复制
            // 选区在同一行
            if (mSelectionStart.row == mSelectionEnd.row) {
                int left = getCharIndex(mSelectionStart) + 1; // 起始字符索引+1（包含起始字符）
                int right = getCharIndex(mSelectionEnd); // 结束字符索引（包含结束字符）
                if (left >= 0 && right >= 0) {
                    // 从结束行中截取选中部分
                    buffer.push_back(mLines[getLineIndex(mSelectionEnd)].substr(left, right - left + 1));
                }
            } else {
                int startLine = getLineIndex(mSelectionStart); // 起始行索引
                int endLine = getLineIndex(mSelectionEnd); // 结束行索引
                int startChar = getCharIndex(mSelectionStart) + 1; // 起始行的起始字符索引+1

                // 处理起始行的选中部分
                if (startChar >= 0)
                    buffer.push_back(mLines[startLine].substr(startChar));
                else
                    buffer.push_back(mLines[startLine]); //表示从行首开始

                // 处理中间行（如果有的话）
                for (int i = startLine + 1; i < endLine; ++i)
                    buffer.push_back(mLines[i]);

                // 处理结束行的选中部分
                int endChar = getCharIndex(mSelectionEnd); // 结束行的结束字符索引
                if (endChar >= 0)
                    buffer.push_back(mLines[endLine].substr(0, endChar + 1)); // 包含结束字符
            }
        } else { // 非选区复制：复制当前行可见内容
            if (getLineVisibleLength(mCursor) != 0)
                buffer.push_back(getVisibleLine(mCursor));
        }
        // cout << "Copied to buffer: ";
        // for (auto& line : buffer) cout << line << "|";
        // cout << endl;
    }

    // 删除内容函数，type=1删除右侧（Del），type=2删除左侧（Backspace）
    void removeContent(int removeType) {
        if (mInSelection) { // 处理选区删除
            copyToBuffer(mSelBin); // 先复制选区内容（可能用于撤销，但此处未实现）
            Position start = mSelectionStart;
            Position end = mSelectionEnd;

            // 合并选区前后内容
            string leftPart = getLeftSubstring(start); // 选区前的内容
            string rightPart = getRightSubstring(end); // 选区后的内容
            mLines[getLineIndex(start)] = leftPart + rightPart; // 合并到起始行

            // 删除中间的行（如果有）
            int firstDelLine = getLineIndex(start) + 1;
            int lastDelLine = getLineIndex(end);
            if (firstDelLine <= lastDelLine) {
                mLines.erase(mLines.begin() + firstDelLine, mLines.begin() + lastDelLine + 1);
                // 如果删除后光标位置超出行数，调整到最后一行行尾
                if (end.row > static_cast<int>(mLines.size())) {
                    moveCursor(3);
                    moveCursor(2);
                }
            }
            mInSelection = false; // 退出选区模式
            return;
        }

        switch (removeType) {
            case 1: { // Del键，删除光标右侧字符
                int lineIdx = getLineIndex(mCursor);
                int charIdx = getCharIndex(mCursor);
                int lineCount = static_cast<int>(mLines.size());
                // 如果在最后一行最后一个可见字符，且没有下一行，无法删除
                if (lineIdx == lineCount - 1 &&
                    charIdx == getLineVisibleLength(mCursor) - 1)
                    return;

                if (charIdx == getLineVisibleLength(mCursor) - 1) { // 行尾，合并下一行
                    mLines[lineIdx] += mLines[lineIdx + 1]; // 合并下一行内容
                    mLines.erase(mLines.begin() + lineIdx + 1); // 删除下一行
                } else { // 删除当前字符
                    string left = getLeftSubstring(mCursor);
                    string right = getRightSubstring(mCursor).substr(1); // 去掉第一个字符（当前字符）
                    mLines[lineIdx] = left + right;
                }
                break;
            }
            case 2: { // Backspace键，删除光标左侧字符
                int charIdx = getCharIndex(mCursor);
                if (charIdx == -1 && mCursor.row == 1) return; // 在第一行行首，无法删除

                if (charIdx == -1) { // 行首，合并上一行
                    moveCursor(3); // 移动到上一行
                    moveCursor(2); // 移动到上一行行尾
                    int prevLineIdx = getLineIndex(mCursor);
                    mLines[prevLineIdx] += mLines[prevLineIdx + 1]; // 合并当前行内容
                    mLines.erase(mLines.begin() + prevLineIdx + 1); // 删除当前行
                } else { // 删除左侧字符
                    string left = getLeftSubstring(mCursor).substr(0, charIdx); // 左侧字符去掉最后一个
                    string right = getRightSubstring(mCursor);
                    mLines[getLineIndex(mCursor)] = left + right;
                    --mCursor.col; // 光标左移
                }
                break;
            }
        }
        // cout << "After remove, line " << mCursor.row << ": " << mLines[getLineIndex(mCursor)] << endl;
    }

    // 查找指定字符串在选区内或全文中的出现次数
    int findOccurrences(const string& target) const {
        vector<string> scope = mInSelection ? mSelBin : mLines; // 确定查找范围
        int count = 0;
        for (const auto& line : scope) {
            size_t pos = 0;
            // 循环查找所有出现位置
            while ((pos = line.find(target, pos)) != string::npos) {
                ++count;
                pos += target.length(); // 从下一个位置继续查找
            }
        }
        return count;
    }

    // 切换选择模式，处理Shift键按下和释放
    void toggleSelection() {
        if (mShiftPressed) { // Shift键释放，结束选区
            mShiftPressed = false;
            if (mSelectionStart == mCursor) return; // 起点和光标相同，无选区

            // 确定选区的起点和终点（保证起点在前）
            if (mSelectionStart < mCursor) {
                mSelectionEnd = mCursor;
            } else {
                mSelectionStart = mCursor;
                mSelectionEnd = mSelectionStart; // 这里可能有问题？应该交换起点终点？
            }
            mInSelection = true;
        } else { // Shift键按下，记录选区起点
            mShiftPressed = true;
            mSelectionStart = mCursor;
            mInSelection = false;
        }
        // cout << "Selection mode: " << (mInSelection ? "active" : "inactive") << endl;
    }

public:
    // 构造函数，初始化空行和光标位置
    TextEditor() {
        mLines.emplace_back(""); // 初始空行
        mCursor = Position(1, 1); // 光标在第一行第一列
        // cout << "TextEditor initialized, lines count: " << mLines.size() << endl;
    }

    // 处理操作指令，根据命令字符执行相应操作
    void processCommand(const string& cmd, const string& arg = "") {
        switch (cmd[0]) {
            case 'M': {
                char dir = arg[0];
                switch (dir) {
                    case 'H': moveCursor(1); break; // 行首
                    case 'E': moveCursor(2); break; // 行尾
                    case 'U': moveCursor(3); break; // 上箭头
                    case 'D': moveCursor(4); break; // 下箭头
                    case 'L': moveCursor(5); break; // 左箭头
                    case 'R': moveCursor(6); break; // 右箭头
                }
                break;
            }
            case 'I': { // 插入操作，参数为插入类型（C/E/S/P）
                char type = arg[0];
                string insertStr;
                if (type == 'C') { // 插入字符，参数格式为ICxxx
                    if (arg.length() < 2) return; // 参数格式错误
                    insertStr = arg.substr(2); // 提取插入的字符串
                }

                switch (type) {
                    case 'C': { // 插入字符到光标位置
                        string left = getLeftSubstring(mCursor);
                        string right = getRightSubstring(mCursor);
                        int lineIdx = getLineIndex(mCursor);
                        mLines[lineIdx] = left + insertStr + right; // 合并字符串
                        mCursor.col += insertStr.length(); // 光标后移插入长度
                        break;
                    }
                    case 'E': createNewLine(kEnter); break; // 插入换行，创建新行
                    case 'S': { // 插入空格
                        mLines[getLineIndex(mCursor)] = getLeftSubstring(mCursor) + kSpace + getRightSubstring(mCursor);
                        ++mCursor.col; // 光标右移一位
                        break;
                    }
                    case 'P': { // 粘贴操作，从粘贴板插入内容
                        if (mPasteBin.empty()) return; // 粘贴板为空，无法粘贴
                        string right = getRightSubstring(mCursor);
                        int lineIdx = getLineIndex(mCursor);

                        if (mPasteBin.size() == 1 && mPasteBin[0].back() != '\n') {
                            // 单一行且无换行符，直接插入到当前行
                            mLines[lineIdx] = getLeftSubstring(mCursor) + mPasteBin[0] + right;
                            mCursor.col += mPasteBin[0].length(); // 调整光标位置
                        } else {
                            // 多行粘贴，需要创建新行
                            mLines[lineIdx] = getLeftSubstring(mCursor) + mPasteBin[0]; // 第一行内容
                            for (int i = 1; i < static_cast<int>(mPasteBin.size() - 1); ++i) {
                                createNewLine(mPasteBin[i]); // 中间行逐行创建
                            }
                            // 处理最后一行
                            if (mPasteBin.back().back() != '\n') {
                                createNewLine(mPasteBin.back() + right); // 最后一行无换行符，与原右侧内容合并
                                mCursor.col = mPasteBin.back().length() + 1; // 光标位置调整
                            } else {
                                createNewLine(mPasteBin.back()); // 最后一行有换行符
                                createNewLine(right); // 原右侧内容放到新行
                                moveCursor(1); // 光标移动到新行首
                            }
                        }
                        break;
                    }
                }
                break;
            }
            case 'R': { // 删除操作，参数为删除类型（Del/Backspace）
                string delType = arg;
                if (delType == "Del") removeContent(1); // 删除右侧字符
                else if (delType == "Backspace") removeContent(2); // 删除左侧字符
                break;
            }
            case 'S': toggleSelection(); break; // 切换选择模式（Shift键）
            case 'F': { // 查找操作，参数为要查找的字符串
                int cnt = findOccurrences(arg);
                cout << cnt << endl; // 输出查找到的次数
                break;
            }
            case 'C': { // 复制或统计操作
                if (cmd[2] == 'P') copyToBuffer(mPasteBin); // 复制选区到粘贴板
                else if (cmd[2] == 'U') { // 统计非空白字符数
                    int cnt = 0;
                    auto scope = mInSelection ? mSelBin : mLines; // 统计范围取决于是否有选区
                    for (const auto& line : scope)
                        for (char c : line)
                            if (c != ' ' && c != '\n') cnt++; // 只统计非空格和非换行符
                    cout << cnt << endl; // 输出统计结果
                }
                break;
            }
            case 'P': { // 打印全部内容
                for (const auto& line : mLines)
                    if (!line.empty()) cout << line; // 输出每一行
                cout << endl; // 最后换行
                break;
            }
        }
        // cout << "After command: " << cmd << " " << arg << endl;
        // cout << "Cursor at: (" << mCursor.row << ", " << mCursor.col << ")" << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int opCount;
    cin >> opCount;

    TextEditor editor;
    string cmd, arg;

    for (int i = 0; i < opCount; ++i) {
        cin >> cmd;
        // 处理带参数的命令
        if (cmd.size() > 1) arg = cmd.substr(1);
        else cin >> arg; // 如果命令本身不带参数，从输入读取参数

        // cout << "Processing command: " << cmd << " " << arg << endl;

        editor.processCommand(cmd, arg);
    }
    return 0;
}