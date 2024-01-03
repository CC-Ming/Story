#pragma once
#include"head.h"
#include"town.h"
#include"draw.h"
#include"stack.h"
#include"envelope.h"
struct Edge { int from, to; };
class World {
private:
	Town* v;	//顶点映射
	int n, m;	//顶点数和边数

	int* h;		//邻接表表头
	int* w;		//边权值
	int* e;		//节点
	int* ne;	//next节点
	wstring str_life = L"";
	wstring str_val = L"";

	int vmx = -INF;
	int all_val = 0;
	int* ans;
	int ans_sz = 0;

	Edge* edge;	//边集合//用来给点分配坐标的
	int idx, idx2;
	//-----------力导向算法参数---------------
	int loop = 160;
	double spring = 0.1;
	double coulomb = 3000;
	double nature = 80;
	double step = 1;
	//----------------------------------------
	void add(int a, int b, int wt);
	void force();
	void local();
	wstring get_path(int id, int* path);
	void write_path(wstring str, COLORREF COLOR, bool all = true);
	bool load_letter();
public:
	bool create(wstring str);
	void show();
	void close() { closegraph(); }
	int size() { return n; }
	int getx(int id)const { return v[id].x; }
	int gety(int id) const{ return v[id].y; }
	int getval(int id) const{ return v[id].val; }
	int getvis(int id) const{ return v[id].vis; }
	void setvis(int id, int VIS) { v[id].vis = VIS; }
	wstring getname(int id) const{ return v[id].name; }
	Edge* getnext(int id, int& size);
	void life_path(int start, int your_life, COLORREF BK, COLORREF COLOR, bool all);
	void val_path(int start, int your_life, COLORREF BK, COLORREF COLOR, bool all);
	void redraw(int id, IMAGE* before);
	void redraw(int id);
	void dfs_val_path(stack<int>* last_life, stack<int>* last_value, int* tx, int t_sz, int life, int value, int now);
	~World();
	void show_town(int id, int x, int y);
};

void World::redraw(int id)
{
	setfillcolor(TC2);
	solidcircle(v[id].x, v[id].y, RADIUS);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	write(v[id].x, v[id].y, v[id].name.c_str());
}

void World::redraw(int id,IMAGE* before)
{
	putimage(0, 0, before);
	setfillcolor(TC2);
	solidcircle(v[id].x, v[id].y, RADIUS);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	write(v[id].x, v[id].y, v[id].name.c_str());
	getimage(before, 0, 0, WINLEN, WINWID);
}

void World::write_path(wstring str, COLORREF COLOR, bool all)
{
	setbkmode(TRANSPARENT);
	settextcolor(COLOR);
	if(all)
		write(WINLEN / 2, WINWID / 5 * 4, str.c_str());
	else
	{
		wstring tmp = L"";
		if (str.size() >= 7) tmp = str.substr(6, 1);
		write(WINLEN / 2, WINWID / 5 * 4, tmp.c_str());
	}
}

wstring World::get_path(int id, int* path)
{
	int* stack = new int[MAX_PATH];
	int top = 0;
	stack[top++] = id;
	for (int i = path[id]; i != -1; i = path[i])
		stack[top++] = i;
	wstring str = L"";
	while (top > 0)
	{
		str += v[stack[--top]].name;
		if (top > 0)
		{
			str+= L" --> ";
		}
	}
	delete[]stack;
	return str;
}

void World::life_path(int start, int your_life, COLORREF BK, COLORREF COLOR, bool all)
{
	write_path(str_life, BK, all);
	int* dis = new int[n];
	int* path = new int[n];
	for (int i = 0; i < n; i++)
	{
		dis[i] = INF;
		v[i].vis2 = 0;
	}
	path[start] = -1;
	dis[start] = 0;
	//Dijkstra
	for (int i = 1; i < n;i++)
	{
		int t = -1;
		for (int j = 0; j < n; j++)
		{
			if (v[j].vis2 == false && (t == -1 || dis[j] < dis[t]))
				t = j;
		}

		v[t].vis2 = true;
		for (int j = 0; j < n; j++)
		{
			int weight = INF;
			for (int k = h[t]; k != -1;k = ne[k])
			{
				if (e[k] == j)
				{
					weight = w[k];
					break;
				}
			}
			if (dis[j] > dis[t] + weight)
			{
				dis[j] = dis[t] + weight;
				path[j] = t;
			}
		}
	}
	str_life = L"I'm Sorry, you have no way to survive anymore :(";
	if (dis[n - 1] >= your_life)
	{
		write_path(str_life, COLOR, true);
	}
	else
	{
		str_life = get_path(n - 1, path);
		write_path(str_life, COLOR, all);
	}

	delete[]dis;
	delete[]path;
}

//从起始点到i点的所有路径中，在背包容量为_Life的情况下，所能装进的最大值
//dp的话，路径可以重复，path记录不了多个前驱，只能暴搜了（）
void World::val_path(int start, int your_life, COLORREF BK, COLORREF COLOR, bool all)
{
	write_path(str_val, BK, all);
	int* tx = new int [MAX_PATH];
	vmx = -INF;
	ans_sz = 0;
	//清空标记
	for (int i = 0; i < n; i++)
		v[i].vis2 = 0;
	v[start].vis2 = true;
	stack<int>* last_life = new stack<int>[n];
	stack<int>* last_value = new stack<int>[n];
	dfs_val_path(last_life,last_value, tx, 0, your_life, 0, start);

	str_val = L"";
	str_val += v[start].name;
	str_val += L" --> ";
	for (int i = 0; i < ans_sz; i++)
	{
		str_val += v[ans[i]].name;
		if (i < ans_sz - 1)str_val += L" --> ";
	}
	if (ans_sz == 0)
	{
		str_val = L"I'm Sorry, you have no way to survive anymore :(";
		write_path(str_val, COLOR, true);
	}
	else write_path(str_val, COLOR, all);
	delete[]tx;
	delete[]last_life;
	delete[]last_value;
}

void World::dfs_val_path(stack<int>* last_life, stack<int>* last_value, int* tx, int t_sz, int life, int value, int now)
{
	if (value == all_val && t_sz > ans_sz && ans_sz != 0)return;
	bool flag = false;
	if (life <= 0)return;
	if (!v[now].vis2)
	{
		flag = 1;
		v[now].vis2 = true;
		if(!v[now].vis)
			value += v[now].val;
	}

	if (now == n - 1)
	{
		if ((vmx < value) || 
			(vmx == value && 
			(ans_sz == 0 || t_sz < ans_sz))
			)
		{
			vmx = value;
			for (int i = 0; i < t_sz; i++)
				ans[i] = tx[i];
			ans_sz = t_sz;
		}
		if (flag)
		{
			v[now].vis2 = false;
			if (!v[now].vis)
				value -= v[now].val;
		}
		return;
	}
	if (!last_life[now].empty() && last_life[now].top() == life && last_value[now].top() == value)return;
	last_life[now].push(life);
	last_value[now].push(value);
	for (int i = h[now]; i != -1; i = ne[i])
	{
		int j = e[i];
		tx[t_sz++] = j;
		dfs_val_path(last_life, last_value, tx, t_sz, life - w[i], value, j);
		t_sz--;
	}
	last_life[now].pop();
	last_value[now].pop();
	if (flag)
	{
		v[now].vis2 = false;
		if (!v[now].vis)
			value -= v[now].val;
	}
}

Edge* World::getnext(int id, int& size)
{
	Edge* ans = new Edge[n];
	size = 0;
	for (int i = h[id]; i != -1; i = ne[i])
		ans[size++] = { e[i],w[i] };
	return ans;
}

World::~World()
{
	closegraph();
	delete[]v;
	delete[]e;
	delete[]w;
	delete[]ne;
	delete[]edge;
	delete[]h;
	delete[]ans;
}

void World::force()
{
	double* forcex = new double[n]();
	double* forcey = new double[n]();
	//计算弹簧力
	for (int k = 0; k < m; k++)
	{
		int i = edge[k].from, j = edge[k].to;
		double dx = v[i].x - v[j].x;
		double dy = v[i].y - v[j].y;
		double dis = sqrt(dx * dx + dy * dy);
		if (dis < EPS)dis = EPS;
		//F = k * （dis - nature）
		double springforce = spring * (dis - nature);

		//cout << "btween " << i << " and " << j << " FS is " << springforce << "\n";

		//力的分解
		double fx = springforce * dx / dis;
		double fy = springforce * dy / dis;
		forcex[i] -= fx;
		forcey[i] -= fy;
		forcex[j] += fx;
		forcey[j] += fy;
	}
	//cout << "===========================\n";
	//计算库仑力
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			double dx = v[i].x - v[j].x;
			double dy = v[i].y - v[j].y;
			double dis2 = dx * dx + dy * dy;
			if (dis2 < EPS)dis2 = EPS;
			double dis = sqrt(dis2);
			//F = k * q1 * q2 / dis^2
			double coulombforce = coulomb * (1 / dis2);

			//cout << "btween " << i << " and " << j << " FC is " << coulombforce << "\n";

			//力的分解
			double fx = coulombforce * dx / dis;
			double fy = coulombforce * dy / dis;
			forcex[i] += fx;
			forcey[i] += fy;
			forcex[j] -= fx;
			forcey[j] -= fy;
		}
	}
	//cout << "--------then---------\n";
	//根据力更新点的速度
	for (int i = 0; i < n; i++)
	{
		v[i].vx = forcex[i];
		v[i].vy = forcey[i];
		//cout << i << "--> vx: " << fixed << setprecision(2) << setw(6) << v[i].vx
		//	<< "   vy: " << fixed << setprecision(2) << setw(6) << v[i].vy << "\n";
	}
	delete[]forcex;
	delete[]forcey;
}

void World::local()
{
	for (int k = 1; k <= loop; k++)
	{
		//cout << "-----This is " << k << " loop-----\n";
		force();
		for (int i = 0; i < n; i++)
		{
			v[i].x += v[i].vx * step;
			v[i].y += v[i].vy * step;
		}

		//cout << "------------" << k << " after:\n";
		//for (int i = 0; i < n; i++)
		//{
		//	cout << i << ":" << v[i].x << " " << v[i].y << "\n";
		//}
		//cout << "------------END------------\n\n";
		step = 4.2 / k;
	}
}

void World::add(int a, int b, int wt)
{
	e[idx] = b;
	w[idx] = wt;
	ne[idx] = h[a];
	h[a] = idx++;
}

bool World::load_letter()
{
	wifstream fin;
	fin.open(LETTER);
	if (!fin.is_open()) return false;
	for (int i = 0; i < n; i++)
	{
		wstring str;
		getline(fin, str);
		Envelope evp(str);
		v[i].env = evp;
	}
	return true;
}

bool World::create(wstring str)
{
	wifstream fin;
	fin.open(str);
	if (!fin.is_open()) return false;
	fin >> n >> m;
	v = new Town[n];
	e = new int[2 * m];
	w = new int[2 * m];
	ne = new int[2 * m];
	edge = new Edge[m];
	h = new int[n];
	ans = new int[MAX_PATH];
	//初始化邻接表表头均为-1
	//h2没有初始化啊啊啊啊啊啊啊
	for (int i = 0; i < n; i++)h[i] = - 1;
	//将顶点名字与编号关联
	for (int i = 0; i < n; i++)
	{
		wstring name;
		int val;
		fin >> name >> val;
		Town t(name, val);
		v[i] = t;
		all_val += val;
		//pv[i] = val;
	}
	//加边
	for (int i = 0; i < m; i++)
	{
		int a, b, wt;
		fin >> a >> b >> wt;
		edge[i] = { a,b };
		add(a, b, wt);
		add(b, a, wt);
	}
	local();
	return load_letter();
}

void World::show()
{
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(TC1);
	int aver_x = 0;
	int aver_y = 0;
	for (int i = 0; i < n; i++)
	{
		aver_x += v[i].x;
		aver_y += v[i].y;
	}

	aver_x /= n;
	aver_y /= n;

	for (int i = 0; i < n; i++)
	{
		v[i].x += WINLEN / 3 - aver_x;
		v[i].y += WINWID / 3 - aver_y;
	}

	for (int k = 0; k < m; k++)
	{
		int i = edge[k].from;
		int j = edge[k].to;
		setlinecolor(BLACK);
		line(v[i].x, v[i].y, v[j].x, v[j].y);
	}
	for (int i = 0; i < n; i++)
	{
		solidcircle(v[i].x, v[i].y, RADIUS);
		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		write(v[i].x, v[i].y, v[i].name.c_str());
	}
}

void World::show_town(int id,int x,int y) 
{
	v[id].env.show(x, y);
}