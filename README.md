# Story
一个基于Easyx的小游戏;A small game based on Easyx;
游戏玩法，从起点开始沿着边走，会消耗一定的时间，首次到达一个记忆点时会收到一封带有记忆的信

#支持自定义地图和文本（可以拿去表白（不是

文件路径在head.h里的最后两个宏里修改：
![image](https://github.com/CC-Ming/Story/assets/151418966/85e7bc97-d482-45b2-96d4-bf626d5b3c19)

map的数据格式，可参照文件里的格式进行自定义：
顶点数目 边数
顶点名称 记忆碎片值
两端顶点编号 消耗时间值

文本格式：每一个顶点对应一行文字即以回车结尾，字数太多可能会超出显示范围，请自行把控

其他游戏参数设置，在head.h里都有标注：
![image](https://github.com/CC-Ming/Story/assets/151418966/42f117f9-5f50-4d1e-8942-e945e9ed4501)

如果地图显示效果比较乱，可以在world.h里根据情况调节以下参数：
![image](https://github.com/CC-Ming/Story/assets/151418966/b7b80fe9-0646-4cb2-a0ba-3d7669be123c)

背景音乐在RUN_Main.cpp中，将蓝框部分替换为自己的音频路径，请确保相对路径或绝对路径正确//ps:不支持网易云下载的MP3格式（别问我怎么知道的（）
![image](https://github.com/CC-Ming/Story/assets/151418966/ea208290-2b3f-42ca-a3be-7c67d73547a0)

提示音在Main.h的开头里可以自行更改：
![image](https://github.com/CC-Ming/Story/assets/151418966/fa57a8f0-f6a6-4ce5-b1d3-0af32113e39f)

#游戏界面截图：
![image](https://github.com/CC-Ming/Story/assets/151418966/dc197c2b-4dba-42f3-9f0b-fdfb1536bc62)
![image](https://github.com/CC-Ming/Story/assets/151418966/d30a5c57-d504-4b55-b07e-09c2f39df621)

