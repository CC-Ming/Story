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
	bool vis = 0;	//用于接受用户所产生的visit结果
	bool vis2 = 0;	//用于调用两个遍历计算最优路径所产生的visit结果
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