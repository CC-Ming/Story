#pragma once
#include"head.h"
#include"envelope.h"
class Town {
private:
	int rand(int l, int r) { return std::rand() % (r - l + 1) + l; }
public:
	int val;
	wstring name;
	Envelope env;
	bool vis = 0;	//���ڽ����û���������visit���
	bool vis2 = 0;	//���ڵ�������������������·����������visit���
	int x, y;
	double vx, vy;
	Town(wstring str, int value) {
		name = str;
		val = value;
		x = rand(BORDER, WINLEN - BORDER);	
		y = rand(BORDER, WINWID - BORDER);
		vx = vy = 0;
	}
	Town(){}
	~Town(){}
};