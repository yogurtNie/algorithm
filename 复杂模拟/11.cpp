#include <bits/stdc++.h>
using namespace std;

const string EMPTY_STR = "null";
const string NEWLINE = "\n";
const string SPACE_CHAR = " ";

// 文本位置结构体
struct TextPosition {
    int row = 1;
    int col = 1;

    TextPosition(int r = 1, int c = 1) : row(r), col(c) {}

    bool operator<(const TextPosition& other) const {
        if (row == other.row) return col < other.col;
        return row < other.row;
    }

    bool operator==(const TextPosition& other) const {
        return row == other.row && col == other.col;
    }
};

// 全局状态
vector<string> documentLines;       // 文档内容
vector<string> clipboard;           // 剪贴板内容
vector<string> selectionBuffer;     // 选中内容缓冲区
TextPosition cursorPosition;        // 光标位置
bool shiftActive = false;           // Shift键状态
bool inSelectionMode = false;       // 选择模式状态
TextPosition selectionAnchor;       // 选择起始点
TextPosition selectionRange[2];     // 选择范围

// 辅助函数：获取行索引(0-based)
int getLineIndex(const TextPosition& pos) { return pos.row - 1; }

// 辅助函数：获取字符索引(0-based)
int getCharIndex(const TextPosition& pos) { return pos.col - 2; }

// 获取行的完整长度
int getLineFullLength(const TextPosition& pos) {
    return documentLines[getLineIndex(pos)].length();
}

// 获取行的可见长度(不含末尾换行符)
int getLineVisibleLength(const TextPosition& pos) {
    if (documentLines[getLineIndex(pos)].back() == '\n')
        return documentLines[getLineIndex(pos)].length() - 1;
    return getLineFullLength(pos);
}

// 获取光标左侧子串
string getLeftSubstr(const TextPosition& pos) {
    return documentLines[getLineIndex(pos)].substr(0, pos.col - 1);
}

// 获取光标右侧子串
string getRightSubstr(const TextPosition& pos) {
    return documentLines[getLineIndex(pos)].substr(pos.col - 1);
}

// 获取可见行内容
string getVisibleLine(const TextPosition& pos) {
    return documentLines[getLineIndex(pos)].substr(0, getLineVisibleLength(pos));
}

// 复制选中内容到指定缓冲区
void copySelectionToBuffer(vector<string>& buffer);

// 获取选中区域内容
vector<string> getSelectedArea() {
    if (inSelectionMode) {
        copySelectionToBuffer(selectionBuffer);
        return selectionBuffer;
    }
    return documentLines;
}

// === 光标操作函数 ===
void moveCursorHome() { cursorPosition.col = 1; }
void moveCursorEnd()
{
    if (getLineIndex(cursorPosition) >= documentLines.size()) {
        cursorPosition.col = 1;
        return;
    }
    cursorPosition.col = getLineVisibleLength(cursorPosition) + 1;
}

void moveCursorUp() {
    if (cursorPosition.row == 1) return;
    const int targetRow = cursorPosition.row - 1;
    const int maxCol = getLineVisibleLength(TextPosition(targetRow, cursorPosition.col)) + 1;
    cursorPosition.col = min(cursorPosition.col, maxCol);
    cursorPosition.row = targetRow;
}

void moveCursorDown() {
    if (cursorPosition.row == documentLines.size()) return;
    const int targetRow = cursorPosition.row + 1;
    const int maxCol = getLineVisibleLength(TextPosition(targetRow, cursorPosition.col)) + 1;
    cursorPosition.col = min(cursorPosition.col, maxCol);
    cursorPosition.row = targetRow;
}

void moveCursorLeft() {
    if (cursorPosition.row == 1 && cursorPosition.col == 1) return;
    if (cursorPosition.col == 1) {
        moveCursorUp();
        moveCursorEnd();
    } else {
        cursorPosition.col--;
    }
}

void moveCursorRight() {
    const int maxCol = getLineVisibleLength(cursorPosition) + 1;
    if (cursorPosition.row == documentLines.size() && cursorPosition.col == maxCol) return;
    if (cursorPosition.col == maxCol) {
        moveCursorDown();
        moveCursorHome();
    } else {
        cursorPosition.col++;
    }
}

// 统一的光标移动接口
void moveCursor(int direction) {
    inSelectionMode = false;
    switch (direction) {
        case 1: moveCursorHome(); break;
        case 2: moveCursorEnd(); break;
        case 3: moveCursorUp(); break;
        case 4: moveCursorDown(); break;
        case 5: moveCursorLeft(); break;
        case 6: moveCursorRight(); break;
    }
}

void insertText(int type, const string& text = "");
void createNewLine(const string& content);

// 复制实现
void copySelectionToBuffer(vector<string>& buffer) {
    buffer.clear();
    if (inSelectionMode) {
        const TextPosition& start = selectionRange[0];
        const TextPosition& end = selectionRange[1];

        if (start.row == end.row) {
            const int left = getCharIndex(start) + 1;
            const int right = getCharIndex(end);
            if (left >= 0 && right >= 0)
                buffer.push_back(documentLines[getLineIndex(start)].substr(left, right - left + 1));
        } else {
            const int upChar = getCharIndex(start) + 1;
            const int upLine = getLineIndex(start);
            const int dnChar = getCharIndex(end);
            const int dnLine = getLineIndex(end);

            if (upChar >= 0)
                buffer.push_back(documentLines[upLine].substr(upChar));
            else
                buffer.push_back(documentLines[upLine]);

            for (int i = upLine + 1; i < dnLine; i++)
                buffer.push_back(documentLines[i]);

            if (dnChar >= 0)
                buffer.push_back(documentLines[dnLine].substr(0, dnChar + 1));
        }
    } else if (getLineVisibleLength(cursorPosition) != 0) {
        buffer.clear();
        buffer.push_back(getVisibleLine(cursorPosition));
    }
}

// 删除内容
void removeContent(int type);

// 插入实现
void insertText(int type, const string& text) {
    if (inSelectionMode) {
        if (type == 4 && clipboard.empty()) return;  // 粘贴且剪贴板为空
        if (selectionRange[1] == selectionRange[0]) {
            cursorPosition = selectionRange[1];
            inSelectionMode = false;
            insertText(type, text);
            return;
        }
        removeContent(1);  // 删除选中内容
        insertText(type, text);
        inSelectionMode = false;
        return;
    }

    string left, right;
    switch (type) {
        case 1:  // 插入字符
            documentLines[getLineIndex(cursorPosition)] = getLeftSubstr(cursorPosition) + text + getRightSubstr(cursorPosition);
            cursorPosition.col += text.length();
            break;

        case 2:  // 插入换行
            right = getRightSubstr(cursorPosition);
            documentLines[getLineIndex(cursorPosition)] = getLeftSubstr(cursorPosition) + NEWLINE;
            createNewLine(right);
            break;

        case 3:  // 插入空格
            documentLines[getLineIndex(cursorPosition)] = getLeftSubstr(cursorPosition) + SPACE_CHAR + getRightSubstr(cursorPosition);
            cursorPosition.col++;
            break;

        case 4:  // 粘贴
            if (clipboard.empty()) return;
            right = getRightSubstr(cursorPosition);

            if (clipboard.size() == 1 && clipboard[0].back() != '\n') {
                documentLines[getLineIndex(cursorPosition)] = getLeftSubstr(cursorPosition) + clipboard[0] + right;
                for (int i = 0; i < clipboard[0].size(); i++)
                    moveCursorRight();
            } else {
                int currentLine = 0;
                documentLines[getLineIndex(cursorPosition)] = getLeftSubstr(cursorPosition) + clipboard[currentLine++];

                for (int i = 1; i < clipboard.size() - 1; i++)
                    createNewLine(clipboard[currentLine++]);

                if (clipboard.back().back() != '\n') {
                    if (currentLine < clipboard.size())
                        createNewLine(clipboard.back() + right);
                    moveCursorHome();
                    for (int i = 0; i < clipboard.back().size(); i++)
                        moveCursorRight();
                } else {
                    if (currentLine < clipboard.size())
                        createNewLine(clipboard.back());
                    createNewLine(right);
                    moveCursorHome();
                }
            }
            break;
    }
}

// 创建新行并插入内容
void createNewLine(const string& content) {
    auto it = documentLines.begin() + getLineIndex(cursorPosition);
    documentLines.insert(++it, content);
    moveCursor(4);  // 下移一行
    moveCursor(1);  // 移动到行首
}

// 删除
void removeContent(int type) {
    if (inSelectionMode) {
        copySelectionToBuffer(selectionBuffer);
        string left = getLeftSubstr(selectionRange[0]);
        string right = getRightSubstr(selectionRange[1]);
        cursorPosition = selectionRange[0];

        documentLines[getLineIndex(selectionRange[0])] = left + right;
        int firstDel = getLineIndex(selectionRange[0]) + 1;

        for (int i = firstDel; i <= selectionRange[1].row - 1; ) {
            documentLines.erase(documentLines.begin() + i);
            selectionRange[1].row--;
        }

        inSelectionMode = false;
        if (cursorPosition.row > documentLines.size()) {
            moveCursorUp();
            moveCursorEnd();
        }
        return;
    }

    switch (type) {
        case 1:  // 删除(Del)
            if (getLineIndex(cursorPosition) >= documentLines.size()) return;
            if (getLineIndex(cursorPosition) + 1 == documentLines.size() &&
                getCharIndex(cursorPosition) == getLineVisibleLength(cursorPosition) - 1)
                return;

            if (getCharIndex(cursorPosition) == getLineVisibleLength(cursorPosition) - 1) {
                documentLines[getLineIndex(cursorPosition)] = getVisibleLine(cursorPosition) + documentLines[getLineIndex(cursorPosition) + 1];
                documentLines.erase(documentLines.begin() + getLineIndex(cursorPosition) + 1);
            } else {
                documentLines[getLineIndex(cursorPosition)] = getLeftSubstr(cursorPosition) + getRightSubstr(cursorPosition).substr(1);
            }
            break;

        case 2:  // 退格(Backspace)
            if (getCharIndex(cursorPosition) == -1 && getLineIndex(cursorPosition) == 0)
                return;

            if (getCharIndex(cursorPosition) == -1) {
                TextPosition backup = cursorPosition;
                moveCursorUp();
                moveCursorEnd();
                documentLines[getLineIndex(backup) - 1] = getVisibleLine(backup) + documentLines[getLineIndex(backup)];
                documentLines.erase(documentLines.begin() + getLineIndex(backup));
            } else {
                documentLines[getLineIndex(cursorPosition)] = getLeftSubstr(cursorPosition).substr(0, getCharIndex(cursorPosition)) + getRightSubstr(cursorPosition);
                cursorPosition.col--;
            }
            break;
    }
    if (documentLines.empty()) {
        documentLines.push_back("");
        cursorPosition = {1, 1};
    }
}

void handleShiftKey();

// Shift键处理
void handleShiftKey() {
    shiftActive = !shiftActive;
    if (shiftActive) {
        if (inSelectionMode) {
            inSelectionMode = false;
            return;
        }
        selectionAnchor = cursorPosition;
    } else {
        if (selectionAnchor == cursorPosition) return;
        if (selectionAnchor < cursorPosition) {
            selectionRange[0] = selectionAnchor;
            selectionRange[1] = cursorPosition;
        } else {
            selectionRange[0] = cursorPosition;
            selectionRange[1] = selectionAnchor;
        }
        inSelectionMode = true;
    }
}

int countOccurrences(const string& word);
int countNonSpaceCharacters();
void printDocument();

// 查找功能
int countOccurrences(const string& word) {
    vector<string> area = getSelectedArea();
    int count = 0;

    for (const string& line : area) {
        size_t pos = 0;
        while ((pos = line.find(word, pos)) != string::npos) {
            count++;
            pos++;
        }
    }
    return count;
}

// 统计非空格字符数
int countNonSpaceCharacters() {
    vector<string> area = getSelectedArea();
    int count = 0;

    for (const string& line : area)
        for (char c : line)
            if (c != ' ' && c != '\n')
                count++;

    return count;
}

// 打印文档
void printDocument() {
    for (const string& line : documentLines)
        if (!line.empty())
            cout << line;
    cout << endl;
}

// 主函数
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int opCount;
    cin >> opCount;
    documentLines.emplace_back("");

    string op, arg;
    for (int i = 1; i <= opCount; i++) {
        cin >> op;
        switch(op[0]) {
            case 'M': { // 移动操作
                cin >> arg;
                switch(arg[0]) {
                    case 'H': moveCursor(1); break;  // Home
                    case 'E': moveCursor(2); break;  // End
                    case 'U': moveCursor(3); break;  // Up
                    case 'D': moveCursor(4); break;  // Down
                    case 'L': moveCursor(5); break;  // Left
                    case 'R': moveCursor(6); break;  // Right
                }
                break;
            }

            case 'I': { // 插入操作
                cin >> arg;
                switch(arg[0]) {
                    case 'C': { // 插入字符
                        string insertStr;
                        cin >> insertStr;
                        insertText(1, insertStr);
                        break;
                    }
                    case 'E': insertText(2); break;  // 插入换行
                    case 'S': insertText(3); break;  // 插入空格
                    case 'P': insertText(4); break;  // 粘贴
                }
                break;
            }

            case 'R': { // 删除操作
                cin >> arg;
                if (arg == "Del") removeContent(1);
                else if (arg == "Backspace") removeContent(2);
                break;
            }

            case 'S': handleShiftKey(); break;  // Shift键

            case 'F': { // 查找
                cin >> arg;
                cout << countOccurrences(arg) << endl;
                break;
            }

            case 'C': { // 复制/统计
                if (op[2] == 'P') copySelectionToBuffer(clipboard);  // 复制
                else if (op[2] == 'U') cout << countNonSpaceCharacters() << endl;  // 统计
                break;
            }

            case 'P': printDocument(); break;  // 打印
        }
    }
    return 0;
}