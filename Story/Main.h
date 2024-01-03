#pragma once
#include"head.h"
#include"textbox.h"
#include"button.h"
#include"world.h"
#include"role.h"
#include"draw.h"

wstring music[3] = { L"resources//music//select_click.mp3",
                     L"resources//music//notification.mp3",
                     L"resources//music//magic_whistle.mp3" };
wstring volume[3] = { L"180",L"600",L"80" };

int nowmusic = 0;

wstring setmusic_open(int id){ return L"open "+ music[id];}
wstring setmusic_vol(int id){return L"setaudio " + music[id] + L" volume to " + volume[id];}
wstring setmusic_play(int id){return L"play " + music[id] + L" wait";}
wstring setmusic_close(int id){return L"close " + music[id];}

DWORD WINAPI playMusic(LPVOID lpParame)
{
    wstring str = setmusic_open(nowmusic);
    mciSendString(str.c_str(), 0, 0, 0);
    str = setmusic_vol(nowmusic);
    mciSendString(str.c_str(), 0, 0, 0);
    str = setmusic_play(nowmusic);
    mciSendString(str.c_str(), 0, 0, 0);
    str = setmusic_close(nowmusic);
    mciSendString(str.c_str(), 0, 0, 0);
    return 0;
}

class Widget
{
private:
    int width;
    int height;
    int currentIndex;   //��ǰ��չʾ��ͼƬ
    int win = 0;
    int show = 0;
    World* map_ptr;
    World map;
    Role you;
    Role* you_ptr;
    vector<IMAGE*> pages;
    vector<vector<Button*> > buttons;
    vector<vector<TextBox*> >textBoxs;

    void addPage(IMAGE* page)
    {
        pages.push_back(page);
        buttons.push_back({});
        textBoxs.push_back({});
    }

    void addButton(int index, Button* button)
    {
        if (index >= 0 && index < buttons.size())
        {
            buttons[index].push_back(button);
        }
    }

    void addTextBox(int index, TextBox* textBox)
    {
        if (index >= 0 && index < textBoxs.size())
        {
            textBoxs[index].push_back(textBox);
        }
    }

    void setCurrentIndex(int index)
    {
        if (index >= 0 && index < pages.size())
        {
            currentIndex = index;
        }
    }

    void mouseClick(int mouseX, int mouseY)
    {
        if (currentIndex >= 0 && currentIndex < buttons.size())
        {
            for (Button* button : buttons[currentIndex])
            {
                if (button->check_click(mouseX, mouseY))
                {
                    nowmusic = 0;
                    CreateThread(NULL, 0, playMusic, NULL, NULL, NULL);
                    break;
                }
            }
        }
        if (currentIndex >= 0 && currentIndex < textBoxs.size())
        {
            for (auto textbox : textBoxs[currentIndex])
            {
                if (textbox->checkClick(mouseX, mouseY))show = 0;
            }
        }
    }

    void mouseMove(int mouseX, int mouseY)
    {

        if (currentIndex >= 0 && currentIndex < buttons.size())
        {
            for (Button* button : buttons[currentIndex])
            {
                button->check_mouseover(mouseX, mouseY);
            }
        }
    }

    void keyInput(wchar_t ch)
    {
        if (currentIndex >= 0 && currentIndex < textBoxs.size())
            for (auto textbox : textBoxs[currentIndex])
                if (textbox->getSelect())
                {
                    //�ж��Ƿ��»س���
                    if (!textbox->keyInput(ch))continue;
                    //��ȡ��ǰ��������
                    wstring now = textbox->getText();
                    //����ı�������
                    textbox->clear();
                    //�ж��Ƿ���ͬһ����
                    if (map.getname(you.town) == now)
                    {
                        nowmusic = 1;
                        CreateThread(NULL, 0, playMusic, NULL, NULL, NULL);

                        MessageBoxEx(GetHWnd(), L"  You are already here :)\
                                    \n  Please choose the next memory you want to go", L"Tips:"
                            , MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
                        continue;
                    }
                    //�ж����������뵱ǰ�����ڵĵ�֮���Ƿ���·��
                    int size = 0;
                    Edge* next = map.getnext(you.town, size);
                    for (int i = 0; i < size; i++)
                    {
                        if (map.getname(next[i].from) == now)
                        {
                            int id = next[i].from;
                            //����޷������ߵ�ָ���ĵ�
                            if (you.life - next[i].to <= 0) {
                                you.x = map.getx(you.town) + map.getx(id) >> 1;
                                you.y = map.gety(you.town) + map.gety(id) >> 1;
                                you.life -= next[i].to;
                                you.show(BLACK);
                                win = -1;
                                getimage(pages[2], 0, 0, WINLEN, WINWID);
                                break;
                            }
                            bool flag = false;
                            //��������Ⱦɫ�ǻ����֮ǰ��ͼƬ��
                            if (map.getvis(id) == 0){
                                flag = true;
                                map.setvis(id, 1);
                                map.redraw(id, &(you.before));
                                you.val += map.getval(id);
                                getimage(pages[2], 0, 0, WINLEN, WINWID);
                            }

                            you.show(WHITE);
                            you.add(id);
                            you.x = map.getx(id);
                            you.y = map.gety(id);
                            you.town = id;
                            you.life -= next[i].to;
                            you.show(BLACK);
                            getimage(pages[2], 0, 0, WINLEN, WINWID);

                            if (flag) {
                                nowmusic = 2;
                                CreateThread(NULL, 0, playMusic, NULL, NULL, NULL);
                                Sleep(1000);
                                map.show_town(id, WINLEN / 2, WINWID / 2);
                                getimage(pages[3], 0, 0, WINLEN, WINWID);
                                setCurrentIndex(3);
                            }

                            //��������յ㣬���ʤ��
                            if (id == map.size() - 1)win = 1;
                            break;
                        }
                        //û��·��
                        if (i == size - 1){
                            nowmusic = 1;
                            CreateThread(NULL, 0, playMusic, NULL, NULL, NULL);
                            MessageBoxEx(GetHWnd(), L"  You can't go to there :(\
							        \n  Please chose another with an edge where you are currently located", L"Tips:"
                                , MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
                        }
                    }
                    delete[]next;
                }
    }

    void draw()
    {
        if (currentIndex >= 0 && currentIndex < pages.size())
        {
            putimage(0, 0, pages[currentIndex]);
            if (currentIndex >= 0 && currentIndex < buttons.size())
            {
                for (Button* button : buttons[currentIndex])
                    button->draw();
            }

            if (currentIndex >= 0 && currentIndex < textBoxs.size())
            {
                for (auto textbox : textBoxs[currentIndex])
                {
                    if (textbox->getSelect()) textbox->updateCursor();
                    textbox->draw();
                }
            }
        }

        if (show == 1)
            map.val_path(0, LIFE,BLACK,WHITE,true);
        if (show == 2)
            map.life_path(0, LIFE,BLACK,WHITE,true);
        if (show == 3)
            map.val_path(you.town, you.life, WHITE, BLACK, false);
        if (show == 4)
            map.life_path(you.town, you.life, WHITE, BLACK, false);
    }

    void create()
    {
        initgraph(width, height);
        //���ô��ڳ��ֵ�λ��
        HWND hwnd = GetHWnd();
        SetWindowPos(hwnd, NULL,365, 200, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        BeginBatchDraw();
        //���� World map;
        map_ptr = new World;
        map = *map_ptr;
        srand(1);
        if (!map.create(MAP)) {
            initgraph(WINLEN, WINWID);
            wchar_t s[] = L"Failed to load map!";
            setbkmode(TRANSPARENT);
            settextcolor(WHITE);
            write(WINLEN/2, WINWID/2, s);
            FlushBatchDraw();
            Sleep(2000);
            closegraph();
            exit(-1);
        }
        //������Ϸ��ͼ
        map.show();
        //���������Ⱦɫ
        map.redraw(0);
        //������Ϸ��ɫ
        you_ptr = new Role(map.getx(0), map.gety(0), 0, 0, LIFE);
        you = *you_ptr;
        //������ʾ��
        wchar_t str[] = L"Input the next memory that you want to go: ";
        settextcolor(BLACK);
        write(WINLEN / 2, WINWID / 2 + 60, str);
    }

public:
    Widget(int width, int height)
        :width(width), height(height), currentIndex(-1){}

    ~Widget() {}

    void init()
    {
        // �������˵�
        IMAGE* page1 = new IMAGE(width, height);
        getimage(page1, 0, 0, width, height);
        addPage(page1);
        // �����˵�������ť
        Button* button1_1 = new Button(WINLEN / 2, WINWID / 3, BUTTON_W, BUTTON_H,
            10, 10, L"Start Game", WHITE, RED, [&]() {
                setCurrentIndex(2);
                putimage(0, 0, pages[2]);
                getimage(&you.before, 0, 0, WINLEN, WINWID);
                you.show(BLACK);
                getimage(pages[2], 0, 0, WINLEN, WINWID);
                FlushBatchDraw();});
        Button* button1_2 = new Button(WINLEN / 2, WINWID / 2, BUTTON_W, BUTTON_H,
            10, 10, L"Optimal Route", WHITE, RED, [&]() {setCurrentIndex(1);});
        Button* button1_3 = new Button(WINLEN / 2, WINWID / 3 * 2, BUTTON_W, BUTTON_H,
            10, 10, L"Exit", WHITE, RED, []() {exit(0);});
        addButton(0, button1_1);
        addButton(0, button1_2);
        addButton(0, button1_3);

        // �����Ӳ˵�
        IMAGE* page2 = new IMAGE(width, height);
        getimage(page2, 0, 0, width, height);
        addPage(page2);
        //�����Ӳ˵��İ�ť
        Button* button2_1 = new Button(WINLEN / 2, WINWID / 3, BUTTON_W, BUTTON_H,
            10, 10, L"More Memory", WHITE, RED, [&]() {show = 1;});
        Button* button2_2 = new Button(WINLEN / 2, WINWID / 2 - 10, BUTTON_W, BUTTON_H,
            10, 10, L"More Time", WHITE, RED, [&]() { show = 2;});
        Button* button2_3 = new Button(WINLEN / 2, WINWID / 3 * 2 - 20, BUTTON_W, BUTTON_H,
            10, 10, L"Back", WHITE, RED, [&]() {show = 0;setCurrentIndex(0);});
        addButton(1, button2_1);
        addButton(1, button2_2);
        addButton(1, button2_3);

        //�����������Ϸ��ɫ
        create();
        //������Ϸ����
        IMAGE* page3 = new IMAGE(width, height);
        getimage(page3, 0, 0, width, height);
        addPage(page3);
        // ����Ϸ���洴����ť
        Button* button3_1 = new Button(WINLEN / 5 * 4, WINWID / 3+15, BUTTON_W-10, BUTTON_H-5,
            10, 10, L"More Memory", GBLUE, BLACK, [&]() {show = 3;});
        Button* button3_2 = new Button(WINLEN / 5 * 4, WINWID / 2-10, BUTTON_W-10, BUTTON_H-5,
            10, 10, L"More Time", GBLUE, BLACK, [&]() {show = 4;});
        addButton(2, button3_1);
        addButton(2, button3_2);
        //����Ϸ���洴���ı���
        TextBox* tbox = new TextBox(WINLEN / 2, WINWID / 2 + 95, 80, 25, 20);
        addTextBox(2, tbox);

        //���ŷⴴ����ť
        IMAGE* page4 = new IMAGE(width, height);
        getimage(page4, 0, 0, width, height);
        addPage(page4);
        Button* OK = new Button(570 * WINLEN / 800, 350 * WINWID / 450, BUTTON_W / 2 - 10, BUTTON_H,
            30, 30, L"OK", WHITE, BLACK, [&]() {setCurrentIndex(2);});
        addButton(3, OK);

        //��ʾ���˵�����
        setCurrentIndex(0);
    }

    void run()
    {
        ExMessage msg;
        while (true)
        {
            if (peekmessage(&msg))
            {
                int mouseX = msg.x;
                int mouseY = msg.y;
                switch (msg.message)
                {
                case WM_LBUTTONDOWN:
                    mouseClick(mouseX, mouseY);
                    break;
                case WM_MOUSEMOVE:
                    mouseMove(mouseX, mouseY);
                    break;
                case WM_CHAR:
                    keyInput(msg.ch);
                    break;
                }
            }

            if (win != 0 && currentIndex != 3)
            {
                if (win == 1)
                {
                    draw();
                    wstring str = L"Your route is: ";
                    wstring str_path = you.get_path(map);
                    str += str_path;
                    write(WINLEN / 2, WINWID / 5 * 4, str.c_str());
                    FlushBatchDraw();
                    nowmusic = 1;
                    CreateThread(NULL, 0, playMusic, NULL, NULL, NULL);
                    MessageBoxEx(GetHWnd(), L"                   You Win!           ", L"Tips:"
                        , MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));

                    IMAGE me;
                    loadimage(&me, L"resources//img//role.png",123,132);
                    draw::draw(WINLEN / 5 * 4, WINWID / 4 * 3, &me);
                    FlushBatchDraw();
                }
                else if (win == -1)
                {
                    draw();
                    FlushBatchDraw();
                    nowmusic = 1;
                    CreateThread(NULL, 0, playMusic, NULL, NULL, NULL);
                    MessageBoxEx(GetHWnd(), L"                   You Lose...           ", L"Tips:"
                        , MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
                }
                Sleep(2000);
                nowmusic = 1;
                CreateThread(NULL, 0, playMusic, NULL, NULL, NULL);
                MessageBoxEx(GetHWnd(), L"The game is over ~\
                \nComing back to the main course then", L"Tips:"
                    , MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
                //�ر���Ϸ����
                delete map_ptr;
                delete you_ptr;
                //���¹�������
                create();
                getimage(pages[2], 0, 0, WINLEN, WINWID);
                win = 0;
                show = 0;
                //�������˵�
                setCurrentIndex(0);
            }
            draw();
            FlushBatchDraw();
            Sleep(10);
        }
        EndBatchDraw();
    }

    void close() { closegraph(); }
};