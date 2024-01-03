#include"Main.h"
#pragma comment(lib, "winmm.lib")
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
//int main()
{
    mciSendStringW(L"open resources//music//Auld_Lang_Syne.mp3 alias bgm", NULL, 0, NULL);
    mciSendStringW(L"setaudio bgm volume to 280", NULL, 0, NULL);
    mciSendString(L"play bgm repeat", NULL, 0, NULL);
    Widget widget(WINLEN, WINWID);
    widget.init();
    widget.run();
    widget.close();
    return 0;
}