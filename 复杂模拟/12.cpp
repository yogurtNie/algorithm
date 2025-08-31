//
// Created by 12472 on 25-5-22.
//
#include <bits/stdc++.h>
using namespace std;
const string NULLSTR = "null";
const string ENTER = "\n";
const string SPACE = " ";
vector<string> line;     //lines of the file
vector<string> pasteBin; //lines of pasteBin
vector<string> selBin;   //lines of selection
struct pos
{
    int row = 1, col = 1;
    bool operator<(const pos &pp) const
    {
        if (row == pp.row)
            return col < pp.col;
        return row < pp.row;
    }
    bool operator==(const pos &pp) const
    {
        return (row == pp.row) && (col == pp.col);
    }
    pos(int r, int c) : row(r), col(c) {}
    pos() { row = col = 1; }
};
pos Cursor;      //position of the Cursor 0=row,1=column,element=1,2,...
bool shifted = false;     //shift enabled or not.
bool inSelection = false; //selection mode enabled or not.
pos remPoint;             //remPoint for selection. (Just a copy of the Cursor there.)
pos selection[2];         //selection area.
int getSpeciLineIndex(const pos &p) { return p.row - 1; }
int getSpeciCharIndex(const pos &p) { return p.col - 2; }
int getSpeciLineFullLength(const pos &p) { return line[getSpeciLineIndex(p)].length(); } //get the string length of current line.
int getSpeciLineVisLength(const pos &p)
{
    if (*(line[getSpeciLineIndex(p)].rbegin()) == '\n')
        return line[getSpeciLineIndex(p)].length() - 1;
    return getSpeciLineFullLength(p);
}
string getSpeciCursorLeftSub(const pos &p) { return line[getSpeciLineIndex(p)].substr(0, p.col - 1); } //get the substring on the left of the Cursor of the line.
string getSpeciCursorRightSub(const pos &p) { return line[getSpeciLineIndex(p)].substr(p.col - 1); }   //get the substring on the right of the Cursor of the line.
string getSpeciLineVisStr(const pos &p) { return line[getSpeciLineIndex(p)].substr(0, getSpeciLineVisLength(p)); }
void theCopy(vector<string> &);
vector<string> getSelectionArea()
{ //return the range of selection. if not in selection, then  return the whole file.
    vector<string> range;
    if (inSelection)
    {
        //        pasteBinBackUp=pasteBin;
        theCopy(selBin);
        range = selBin;
        //        pasteBin=pasteBinBackUp;
    }
    else
        range = line;
    return range;
}
void Move(int type)
{
    inSelection = false;
    bool moveLR = false;
    if(type == 1){
        Cursor.col = 1;
    }else if(type == 2){
        Cursor.col = getSpeciLineVisLength(Cursor) + 1;
    }else if(type==3){
        if (Cursor.row == 1)
                return;
            moveLR = false;
            if (getSpeciLineVisLength(pos(Cursor.row - 1, Cursor.col)) < Cursor.col - 1)
                moveLR = true; //moded getCurLineLength().
            --Cursor.row;
            if (moveLR)
                Move(2);
    }else if(type ==4){
        if (Cursor.row == line.size())
                return;
            moveLR = false;
            if (getSpeciLineVisLength(pos(Cursor.row + 1, Cursor.col)) < Cursor.col - 1)
                moveLR = true; //moded getCurLineLength().
            ++Cursor.row;
            if (moveLR)
                Move(2);
    }else if(type==5){
        if (Cursor.row == 1 && Cursor.col == 1)
                return;
            if (Cursor.col == 1)
            {
                Move(3);
                Move(2);
                return;
            }
            --Cursor.col;
    }else if(type ==6){
        if (Cursor.row == line.size() && Cursor.col == getSpeciLineVisLength(Cursor) + 1)
                return;
            if (Cursor.col == getSpeciLineVisLength(Cursor) + 1)
            { //moded getCurLineLength().
                Move(4);
                Move(1);
                return;
            }
            ++Cursor.col;
    }else if(type ==7){
        Cursor.col = getSpeciLineVisLength(Cursor) + 2; //moded getCurLineLength().
    }


}

void insert(int, string arg);
void createNextLineWithStr(string str)
{
    auto ins = line.begin();
    for (int i = 1; i <= getSpeciLineIndex(Cursor); i++)
        ++ins;
    line.insert(++ins, str);
    Move(4);
    Move(2);
}

void theCopy(vector<string> &bin)
{
    if (inSelection)
    {
        bin.clear();
        if (selection[0].row == selection[1].row)
        {
            int leftIndex = getSpeciCharIndex(selection[0]) + 1;
            int rightIndex = getSpeciCharIndex(selection[1]);
            if (leftIndex >= 0 && rightIndex >= 0)
                bin.push_back(line[getSpeciLineIndex(selection[1])].substr(leftIndex, rightIndex - leftIndex + 1));
        }
        else
        {
            int upCharIndex = getSpeciCharIndex(selection[0]) + 1;
            int upLineIndex = getSpeciLineIndex(selection[0]);
            int dnCharIndex = getSpeciCharIndex(selection[1]);
            int dnLineIndex = getSpeciLineIndex(selection[1]);
            if (upCharIndex >= 0)
                bin.push_back(line[upLineIndex].substr(upCharIndex));
            else
                bin.push_back(line[upLineIndex]);
            for (int i = upLineIndex + 1; i < dnLineIndex; i++)
            {
                string tmp = line[i];
                bin.push_back(tmp);
            }
            if (dnCharIndex >= 0)
                bin.push_back(line[dnLineIndex].substr(0, dnCharIndex + 1));
        }
        return;
    }
    else if (getSpeciLineVisLength(Cursor) != 0)
    {
        bin.clear();
        bin.push_back(getSpeciLineVisStr(Cursor));
        return;
    }
}

void theRemove(int);
void insert(int type, string arg)
{
    vector<string>::iterator ins;
    string left, right;
    if (inSelection)
    {
        if (type == 4 && pasteBin.empty())
            return;
        if (selection[1] == selection[0])
        {
            Cursor = selection[1];
            inSelection = false;
            insert(type, arg);
            return;
        }
        theRemove(1); //type can be any value.
        insert(type, arg);
        inSelection = false;
        return;
    }
    switch (type)
    {
        case 1:
            line[getSpeciLineIndex(Cursor)] = getSpeciCursorLeftSub(Cursor) + arg + getSpeciCursorRightSub(Cursor);
            Cursor.col += arg.length();
            break;
        case 2:
            right = getSpeciCursorRightSub(Cursor);
            line[getSpeciLineIndex(Cursor)] = getSpeciCursorLeftSub(Cursor) + ENTER;
            ins = line.begin();
            for (int i = 1; i <= getSpeciLineIndex(Cursor); i++)
                ++ins;
            line.insert(++ins, right);
            Move(4);
            Move(1);
            break;
        case 3:
            line[getSpeciLineIndex(Cursor)] = getSpeciCursorLeftSub(Cursor) + SPACE + getSpeciCursorRightSub(Cursor);
            ++Cursor.col;
            break;
        case 4:
            if (pasteBin.empty())
                return;
            right = getSpeciCursorRightSub(Cursor);
            if (pasteBin.size() == 1 && *(pasteBin[0].rbegin()) != '\n')
            {
                line[getSpeciLineIndex(Cursor)] = getSpeciCursorLeftSub(Cursor) + pasteBin[0] + right;
                for (int i = 0; i < pasteBin[0].size(); i++)
                    Move(6);
            }
            else
            {
                int curLine = -1;
                line[getSpeciLineIndex(Cursor)] = getSpeciCursorLeftSub(Cursor) + pasteBin[++curLine];
                for (int i = 1; i < pasteBin.size() - 1; i++)
                    createNextLineWithStr(pasteBin[++curLine]);
                if (*(pasteBin[pasteBin.size() - 1].rbegin()) != '\n')
                {
                    if (curLine + 1 <= pasteBin.size() - 1)
                        createNextLineWithStr(pasteBin[pasteBin.size() - 1] + right);
                    Move(1);
                    for (int i = 0; i < pasteBin[pasteBin.size() - 1].size(); i++)
                        Move(6);
                }
                else
                {
                    if (curLine + 1 <= pasteBin.size() - 1)
                        createNextLineWithStr(pasteBin[pasteBin.size() - 1]);
                    createNextLineWithStr(right);
                    Move(1);
                }
            }
            break;
    }
}

void theRemove(int type)
{
    vector<string>::iterator ins;
    string left, right;
    if (inSelection)
    {
        theCopy(selBin);
        left = getSpeciCursorLeftSub(selection[0]);
        right = getSpeciCursorRightSub(selection[1]);
        Cursor = selection[0];
        line[getSpeciLineIndex(selection[0])] = left + right;
        int firstDelLineIndex;
        firstDelLineIndex = getSpeciLineIndex(selection[0]) + 1;
        for (int i = firstDelLineIndex; i <= selection[1].row - 1;)
        {
            ins = line.begin();
            for (int j = 1; j <= i; j++)
                ++ins;
            line.erase(ins);
            --selection[1].row;
        }
        inSelection = false;
        if (Cursor.row > line.size())
        {
            Move(3);
            Move(2);
        }
        return;
    }
    switch (type)
    {
        case 1:
            if (getSpeciLineIndex(Cursor) + 1 == line.size() && getSpeciCharIndex(Cursor) == getSpeciLineVisLength(Cursor) - 1)
                return; //moded getCurLineLength().
            if (getSpeciCharIndex(Cursor) == getSpeciLineVisLength(Cursor) - 1)
            { //moded getCurLineLength().
                line[getSpeciLineIndex(Cursor)] = getSpeciLineVisStr(Cursor) + line[getSpeciLineIndex(Cursor) + 1];
                ins = line.begin();
                for (int i = 1; i <= getSpeciLineIndex(Cursor); i++)
                    ++ins;
                line.erase(++ins);
                return;
            }
            left = getSpeciCursorLeftSub(Cursor);
            right = getSpeciCursorRightSub(Cursor).substr(1);
            line[getSpeciLineIndex(Cursor)] = left + right;
            break;
        case 2:
            if (getSpeciCharIndex(Cursor) == -1 && getSpeciLineIndex(Cursor) == 0)
                return;
            if (getSpeciCharIndex(Cursor) == -1)
            {
                pos tmpCurs = Cursor; //backup the Cursor. so we can move the Cursor before line is merged.
                Move(3);
                Move(2);
                line[getSpeciLineIndex(tmpCurs) - 1] = getSpeciLineVisStr(pos(tmpCurs.row - 1, tmpCurs.col)) + line[getSpeciLineIndex(tmpCurs)];
                ins = line.begin();
                for (int i = 1; i <= getSpeciLineIndex(tmpCurs); i++)
                    ++ins;
                line.erase(ins);
                return;
            }
            left = getSpeciCursorLeftSub(Cursor).substr(0, getSpeciCharIndex(Cursor));
            right = getSpeciCursorRightSub(Cursor);
            line[getSpeciLineIndex(Cursor)] = left + right;
            --Cursor.col; //Cursor goes back 1 char.
            break;
    }
}

int theFind(string word)
{
    vector<string> range = getSelectionArea();
    int ans = 0;
    for (string curLine : range)
    {
        int fIndex = 0;
        while (fIndex < curLine.length() && (fIndex = curLine.find(word)) != string::npos)
        {
            ++ans;
            curLine = curLine.substr(fIndex + 1);
            fIndex = 0;
        }
    }
    return ans;
}

void shift()
{
    shifted = !shifted;
    if (shifted)
    {
        if (inSelection)
        {
            inSelection = false;
            return;
        }
        remPoint = Cursor;
    }
    else
    {
        if (remPoint == Cursor)
            return;
        if (remPoint < Cursor)
        {
            selection[0] = remPoint;
            selection[1] = Cursor;
        }
        else
        {
            selection[1] = remPoint;
            selection[0] = Cursor;
        }
        inSelection = true;
    }
}

int theCount()
{
    vector<string> range = getSelectionArea();
    int ans = 0;
    for (string str : range)
        for (char c : str)
            if (c != ' ' && c != '\n')
                ans++;
    return ans;
}

void thePrint()
{
    for (string str : line)
        if (!str.empty())
            cout << str;
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    int opCnt;
    cin >> opCnt;
    line.emplace_back("");
    string op, arg1;
    bool insertChar = false; //for debug.
    for (int opI = 1; opI <= opCnt; opI++)
    {
        insertChar = false;
        cin >> op;
        switch(op[0]){
            case 'M': {
                cin >> arg1;
                switch(arg1[0]){
                    case 'H':{
                        Move(1);
                        break;
                    }
                    case 'E':{
                        Move(2);
                        break;
                    }
                    case 'U':{
                        Move(3);
                        break;
                    }
                    case 'D':{
                        Move(4);
                        break;
                    }
                    case 'L':{
                        Move(5);
                        break;
                    }
                    case 'R':{
                        Move(6);
                        break;
                    }
                }

            break;
            }
            case 'I':
                    {
                        cin >> arg1;
                        switch(arg1[0]){
                            case 'C':{
                                string arg2;
                            cin >> arg2;
                            insert(1, arg2);
                            insertChar = true; // for debug.
                            break;
                            }
                            case 'E':{
                                insert(2, NULLSTR);
                                break;
                            }
                            case 'S':{
                                insert(3, NULLSTR);
                                break;
                            }
                            case 'P':{
                                insert(4, NULLSTR);
                                break;
                            }
                        }

                        break;
                    }
            case 'R': {
                cin >> arg1;
            if (arg1 == "Del")
            {
                theRemove(1);
            }
            else if (arg1 == "Backspace")
            {
                theRemove(2);
            }
            break;
            }
            case 'S':{
                shift();
                break;
            }
            case 'F':{
                cin >> arg1;
            int ans = theFind(arg1);
            cout << ans << endl;
            break;
            }
            case 'C':{
                if(op[2]=='P'){
                    theCopy(pasteBin);
                }else if(op[2]=='U'){
                    cout << theCount() << endl;
                }
                break;
            }
            case 'P':{
                thePrint();
                break;
            }
        }

    }
    return 0;
}