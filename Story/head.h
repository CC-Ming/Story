#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include<string>
#include<fstream>
#include<cmath>
#include<ctime>			//随机种子
#include<graphics.h>	//图形库
#include<conio.h>		//按键交互
#include<mmsystem.h>	//音乐播放
#include<functional>
#include<Windows.h>

//----------------------
#include<iostream>
#include<iomanip>
#include<vector>
using std::vector;
using std::cout;
using std::wcout;
using std::fixed;
using std::setw;
using std::setprecision;
//----------------------

using std::wifstream;
using std::ofstream;
using std::string;
using std::wstring;

#define WINLEN 800		//窗口长度
#define WINWID 450		//窗口宽度
#define BORDER 60		//边界宽度
#define TC1 RED			//未被访问过的点的颜色
#define TC2 BLUE		//已被访问过的点的颜色
#define RADIUS 10		//圆形半径
#define EPS 1			//最小精度
#define LIFE 100		//角色初始生命值
#define INF 10000000	//无穷
#define MAX_PATH 200	//最多可以显示的路径长度（含箭头和空格符号的长度
#define MAX_BUTTON 10	//一个页面的最多按钮数量
#define BUTTON_W 120	//默认按钮宽度
#define BUTTON_H 35		//默认按钮高度

#define GBLUE RGB(155,175,188)

#define LETTER L"resources//str_en.txt"		//文字加载文件
#define MAP L"resources//map.txt"			//地图加载文件