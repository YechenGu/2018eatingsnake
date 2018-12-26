#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include "headMove.h"
#include "generate.h"
#include "map1.h"
#include "smartGrass.h"
#include "rankList.h"
#include "load.h"
#include "main.h"
#define Width 640
#define Height 640
#define distance 20
#define radius 9
#define initScore 1000
#pragma comment(lib,"winmm.lib")

//设计UI界面，完成用户登陆系统

int poison_x,poison_y;
int oldPoison_x,oldPoison_y;
int food_x,food_y;
int smart_x = 20,smart_y = 20;
int foodState = 1;  //  依然存在食物
int poisonState = 1;  // 依然存在毒草
int bombState = 1;   // 依然存在炸弹
int snakeCount = 3;
int preSnakeCount = 3;
int state[33][33];  // 0 -- empty  1 -- food 2 -- poison  3 -- bomb  4 -- snake  5 -- smartGrass  6 -- wall
int smartState = 0;    // 0--没生成 1--进入智慧模式 2--已经生成还没吃
int rankState;

node *head,*tail,*p1,*p2,*p3,*p;
node *bombFirst,*bombLast,*b1,*b2,*b3,*b;
char input;
char oldInput = 'd';
char smartDirection;     //智慧模式下的方向
unsigned long seed = 2;
int a;
int score = initScore;
char s[6];
char user_name[30];

void welcomeMain();
void welcomeN();
void welcomeS();
void Game();
void newStartUp();
void oldStartUp();
void gameOver();

extern int loopTime1;
extern int map1[2][2];
extern int loopTime2;
extern int map2[12][2];
extern int loopTime3;
extern int map3[131][2];
int loadStatus;

int gameState = 0;
int difficulty;
int remoteLevel = 1;

//****************************=== main    函数  ===****************************//
int main()
{
    initgraph(960,Height);     // 初始化画布
    BeginBatchDraw();
    mciSendString("open .\\battle1.mp3 alias bkmusic",NULL,0,NULL);
    mciSendString("play bkmusic repeat",NULL,0,NULL);
    settextstyle(18, 0, _T("宋体"));
    outtextxy(350,200," 请     输      入     姓      名  ");
    FlushBatchDraw();
    scanf("%s", user_name);
    cleardevice();
labelWelcome:welcomeMain();
    if (gameState == 1)         //选择新游戏
    {
        remoteLevel = 1;
        Game();
        cleardevice();
    }
    else if (gameState == 2)     // 选择读档
    {
        FILE *fp;
        fp = fopen(".\\load.txt", "r");     //从文件读出
        fscanf(fp, "%d",&loadStatus);
        fclose(fp);
        if   (loadStatus == 1)
        {loadOut();}
        else                    //如果没有存档的话，就进行提示
        {
            outtextxy(310,310," 暂   时   没   有   存   档   ！ ");
            FlushBatchDraw();
            Sleep(1000);
            cleardevice();
            goto labelWelcome;
        }
        Game();
        cleardevice();
    }
    else if (gameState == 3)      //选择查看排行榜
    {
        rankListOpen();
        goto labelWelcome;
    }
    else if (gameState == 4)      //选择查看说明书
    {cleardevice(); goto labelWelcome;}
    goto labelWelcome;
    EndBatchDraw();
    getch();
    closegraph();
    return 0;
}

void welcomeN()                     //  开始新游戏的初始化界面
{
    settextcolor(GREEN);
    remoteLevel = 1;
    rankState = 0;
    score = initScore;
    oldInput = 'd';
    settextstyle(18, 0, _T("宋体"));
    outtextxy(350,200," 请     选      择     难     度  ");
    outtextxy(220,360," 1 ----- 简  单          2 ----- 中  等          3 ----- 困  难   ");
    settextstyle(16, 0, _T("宋体"));
    FlushBatchDraw();
labelInvalidInput:difficulty = getch()-48;
    if (difficulty<1 || difficulty >3)      //在难度选择无效的情况下提示错误信息
    {
        outtextxy(320,450," InvalidInput  !  Please  input  again  !");
        goto labelInvalidInput;
    }
    cleardevice();
}

void welcomeS()    //  读入旧游戏的初始化界面
{
    settextcolor(GREEN);
    outtextxy(430,250," 欢   迎   回   来  ");
    outtextxy(400,350," 加       载        中 ");
    rankState = 0;
    FlushBatchDraw();
    Sleep(2000);
    cleardevice();
}

void welcomeMain()    //  游戏的主初始化界面
{
labelInit:    settextcolor(BLUE);
    settextstyle(32, 0, _T("宋体"));
    outtextxy(350,70,"贪    吃    蛇");
    settextstyle(16, 0, _T("宋体"));
    settextcolor(GREEN);
    outtextxy(300,200," N    键   - - - - - -  新    游   戏");
    outtextxy(300,300," L    键   - - - - - -  加  载  存  档 ");
    outtextxy(300,400," R    键   - - - - - -  排    行   榜");
    outtextxy(300,500," G    键   - - - - - -  游  戏  说  明 ");
    outtextxy(300,600," Q    键   - - - - - -  退  出  游  戏 ");
    FlushBatchDraw();
    char user_choose = getch();
    if (user_choose == 'n')
    {
        gameState = 1;
        cleardevice();
        welcomeN();
    }
    else if (user_choose == 'l')
    {
        gameState = 2;
        cleardevice();
        welcomeS();
    }
    else if (user_choose == 'r')
    {
        gameState = 3;
    }
    else if (user_choose == 'g')
    {
        cleardevice();
        outtextxy(300,100," 绿   色   的   是   聪   明   的   小   蛇");
        outtextxy(300,200," 蓝   色   的   是   美   味   的   食   物");
        outtextxy(300,300," 黄   色   的   是   有   毒   的   毒   草");
        outtextxy(300,400," 红   色   的   是   烈   性   的   炸   药");
        outtextxy(220,500," 白 色 的 是 智 慧 草 , 也 可 以 敲 击 键 盘 退 出 智 慧 模 式");
        outtextxy(330,600," 按   任   意   键   退   出");
        FlushBatchDraw();
        mciSendString("close dingdongmusic",NULL,0,NULL);
        mciSendString("open .\\dingdong.mp3 alias dingdongmusic",NULL,0,NULL);
        mciSendString("play dingdongmusic",NULL,0,NULL);
        Sleep(3000);
        getch();
        gameState = 4;
    }
    else if (user_choose == 'q')
    {
        exit(0);
    }
    else
    {
        cleardevice();
        outtextxy(320,300,"  请      重      新      输      入");
        FlushBatchDraw();
        Sleep(1000);
        cleardevice();
        goto labelInit;
    }
    cleardevice();
}



void gameOver()
{
    cleardevice();
    if (rankState == 1)
    {
        outtextxy(300,280," 恭 喜 ! 你 进 入 了 排 行 榜");
        mciSendString("close enterRankmusic",NULL,0,NULL);
        mciSendString("open .\\enterRank.mp3 alias enterRankmusic",NULL,0,NULL);
        mciSendString("play enterRankmusic",NULL,0,NULL);
    }
    else
    {
        outtextxy(280,280," 很 遗 憾 ， 你 没 有 进 入 排 行 榜");
        mciSendString("close notEnterRankmusic",NULL,0,NULL);
        mciSendString("open .\\notEnterRank.mp3 alias notEnterRankmusic",NULL,0,NULL);
        mciSendString("play notEnterRankmusic",NULL,0,NULL);
    }
    outtextxy(320,420," 按   任   意   键   退   出");
    FlushBatchDraw();
    Sleep(300);
    getch();
}

void Game()
{
    if (gameState == 2) {oldStartUp();}                //  如果选取读档模式，那么就采取读档模式下的初始化方式
    
    if (remoteLevel == 1)                             //  检测当前属于第几关
    {}//normal state
    else if (remoteLevel == 2)
    {
    labelGame2:Sleep(300);
        cleardevice();
        mciSendString("close passmusic",NULL,0,NULL);
        mciSendString("open .\\fireworks.mp3 alias passmusic",NULL,0,NULL);
        mciSendString("play passmusic",NULL,0,NULL);
        settextcolor(GREEN);
        outtextxy(300,320,"恭    喜   !   你    通   过   了   第   一   关  !");
        FlushBatchDraw();
        Sleep(3000);
        cleardevice();
    }
    else if (remoteLevel == 3)
    {
    labelGame3:Sleep(300);
        cleardevice();
        mciSendString("close passmusic",NULL,0,NULL);
        mciSendString("open .\\fireworks.mp3 alias passmusic",NULL,0,NULL);
        mciSendString("play passmusic",NULL,0,NULL);
        settextcolor(GREEN);
        outtextxy(300,320,"恭    喜   !   你    通   过   了   第   二   关  !");
        FlushBatchDraw();
        Sleep(3000);
        cleardevice();
    }
    
    if (gameState == 1) {newStartUp();}                 //如果选取新游戏，那么就采取新游戏模式下的初始化方式
    
    setfillcolor(BROWN);                                //画出地图里面的墙
    if (remoteLevel == 1)
    {
        for (a=0; a<loopTime1; a++)                     //画出地图里面的墙
        {
            solidrectangle(map1[a][0]-10,map1[a][1]-10,map1[a][0]+8,map1[a][1]+8);
            state[map1[a][0]/20][map1[a][1]/20] = 6;
        }
    }
    else if (remoteLevel == 2)
    {
        for (a=0; a<loopTime2; a++)                     //画出地图里面的墙
        {
            solidrectangle(map2[a][0]-10,map2[a][1]-10,map2[a][0]+8,map2[a][1]+8);
            state[map2[a][0]/20][map2[a][1]/20] = 6;
        }
    }
    else if (remoteLevel == 3)
    {
        for (a=0; a<loopTime3; a++)                     //画出地图里面的墙
        {
            solidrectangle(map3[a][0]-10,map3[a][1]-10,map3[a][0]+8,map3[a][1]+8);
            state[map3[a][0]/20][map3[a][1]/20] = 6;
        }
    }
    
    if(gameState == 1) {generatepoison();}              //新游戏下生成初始毒草
    if(gameState == 1) {generatefood();}                //新游戏下生成初始食物

    setfillcolor(BLACK);                                //给予开始游戏前的准备
    solidrectangle(700,300,950,330);
    settextcolor(WHITE);
    outtextxy(720,310,"按 任 意 键 开 始");
    
    settextcolor(BLUE);
    outtextxy(750,350,"游  戏  说  明");
    setcolor(YELLOW);
    setfillcolor(GREEN);
    fillcircle(750,400,radius);
    outtextxy(850,400,"蛇    身");
    setcolor(GREEN);
    setfillcolor(BLUE);
    fillcircle(750,450,radius);
    outtextxy(850,450,"食    物");
    setcolor(GREEN);
    setfillcolor(YELLOW);
    fillcircle(750,500,radius);
    outtextxy(850,500,"毒    草");
    setcolor(BROWN);
    setfillcolor(RED);
    fillcircle(750,550,radius);
    outtextxy(850,550,"炸    弹");
    setcolor(BLUE);
    setfillcolor(WHITE);
    fillcircle(750,600,radius);
    outtextxy(850,600,"智  慧  草");
    FlushBatchDraw();
    
    getch();
    setfillcolor(BLACK);
    solidrectangle(700,300,950,360);
    settextcolor(WHITE);
    outtextxy(720,310,"按 M 键 保 存 游 戏");             //提示玩家存档的操作
    FlushBatchDraw();
    settextcolor(WHITE);
    outtextxy(720,210,"当前分数:");
    
    
    while(1)                                              // 在初始化之后，进入游戏的响应事件循环
    {
        if (seed%10 != 0 && seed%10 != 1)                 // 控制毒草是否闪烁，整除10，或者余1就变黑，不能整除就照样显示
        {
            setcolor(GREEN);
            setfillcolor(YELLOW);
            fillcircle(poison_x,poison_y,radius);
        }
        else
        {
            setcolor(BLACK);
            setfillcolor(BLACK);
            fillcircle(poison_x,poison_y,radius);
        }
        
        if (seed%1000 < 300 )                           // 控制毒草消失
        {
            setfillcolor(BLACK);
            fillcircle(poison_x,poison_y,radius);
            state[poison_x/20][poison_y/20] = 0;
            oldPoison_x = poison_x;
            oldPoison_y = poison_y;
            poison_x = -40;
            poison_y = -40;
        }
        else                                            // 控制毒草重新出现
        {
            if (state[oldPoison_x/20][oldPoison_y/20] != 0)
            {
                generatepoison();
            }
            else
            {
                setcolor(GREEN);
                setfillcolor(YELLOW);
                fillcircle(oldPoison_x,oldPoison_y,radius);
                state[poison_x/20][poison_y/20] = 2;
                poisonState = 1;
            }
        }
        
        headMove();
        
        if (head->x > Width-distance ||head->x < distance || head->y > Height-distance ||head->y < distance )
            goto labelGameOver;                                                         //撞边缘的墙而死
        
        if (remoteLevel == 1)
        {
            for (a = 0; a<loopTime1; a++) {
                if ((head->x-map1[a][0]<20&&map1[a][0]-head->x<20)&&(head->y-map1[a][1]<20&&map1[a][1]-head->y<20))
                {
                    goto labelGameOver;                                                  //撞关卡的墙而死
                }
            }
        }
        else if (remoteLevel == 2)
        {
            for (a = 0; a<loopTime2; a++) {
                if ((head->x-map2[a][0]<20&&map2[a][0]-head->x<20)&&(head->y-map2[a][1]<20&&map2[a][1]-head->y<20))
                {
                    goto labelGameOver;
                }                                                                         //撞关卡的墙而死
            }
        }
        else if (remoteLevel == 3)
        {
            for (a = 0; a<loopTime3; a++) {
                if ((head->x-map3[a][0]<20&&map3[a][0]-head->x<20)&&(head->y-map3[a][1]<20&&map3[a][1]-head->y<20))
                {
                    goto labelGameOver;
                }                                                                         //撞关卡的墙而死
            }
        }
        
        for (p = head->next;p->next != NULL; p = p->next)
        {
            if ((head->x-p->x<20&&p->x-head->x<20)&&(head->y-p->y<20&&p->y-head->y<20))
            {
                goto labelGameOver;                                                      //吃到自己而死
            }
            
        }
        if ((head->x-tail->x<20&&tail->x-head->x<20)&&(head->y-tail->y<20&&tail->y-head->y<20))
        {
            goto labelGameOver;                                                         //吃到自己尾巴而死
        }
        
        
        setcolor(YELLOW);                               //画出头
        setfillcolor(GREEN);
        fillcircle(head->x,head->y,radius);
        
        
        if (smartState == 0 &&  seed%317 == 0 && remoteLevel<=2)          //是否生成智慧草
        {
            generatesmart();
            smartState = 2;
        }
        
        if (smartState == 1)                            //是否进入智慧模式
        {
            smartDirection = oldInput;
            smartGrass();
        }
        
        
        
        if (foodState == 1 && poisonState == 1 && bombState == 1 )          //食物毒草炸弹都没吃就一切照旧
        {
            setcolor(BLACK);
            setfillcolor(BLACK);
            fillcircle(tail->x,tail->y,radius);
            state[tail->x/20][tail->y/20] = 0;
            (tail->previous)->next=NULL;
            tail=tail->previous;
        }
        else if (foodState == 0)
        {
            score += 50*difficulty;
            generatefood();
        }
        else if (poisonState == 0)
        {
            setcolor(BLACK);
            setfillcolor(BLACK);
            fillcircle(tail->x,tail->y,radius);
            state[tail->x/20][tail->y/20] = 0;
            (tail->previous)->next=NULL;
            tail=tail->previous;
            fillcircle(tail->x,tail->y,radius);
            state[tail->x/20][tail->y/20] = 0;
            (tail->previous)->next=NULL;
            tail=tail->previous;
            score -= 100*difficulty;
            if ( snakeCount<=2)
            {
                goto labelGameOver;
            }
            generatepoison();
        }
        else if (bombState == 0)
        {
            setcolor(BLACK);
            setfillcolor(BLACK);
            for (int j = 0;j <= preSnakeCount - snakeCount;j++)      //
            {
                fillcircle(tail->x,tail->y,radius);
                state[tail->x/20][tail->y/20] = 0;
                (tail->previous)->next=NULL;
                tail=tail->previous;
            }
            score -= 200*difficulty;
            if ( snakeCount<=2)
            {
                goto labelGameOver;
            }
            generatebomb();
        }
        
        setfillcolor(BLACK);                            //打印分数
        solidrectangle(800,200,860,230);
        settextcolor(WHITE);
        sprintf(s,"%d",score);
        outtextxy(820,210,s);
        
        
        if (remoteLevel==2&&score >= 2000)              //达到要求，升级进入第三关
        {
            remoteLevel = 3;
            smartState = 0;
            gameState = 1;
            goto labelGame3;
        }
        if (remoteLevel==1&&score >= 3000)              //达到要求，升级进入第二关
        {
            remoteLevel = 2;
            smartState = 0;
            gameState = 1;
            goto labelGame2;
        }
        
        
        if (remoteLevel == 1) Sleep(210/difficulty);
        else if (remoteLevel == 2) Sleep(180/difficulty);
        else if (remoteLevel == 3) Sleep(150/difficulty);
        
        preSnakeCount = snakeCount;
        
        seed++;
        
        FlushBatchDraw();
        
    }
    
labelGameOver:FlushBatchDraw();
    mciSendString("close deathmusic",NULL,0,NULL);
    mciSendString("open .\\death.mp3 alias deathmusic",NULL,0,NULL);
    mciSendString("play deathmusic",NULL,0,NULL);
    rankList();
    Sleep(500);
    settextcolor(RED);
    gameOver();
}
//*****************************=== 恢复旧游戏 ===*****************************//
void oldStartUp()
{
    setfillcolor(BROWN);                                             //画出地图周围的墙
    int i;
    int y,z;
    for ( i = 0;i <= Height;i += radius)
    {
        solidrectangle(0,i,8,i+8);
        solidrectangle(Width-radius,i,Width-2,i+8);
    }
    for ( i = 10; i <= Width-radius;i+=radius)
    {
        solidrectangle(i,0,i+8,8);
        solidrectangle(i,Height-radius,i+8,Height-2);
    }
    
    setcolor(YELLOW);
    setfillcolor(GREEN);
    for (p = head;p != NULL ; p = p->next )
    {fillcircle(p->x,p->y,radius);}
    setcolor(BROWN);
    setfillcolor(RED);
    for (b = bombFirst;b != NULL ;b = b->next)
    {fillcircle(b->x,b->y,radius);}
    setcolor(GREEN);
    setfillcolor(YELLOW);
    fillcircle(poison_x,poison_y,radius);
    setcolor(GREEN);
    setfillcolor(BLUE);
    fillcircle(food_x,food_y,radius);
    if (smartState == 2)
    {
        setcolor(BLUE);
        setfillcolor(WHITE);
        fillcircle(smart_x,smart_y,radius);
    }
}
//*****************************=== 新游戏状态下的初始化 ===*****************************//
void newStartUp()
{
    setfillcolor(BROWN);                                             //画出地图周围的墙
    int i;
    int y,z;
    for(y=0;y<33;y++)
    {
        for(z=0;z<33;z++)
        {state[y][z] = 0;}
    }
    for ( i = 0;i <= Height;i += radius)
    {
        solidrectangle(0,i,8,i+8);
        solidrectangle(Width-radius,i,Width-2,i+8);
    }
    for ( i = 10; i <= Width-radius;i+=radius)
    {
        solidrectangle(i,0,i+8,8);
        solidrectangle(i,Height-radius,i+8,Height-2);
    }
    
    for (i=0; i<=Height; i+=20)
    {
        state[0][i/20] = 6;
        state[Width/20][i/20] = 6;
    }
    for (i=20; i<=Width-distance; i+=20) {
        state[i/20][0] = 6;
        state[i/20][Height/20] = 6;
    }
    
    //========================================================== 画出初始状态下的蛇
    p1 = (node *)malloc(sizeof(node));
    p2 = (node *)malloc(sizeof(node));
    p3 = (node *)malloc(sizeof(node));
    
    p1->x=120;
    p1->y=200;
    state[p1->x/20][p1->y/20] = 4;
    p2->x=100;
    p2->y=200;
    state[p2->x/20][p2->y/20] = 4;
    p3->x=80;
    p3->y=200;
    state[p3->x/20][p3->y/20] = 4;
    oldInput = 'd';
    p1->next = p2;
    p2->next = p3;
    p3->next = NULL;
    p1->previous=NULL;
    p2->previous=p1;
    p3->previous=p2;
    
    head = p1;
    tail = p3;
    
    setcolor(YELLOW);
    setfillcolor(GREEN);
    
    for (p = head;p ->next != NULL ; p = p->next )
    {
        fillcircle(p->x,p->y,radius);
        state[p->x/20][p->y/20] = 4;
    }
    fillcircle(tail->x,tail->y,radius);
    state[tail->x/20][tail->y/20] = 4;
    
    snakeCount = 3;
    preSnakeCount = 3;
    
    //=================================================  画出初始状态下的墙
    
    b1 = (node *)malloc(sizeof(node));
    b2 = (node *)malloc(sizeof(node));
    b3 = (node *)malloc(sizeof(node));
    
    b1->x=320;
    b1->y=360;
    state[b1->x/20][b1->y/20] = 3;
    b2->x=480;
    b2->y=520;
    state[b2->x/20][b2->y/20] = 3;
    b3->x=240;
    b3->y=60;
    state[b3->x/20][b3->y/20] = 3;
    b1->next = b2;
    b2->next = b3;
    b3->next = NULL;
    b1->previous = NULL;
    b2->previous = b1;
    b3->previous = b2;
    bombFirst = b1;
    bombLast = b3;
    
    setcolor(BROWN);
    setfillcolor(RED);
    
    for (b = bombFirst;b ->next != NULL ;b = b->next )
    {
        fillcircle(b->x,b->y,radius);
        state[b->x/20][b->y/20] = 3;
    }
    fillcircle(bombLast->x,bombLast->y,radius);
    state[bombLast->x/20][bombLast->y/20] = 3;
}
