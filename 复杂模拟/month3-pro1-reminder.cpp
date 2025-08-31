//
// Created by 12472 on 25-5-20.
//
// 复杂模拟:记事本
// 数据结构：数组，但不能是线性数组，因为无法确定最大会有多大（5000的数量级）
// 或许可以用vector<string> / reminder[N][N]
// 操作1: 光标移动
// Home: pos.col = 1
// End: pos.col = v[pos.row].size() + 1
// Up: if (pos.row != 1) pos.col = (pos.col > v[pos.row - 1].size() + 1 ? v[pos.row - 1].size() + 1 : pos.col)
// pos.row = (pos.row == 1 ? 1 : pos.row - 1);
// Down:
#include<bits/stdc++.h>
using namespace std;
const int N = 5010;
vector<string> v;                           // 记事本
vector<string> Paste;                       // 粘贴板
vector<string> selectBin;                    // 选中内容
bool IsSelected = false;                    // 是否选中
bool IsShifted = false;                     // 是否粘滞
bool IsDebug = false;



int pcnt = 0;
struct position         // 光标
{
    int row, col;
    position(int r = 1, int c = 1) : row(r), col(c) {}
    position& operator = (const position& p)
    {
        row = p.row; col = p.col;
        return *this;
    }
    bool operator == (const position& p) const
    {
        return row == p.row && col == p.col;
    }
    bool operator != (const position& p) const
    {
        return row != p.row || col != p.col;
    }
    bool operator < (const position& p) const
    {
        if (row == p.row) return col < p.col;
        return row < p.row;
    }
}pos;

position Left, Right;
position selected[2];
int LineLen(position p)
{
    if (v[p.row].back() == '\n') return v[p.row].size() - 1;
    return v[p.row].size();
}

string getLeftStr(position p)
{
    if (p.col == 1) return "";
    //string s = v[p.row].substr(0, max(0, p.col - 2) + 1);
    return v[p.row].substr(0, max(0, p.col - 2) + 1);
}

string getRightStr(position p)
{
    int size = v[p.row].size();
    if (size == 0 || p.col - 1 >= size) return "";
    if (p.col == 1) return v[p.row];
    return v[p.row].substr(p.col - 1);
}
// 光标移动功能
void Move(int type);
void theMove()
{
    string choice; cin >> choice;
    switch (choice[0])
    {
    case 'H': Move(1);break;
    case 'E':Move(2);break;
    case 'U':Move(3);break;
    case 'D':Move(4);break;
    case 'L':Move(5);break;
    case 'R':Move(6);break;
    }
}
void Move(int type)
{
    if (IsSelected) IsSelected = false;
    //string choice; cin >> choice;
    switch (type)
    {
    case 1:                               // 光标移到当前行的开头
        {
            pos.col = 1;
            break;
        }
    case 2:                               // 光标移到当前行的末尾
        {
            if (v[pos.row].back() == '\n') pos.col = v[pos.row].size();
            else pos.col = v[pos.row].size() + 1;
            break;
        }
    case 3:                               // 光标移动到上一行的相同列
        {
            if (pos.row == 1) break;
            bool IsSmaller = false;
            if (pos.col - 1 > LineLen(position(pos.row - 1, pos.col))) IsSmaller = true;
            pos.row = pos.row - 1;
            if (IsSmaller) Move(2);
            break;
        }
    case 4:
        {
            if (pos.row == v.size() - 1) break;
            // 当前行的长度比下一行的长
            bool IsSmaller = false;
            if (pos.col - 1 > LineLen(position(pos.row + 1, pos.col))) IsSmaller = true;
            pos.row = pos.row + 1;
            if (IsSmaller) Move(2);
            break;
        }
    case 5:
        {
            if (pos.col == 1 && pos.row == 1) break;
            if (pos.col == 1)
            {
                Move(3);
                Move(2);
            }
            else pos.col--;
            break;
        }
    case 6:
        {
            if (pos.row == v.size() - 1 && pos.col == v[pos.row].size() + 1) break;
            if (pos.col - 1 == LineLen(pos))
            {
                Move(4);
                Move(1);
            }
            else pos.col++;
            break;
        }

    }
    if (IsDebug) cout << "(" << pos.row << ", "  << pos.col << ")" << endl;
}

// 输入功能
// void insertStr()
// {
//     string str; cin >> str;
//     Insert(str, )
// }
void Remove(int type);
void print();
void insertLine(string s)
{
    v.insert(v.begin() + pos.row + 1, s);  // 在pos之后的那一行插入
    Move(4);                                    // 更新光标到下一行
    Move(2);                                    // 更新光标到尾端
}
void Insert(int type, string str);
void theInsert()
{
    string choice; cin >> choice;
    switch (choice[0])
    {
    case 'C':
        {
            string str; cin >> str;
            Insert(1, str);
            break;
        }
    case 'E':
        {
            Insert(2,"\n");
            break;
        }
    case 'S':
        {
            Insert(3," ");
            break;
        }
    case 'P':
        {
            Insert(4,"");
            break;
        }

    }
}
void Insert(int type, string str)
{
    vector<string>::iterator vt;
    if (IsSelected)                         // 处于被选中状态的时候，先删掉
    {
        if (type == 4 && Paste.empty()) return;
        if (selected[0] == selected[1])
        {
            IsSelected = false;
            pos = selected[0];
            Insert(type, str);
            return;
        }
        Remove(1);
        Insert(type, str);
        IsSelected = false;
        return;
    }
    switch (type)
    {
    case 1:
        {
            // 先拿到要插入的地方右边的所有
            v[pos.row] = getLeftStr(pos) + str + getRightStr(pos);
            pos.col += str.size();
            break;
        }
    case 2:
        {
            string right = getRightStr(pos);
            v[pos.row] = getLeftStr(pos) + str;
            v.insert(v.begin() + pos.row + 1, right);
            Move(4);
            Move(1);
            break;
        }
    case 3:
        {
            v[pos.row] = getLeftStr(pos) + str + getRightStr(pos);
            pos.col++;
            break;
        }
    case 4:
        {
            if (Paste.empty()) break;                  // 若粘贴板无内容，则忽略
            string R = getRightStr(pos);
            int cnt = Paste.size() - 1;                 // 疑问：这个size函数的值到底是由什么决定的？
            if (cnt == 1 && Paste[1].back() != '\n')   // 若只有一行，直接插入
            {
                v[pos.row] = getLeftStr(pos) + Paste[1] + R;
                pos.col += Paste[1].size();
            }
            else
            {
                int curr = 0;
                v[pos.row] = getLeftStr(pos) + Paste[++curr];
                for (int i = 2; i < Paste.size() - 1; i++)
                    insertLine(Paste[++curr]);
                if (Paste[Paste.size() - 1].back() != '\n')
                {
                    if (curr <= Paste.size() - 1)
                        insertLine(Paste[Paste.size() - 1] + R);
                    Move(1);        // 更新到开头，因为要开始更新列索引了
                    for (int i = 0; i < Paste[Paste.size() - 1].size(); i++) Move(6);
                }
                else
                {
                    if (curr <= Paste.size() - 1)
                        insertLine(Paste[Paste.size() - 1]);
                    insertLine(R);
                    Move(1);            // 更新到开头，因为换行了
                }
                // if (Paste[cnt].back() == '\n')
                // {
                //     v.insert(v.begin() + pos.row + 1, R);
                //     pos.col = 1;
                // }
                //
                // else { pos.col = Paste[cnt].size() + 1; Paste[cnt] += R;}
                // for (int i = Paste.size() - 1; i > 1; i--)  // 依旧为了不干扰索引，倒着插
                // {
                //     v.insert(v.begin() + pos.row + 1, Paste[i]);
                // }
                // v[pos.row] = getLeftStr(pos) + Paste[1];
                // if (Paste[cnt].back() == '\n') pos.row += cnt;
                // else pos.row += cnt - 1;
            }
            break;
        }
    }
    if (IsDebug) print();
    if (IsDebug) cout << "(" << pos.row << ", "  << pos.col << ")" << endl;
}
void Copy(vector<string>& pb);
// 删除
void Remove(int type)
{
    vector<string>::iterator it;
    if (IsSelected)
    {
        Copy(selectBin);
        int sr = selected[0].row, er = selected[1].row;
        string L = getLeftStr(selected[0]);
        string R = getRightStr(selected[1]);
        pos = selected[0];
        v[pos.row] = L + R;
        for (int i = sr + 1; i <= er; i++)
        {
            it = v.begin();
            for (int j = 1; j <= i; j++) ++it;
            v.erase(it);
            er--;
        }
        IsSelected = false;
        if (pos.row > v.size() - 1)
        {
            Move(3); Move(2);
        }
        if (IsDebug) print();
        return;
    }
    switch (type)
    {
    case 1:
        {
            if (pos.row == v.size() - 1 && pos.col - 2 == v[pos.row].size() -1) return;
            if (pos.col - 2 == LineLen(pos) - 1)        // 如果在最尾端
            {
                v[pos.row] = getLeftStr(pos) + v[pos.row + 1];
                v.erase(v.begin() + pos.row + 1);
                return;
            }
            string L = getLeftStr(pos), R = getRightStr(position(pos.row, pos.col + 1));
            v[pos.row] = L + R;
            break;
            // int size = v[pos.row].size();
            // if (v[pos.row + 1].size() == 0 && pos.col == size + 1) break;    // 如果处于文件的最尾端，不动
            // if (v[pos.row][pos.col - 1] != '\n')
            //     v[pos.row].erase(pos.col - 1, 1);
            // else
            // {
            //     v[pos.row].erase(pos.col - 1);
            //     v[pos.row] += v[pos.row + 1];
            //     v.erase(v.begin() + pos.row + 1);
            // }
            // break;
        }
    case 2:               // 一个小问题：如果是在每一行的开头，是忽略这个操作，还是认为上一行的结尾是这一行的开头？
        {
            if (pos.row == 1 && pos.col == 1) return;
            if (pos.col == 1)
            {
                position tmp = pos;
                Move(3); Move(2);       // 移到上一行的尾端
                v[pos.row] = getLeftStr(pos) + v[tmp.row];
                v.erase(v.begin() + pos.row + 1);
                return;
            }
            v[pos.row] = getLeftStr(pos).substr(0, pos.col - 2) + getRightStr(pos);
            pos.col--;
            break;
            // if (pos.col == 1 && pos.row == 1) break;
            // if (pos.col == 1 && v[pos.row - 1].size() != 0)
            // {
            //     int size = v[pos.row - 1].size();
            //     v[pos.row - 1].pop_back();
            //     v[pos.row - 1] += v[pos.row];
            //     v.erase(v.begin() + pos.row);
            //     pos.row--;
            //     pos.col = size;
            //     break;
            // }
            // if (v[pos.row][pos.col - 2] != '\n')
            // {
            //     v[pos.row].erase(pos.col - 2, 1);
            //     pos.col--;
            // }
            // else
            // {
            //     v[pos.row].erase(pos.col - 2, 1);
            //     pos.col--;
            //     v[pos.row] += v[pos.row + 1];
            //     v.erase(v.begin() + pos.row + 1);
            // }
            // break;
        }
    }
    if (IsDebug) print();
    if (IsDebug) cout << "(" << pos.row << ", "  << pos.col << ")" << endl;
}

void theRemove()
{
    string order;
    cin >> order;
    switch (order[0])
    {
    case 'D':Remove(1);break;
    case 'B':Remove(2);break;
    }

}

void Shift()
{
    if (IsShifted)                      // 处于粘滞启动状态，将粘滞关闭，进入选中状态
    {
        if (Left != pos)
        {
            IsSelected = true;
            if (pos < Left)
            {
                selected[0] = pos;
                selected[1] = Left;
            }
            else
            {
                selected[0] = Left;
                selected[1] = pos;
            }
            if (IsDebug) cout << "SelectedArea: (" << selected[0].row << ", " << selected[0].col << ") ";
            if (IsDebug) cout << "(" << selected[1].row << ", " << selected[1].col << ")" << endl;
        }
        IsShifted = false;
    }
    else                                // 处于粘滞关闭状态，此时把粘滞打开，并记录当前光标位置
    {
        if (IsSelected)                 // 如果已经在选中状态中
        {
            IsSelected = false;         // 退出选中状态，记录点还保持为当前的
        }
        Left = pos;                 // 否则将pos对应的记录成记录点
        IsShifted = true;
    }

}

// 辅助函数
vector<string> getSelected()
{
    vector<string> res;
    if (IsSelected)
    {
        Copy(selectBin);
        res = selectBin;
    }
    else res = v;
    return res;
}

// 查找
void Find()
{
    string str; cin >> str;
    int ans = 0;
    vector<string> tmp = getSelected();
    for (auto& s : tmp)
    {
        int found = 0;
        while (found < s.length() && (found = s.find(str)) != string::npos)
        {
            ans++;
            s = s.substr(found + 1);
            found = 0;
        }
    }
    //cout << "Find " << str << " : ";
    cout << ans << endl;
}

// 字数统计
void Count()
{
    vector<string> tmp = getSelected();
    int ans = 0;
    for (auto& s : tmp)
        for (char c : s)
            if (c != ' ' && c != '\n') ans++;
    //cout << "Count: ";
    cout << ans << endl;
}

// 复制
void Copy(vector<string>& pb)
{
    if (IsSelected)         // 将选中内容移动到pb中
    {
        pb.clear();
        pb.push_back("");
        if (selected[0].row == selected[1].row)         // 在同一行
        {
            //pb.resize(2);
            int L = selected[0].col - 1;
            int R = selected[1].col - 2;
            if (L >= 0 && R >= 0)
            {
                pb.push_back(v[selected[0].row].substr(L, R - L + 1));
            }
            // int row = selected[0].row;
            // string tmp = v[row].substr(selected[0].col - 1, selected[1].col - 2 - (selected[0].col - 1) + 1);
            // pb.push_back(tmp);
        }
        else                                           // 不在同一行
        {
            int sr = selected[0].row, er = selected[1].row;
            int sc = selected[0].col - 1, ec = selected[1].col - 2;
            //pb.resize(er - sc + 2);
            for (int i = sr; i <= er; i++)
            {
                if (i == sr)                            // 第一行
                {
                    if (sc >= 0) pb.push_back(v[i].substr(sc));
                    else pb.push_back(v[i]);
                }
                else if (i == er)                       // 最后一行
                    pb.push_back(v[i].substr(0, ec + 1));
                else
                    pb.push_back(v[i]);

            }
        }
    }
    else
    {
        // 一定注意，是当本行有能复制的地方的时候才准复制，否则会把之前复制的给清空
        if (LineLen(pos) != 0)                     // 光标所在的行复制到这里边
        {
            pb.clear();
            //pb.resize(2);
            pb.push_back("");
            pb.push_back(v[pos.row]);
            if (pb[1].back() == '\n') pb[1].pop_back();
        }
    }
    if (IsDebug) for (auto& s : pb) cout << s;
    if (IsDebug) cout << endl;
}

// 打印
void print()
{
    //cout << ++pcnt << ": ";
    for (auto& s : v)
    {
        cout << s;
    }
    //if (v[v.size() - 1].size() == 0 && v.size() > 2) v.pop_back();
    cout << "\n";
}

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    int n; cin >> n;
    //cout << v.size() << endl;
    //cout << Paste.size() <<"\n";
    IsDebug = false;
    v.push_back("");
    v.push_back("");
    for (int i = 0; i < n; i++)
    {
        char c[10]; scanf("%s", c);
        if (c[0] == 'M')
            theMove();
        else if (c[0] == 'I')
            theInsert();
        else if (c[0] == 'R')
            theRemove();
        else if (c[0] == 'P')
            print();
        else if (c[0] == 'S')
            Shift();
        else if (c[0] == 'F')
            Find();
        else if (c[0] == 'C' && c[2] == 'U')
            Count();
        else if (c[0] == 'C' && c[2] == 'P')
            Copy(Paste);
    }
    return 0;
}