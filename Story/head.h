#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include<string>
#include<fstream>
#include<cmath>
#include<ctime>			//�������
#include<graphics.h>	//ͼ�ο�
#include<conio.h>		//��������
#include<mmsystem.h>	//���ֲ���
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

#define WINLEN 800		//���ڳ���
#define WINWID 450		//���ڿ��
#define BORDER 60		//�߽���
#define TC1 RED			//δ�����ʹ��ĵ����ɫ
#define TC2 BLUE		//�ѱ����ʹ��ĵ����ɫ
#define RADIUS 10		//Բ�ΰ뾶
#define EPS 1			//��С����
#define LIFE 100		//��ɫ��ʼ����ֵ
#define INF 10000000	//����
#define MAX_PATH 200	//��������ʾ��·�����ȣ�����ͷ�Ϳո���ŵĳ���
#define MAX_BUTTON 10	//һ��ҳ�����ఴť����
#define BUTTON_W 120	//Ĭ�ϰ�ť���
#define BUTTON_H 35		//Ĭ�ϰ�ť�߶�

#define GBLUE RGB(155,175,188)

#define LETTER L"resources//str_en.txt"		//���ּ����ļ�
#define MAP L"resources//map.txt"			//��ͼ�����ļ�