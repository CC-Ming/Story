#pragma once
#include"head.h"
#include"draw.h"

class TextBox
{
private:
    int x;
    int y;
    int width;
    int height;
    int maxWord;    //最长单词个数
    wstring text;   //文本
    bool isSelected;//是否被选中
    bool showCursor;//是否显示光标
    int cursorPos;  //光标位置

public:
    TextBox(int x, int y, int width, int height, int maxWord)
        : x(x - width / 2), y(y - height / 2), width(width), height(height), maxWord(maxWord),
        isSelected(false), showCursor(true), cursorPos(0) {}

    wstring getText() const { return text; }
    bool getSelect() const { return isSelected; }
    bool isEmpty() const { return text.empty(); }
    void clear() { text = L"";cursorPos = 0; }
    void setText(const wstring& newText);
    void draw();
    bool checkClick(int mouseX, int mouseY);
    bool keyInput(wchar_t ch);
    void updateCursor();
};

void TextBox::setText(const wstring& newText)
{
    text = newText;
    cursorPos = text.length();
}

void TextBox::draw()
{
    setfillcolor(WHITE);
    if (isSelected)
    {
        setlinecolor(RGB(0, 120, 215));
        fillrectangle(x, y, x + width, y + height);
    }
    else
    {
        setlinecolor(RGB(122, 122, 122));
        fillrectangle(x, y, x + width, y + height);
    }

    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    //settextstyle(height * 3 / 4, 0, _T("微软雅黑"));

    //outtextxy(x + 5, y + (height - textheight(_T("微软雅黑"))) / 2, text.c_str());
    outtextxy(x + 5, y + 5, text.c_str());

    setlinecolor(BLACK);
    if (isSelected && showCursor)
    {
        int cursorX = x + 5 + textwidth(text.substr(0, cursorPos).c_str());
        line(cursorX, y + 2 + height / 8, cursorX, y + height * 7 / 8 - 2);
    }
}

bool TextBox::checkClick(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        isSelected = true;
        return true;
    }
    else
    {
        isSelected = false;
        cursorPos = text.length();
        return false;
    }
}

bool TextBox::keyInput(wchar_t ch)
{
    if (isSelected)
    {
        switch (ch)
        {
        case '\b':				// 用户按退格键，删掉一个字符
            if (!text.empty() && cursorPos > 0)
            {
                text.erase(cursorPos - 1, 1);
                cursorPos--;
            }
            break;
        case '\r':
        case '\n':
            cursorPos = text.length();
            isSelected = true;
            return true;
            break;
        default:				// 用户按其它键，接受文本输入
            if (text.length() < maxWord)
            {
                text.insert(cursorPos, 1, ch);
                cursorPos++;
            }
        }
    }
    return false;
}

void TextBox::updateCursor()
{
    static DWORD lastTick = GetTickCount();
    DWORD currentTick = GetTickCount();
    if (currentTick - lastTick >= 500) // 每500毫秒切换光标状态
    {
        showCursor = !showCursor;
        lastTick = currentTick;
    }
}