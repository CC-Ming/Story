# Story基本介绍
这是一个关于记忆的文字游戏，基于Easyx实现。
主角误打误撞来到了一个奇怪的世界，在这个世界里主角拥有一定量的可支配时间，并且世界里的每一个小镇都封存着主角过往的一部分记忆，如果主角耗尽了她可支配的时间，那么她就会永远的被困在这个世界里。主角想离开这个地方，尽快回到现实世界中，因为她还有一堆作业要写，但是又很想知道过去究竟发生了什么，会是被自己已经遗忘的记忆吗？在这里可以找回来吗？

关于More Memory 和 More Time按钮，分别对应可以到达出口时获得最多记忆碎片的路径和剩余时间最多的路径，主菜单有最优路线的选择按钮可以进行查看，游戏界面也有相应的路径提示

# 支持自定义地图和文本（可以拿去表白（不是

文件路径在head.h里的最后两个宏里修改：
```
#define LETTER L"resources//str_en.txt"  //文字加载文件
#define MAP L"resources//map.txt"        //地图加载文件
```

map的数据格式，可参照文件里的格式进行自定义：
顶点数目 边数
顶点名称 记忆碎片值
两端顶点编号 消耗时间值

文本格式：每一个顶点对应一行文字即以回车结尾，字数太多可能会超出显示范围，请自行把控

其他游戏参数设置，在head.h里都有标注：
```
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
```

如果地图显示效果比较乱，可以在world.h里根据情况调节以下参数：
```
//-----------力导向算法参数---------------
int loop = 160;
double spring = 0.1;
double coulomb = 3000;
double nature = 80;
double step = 1;
//----------------------------------------
```
背景音乐及其音量大小在RUN_Main.cpp中，可替换为自己的音频路径，请确保相对路径或绝对路径正确//ps:不支持网易云下载的MP3格式（别问我怎么知道的（）
```
mciSendStringW(L"open resources//music//Auld_Lang_Syne.mp3 alias bgm", NULL, 0, NULL);
mciSendStringW(L"setaudio bgm volume to 280", NULL, 0, NULL);
```

提示音及其音量大小可在Main.h的开头里自行更改：
```
wstring music[3] = { L"resources//music//select_click.mp3",
                     L"resources//music//notification.mp3",
                     L"resources//music//magic_whistle.mp3" };
wstring volume[3] = { L"180",L"600",L"80" };
```

# 游戏界面截图：

<img src="https://github.com/CC-Ming/Story/assets/151418966/e87ab69d-c5d9-4c7e-a6ec-ab853a9ba1f9" width = "600" height = "337" alt="主菜单" align=center />

<img src="https://github.com/CC-Ming/Story/assets/151418966/c7e848f9-6e95-421a-a830-524af9f52222" width = "600" height = "337" alt="游戏胜利界面" align=center />

<img src="https://github.com/CC-Ming/Story/assets/151418966/d30a5c57-d504-4b55-b07e-09c2f39df621" width = "600" height = "337" alt="信封界面" align=center />

