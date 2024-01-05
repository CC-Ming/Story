#pragma once
#include"head.h"
#include"draw.h"
class Button
{
private:
    int x, y;
    int width, height;
    int rw = 10, rh = 10;
    float scale;
    bool is_mouseover;
    wstring text;
    COLORREF BKCOLOR = BLACK;
    COLORREF TCOLOR = WHITE;
    std::function<void()> onclik;

public:
    Button(int x, int y, int width, int height, int rw, int rh
        , const wstring& text, COLORREF BK, COLORREF TCO, const std::function<void()>& onclik)
        : x(x - width / 2), y(y - height / 2), width(width), height(height), rw(rw), rh(rh)
        , text(text),BKCOLOR(BK) ,TCOLOR(TCO), onclik(onclik), scale(1.0f), is_mouseover(false) {}

    Button(){}
    void check_mouseover(int mouseX, int mouseY);
    bool check_click(int mouseX, int mouseY, USHORT message = 0);
    void draw();
};

void Button::check_mouseover(int mouseX, int mouseY)
{
    is_mouseover = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
    if (is_mouseover)
    {
        scale = 0.9f;
    }
    else scale = 1.0f;
}

bool Button::check_click(int mouseX, int mouseY, USHORT message)
{
    if (message == 0 &&
        mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        onclik();
        is_mouseover = false;
        scale = 1.0f;
        return true;
    }
    return false;
}

void Button::draw()
{
    int scaled_width = width * scale;
    int scaled_height = height * scale;
    int scaledX = x + (width - scaled_width) / 2;
    int scaledY = y + (height - scaled_height) / 2;
   
    if (is_mouseover)
    {
        setlinecolor(RGB(0, 120, 215));
        setfillcolor(RGB(229, 241, 251));
    }
    else
    {
        setlinecolor(RGB(173, 173, 173));
        setfillcolor(BKCOLOR);
    }
    fillroundrect(scaledX, scaledY, scaledX + scaled_width, scaledY + scaled_height, rw, rh);
    settextcolor(TCOLOR);
    setbkmode(TRANSPARENT);
    write(scaledX + scaled_width / 2, scaledY + scaled_height / 2, text.c_str());
}
