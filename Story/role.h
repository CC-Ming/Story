#pragma once
#include"head.h"
#include"draw.h"
#include"world.h"
class Role {
	int path_mxsz = 4;
	int path_sz = 0;
	int* path;
public:
	IMAGE before;
	IMAGE cor;
	int x, y, town, val, life;
	Role(int _x = 0, int _y = 0, int _town = 0, int _val = 0, int _life = LIFE);
	~Role() {}
	void show(COLORREF COLOR);
	void add(int id);
	wstring get_path(const World& map);
};

wstring Role::get_path(const World& map)
{
	int* stack = new int[path_sz];
	int top = 0;
	for (int i = path_sz - 1; i >= 0; i--)
		stack[top++] = path[i];
	wchar_t str[MAX_PATH] = L"";
	while (top > 0)
	{
		wcscat_s(str, map.getname(stack[--top]).c_str());
		if (top > 0)
		{
			wcscat_s(str, L" --> ");
		}
	}
	delete[]stack;
	return str;
}

void Role::add(int id)
{
	path[path_sz++] = id;
	if (path_sz >= path_mxsz)
	{
		int* tmp = new int[path_mxsz * 2];
		for (int i = 0; i < path_sz;i++)
			tmp[i] = path[i];
		path_mxsz *= 2;	//之前忘记加这句了，瞎走的时候程序直接崩溃了(...
		delete[]path;
		path = tmp;
	}
}

Role::Role(int _x, int _y, int _town, int _val, int _life)
{
	x = _x;
	y = _y;
	town = _town;
	val = _val;
	life = _life;
	loadimage(&cor, L"resources//img//coor.png", 30, 30);
	path = new int[path_mxsz]();
	add(town);
	getimage(&before, 0, 0, WINLEN, WINWID);
}

void Role::show(COLORREF COLOR)
{
	//cleardevice();
	putimage(0, 0, &before);
	draw::draw(x, y - 15, &cor);
	wchar_t strval[30];
	wchar_t strlife[30];
	swprintf_s(strval, L"Memory Fragments: %d", val);//将字符串输出到字符数组
	swprintf_s(strlife, L"Remaining Time: %d", life);
	setbkmode(TRANSPARENT);
	settextcolor(COLOR);
	write(WINLEN / 2, WINWID / 2, strval);
	write(WINLEN / 2, WINWID / 2 + 30, strlife);
}