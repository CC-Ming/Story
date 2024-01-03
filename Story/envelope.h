#pragma once
#include"head.h"
#include"draw.h"
#include"button.h"

class Envelope
{
public:
	wstring content = L"";
	IMAGE* paper;
	int height = WINWID / 6 * 5;
	int width = WINLEN / 3 * 2;
	Envelope(wstring str);
	~Envelope() {}
	void show(int x, int y);
};

Envelope::Envelope(wstring str = L"")
{
	content = str;
	paper = new IMAGE(width,height);
	loadimage(paper, L"resources//img//paper.png", width, height);
}

void Envelope::show(int x, int y)
{
	draw::draw(x, y, paper);
	LOGFONT* font = new LOGFONT;
	gettextstyle(font);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(18, 0, L"System", 0, 0, 0, 0, 1, 0);
	int sx = x - width / 2 + width / 5;
	int sy = y - height / 2 + height / 5;
	int tx = x - width / 2 + width / 5 * 4;
	int ty = y - height / 2 + height / 5 * 4;
	if (content.size() <= 50)sy += 85;
	else if (content.size() <= 100)sy += 70;
	else if (content.size() <= 150)sy += 60;
	else if (content.size() <= 290)sy += 50;
	else if (content.size() <= 400)sy += 25;
	RECT r = { sx,sy,tx,ty };
	drawtext(content.c_str(), &r, DT_CENTER | DT_WORDBREAK);
	settextstyle(font);
	delete font;
	FlushBatchDraw();
}