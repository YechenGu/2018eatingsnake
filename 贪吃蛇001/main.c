// I will get down to replacing food with bomb

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include "headMove.h"
#include "generate.h"
#include "map1.h"
#include "main.h"
#define Width 640
#define Height 640
#define distance 20
#define radius 10

int poison_x,poison_y;
int food_x,food_y;
int foodState = 1;  //  food remaining
int poisonState = 1;  // poison remaining
int bombState = 1;   // bomb remaining
int snakeCount = 3;
int preSnakeCount = 3;


node *head,*tail,*p1,*p2,*p3,*p;
node *bombFirst,*bombLast,*b1,*b2,*b3,*b;
char input;
char oldInput = 'd';
unsigned long seed = 2;
int a;
int score = 400;

void welcome();
void startUp();
void game();
void gameOver();

extern int loopTime1;
extern int map1[2][2];
extern int loopTime2;
extern int map2[12][2];

static int difficulty;
int remoteLevel = 1;

//***********************************************************************************************************************
int main()
{
    initgraph(960,Height);     //init the canvas
    BeginBatchDraw();
labelWelcome:welcome();
    remoteLevel = 1;
    game(1);
labelGame2:remoteLevel = 2;
    game(2);
labelGameOver:gameOver();
    EndBatchDraw();
    getch();
    closegraph();
    return 0;
}

void welcome()    //
{
    outtextxy(460,310,"Welcome to the world of eating snake,please enter the difficulty you like  ");
    outtextxy(460,330,"1--easy  2--normal  3--hard  4--crazy  5--hell ");
    FlushBatchDraw();
    difficulty = getch();
    cleardevice();
}

void gameOver()
{
     cleardevice();
     outtextxy(460,320,"Oh!!! You have died!!! Press any button to quit");
     FlushBatchDraw();
}

void game(int level)
{
    startUp();
    
    if (level == 1)
    {
        for (a=0; a<loopTime1; a++)      //draw the map wall   >>>
        {
            solidrectangle(map1[a][0]-10,map1[a][1]-10,map1[a][0]+8,map1[a][1]+8);
        }
    }
    else if (level == 2)
    {
        for (a=0; a<loopTime2; a++)      //draw the map wall   >>>
        {
            solidrectangle(map2[a][0]-10,map2[a][1]-10,map2[a][0]+8,map2[a][1]+8);
        }
    }
    
    generatepoison();
    generatefood();
    
    while(1)
    {
        if (seed%10 != 0 && seed%10 != 1)
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
        
        headMove();
        
        if (head->x > Width-distance ||head->x < distance || head->y > Height-distance ||head->y < distance )
            goto labelGameOver;
        
        if (level == 1)
        {
            for (a = 0; a<loopTime1; a++) {
                if ((head->x-map1[a][0]<20&&map1[a][0]-head->x<20)&&(head->y-map1[a][1]<20&&map1[a][1]-head->y<20))
                {
                    goto labelGameOver;
                }
            }
        }
        else if (level == 2)
        {
            for (a = 0; a<loopTime2; a++) {
                if ((head->x-map2[a][0]<20&&map2[a][0]-head->x<20)&&(head->y-map2[a][1]<20&&map2[a][1]-head->y<20))
                {
                    goto labelGameOver;
                }
            }
        }
        
        setcolor(YELLOW);
        setfillcolor(GREEN);
        fillcircle(head->x,head->y,radius);
        
        if (foodState == 1 && poisonState == 1 && bombState == 1 )
        {
            setcolor(BLACK);
            setfillcolor(BLACK);
            fillcircle(tail->x,tail->y,radius);
            (tail->previous)->next=NULL;
            tail=tail->previous;
        }
        else if (foodState == 0)
        {
            score += 100;
            generatefood();
        }
        else if (poisonState == 0)
        {
            setcolor(BLACK);
            setfillcolor(BLACK);
            fillcircle(tail->x,tail->y,radius);
            (tail->previous)->next=NULL;
            tail=tail->previous;
            fillcircle(tail->x,tail->y,radius);
            (tail->previous)->next=NULL;
            tail=tail->previous;
            score -= 200;
            generatepoison();
        }
        else if (bombState == 0)
        {
            setcolor(BLACK);
            setfillcolor(BLACK);
            for (int j = 0;j <= preSnakeCount - snakeCount;j++)      // i∫Õj±‰¡ø√˚≥ÂÕª
            {
                fillcircle(tail->x,tail->y,radius);
                (tail->previous)->next=NULL;
                tail=tail->previous;
            }
            score -= 400;
            generatebomb();
        }
        
        if (level==1&&socre >= 2000)
        {
            goto labelGame2;
        }
        
        for (p = head->next;p->next != NULL; p = p->next)        //…ﬂ≥‘µΩ¡À◊‘º∫
        {
            if ((head->x-p->x<20&&p->x-head->x<20)&&(head->y-p->y<20&&p->y-head->y<20))
            {
                goto labelGameOver;
            }
            
        }
        if ((head->x-tail->x<20&&tail->x-head->x<20)&&(head->y-tail->y<20&&tail->y-head->y<20))    //…ﬂ≥‘µΩ¡ÀŒ≤∞Õ
        {
            goto labelGameOver;
        }
        if ( snakeCount<=2)
        {
            goto labelGameOver;
        }
        
        if (level == 1) Sleep(240/difficulty);
        else if (level == 2) Sleep(180/difficulty);
        
        }
        
        preSnakeCount = snakeCount;
        
        seed++;
        
        FlushBatchDraw();
    
}


//************************************************************************************************************************************************
void startUp()
{
    setfillcolor(BROWN);                     //draw the boundry wall
    int i;
    for ( i = 0;i <= Height;i += radius)
    {
        solidrectangle(0,i,8,i+8);
    }
    for ( i = 0;i <= Height;i += radius)
    {
        solidrectangle(Width-radius,i,Width-2,i+8);
    }
    for ( i = 10; i <= Width-10;i+=radius)
    {
        solidrectangle(i,0,i+8,8);
    }
    for ( i = 10; i <= Width-radius;i+=radius)
    {
        solidrectangle(i,Height-radius,i+8,Height-2);
    }
    
    //=======================================   draw the init snake
    p1 = (node *)malloc(sizeof(node));
    p2 = (node *)malloc(sizeof(node));
    p3 = (node *)malloc(sizeof(node));
    
    p1->x=120;
    p1->y=200;
    p2->x=100;
    p2->y=200;
    p3->x=80;
    p3->y=200;
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
    }
    fillcircle(tail->x,tail->y,radius);
    
    //==================================  draw the init bomb
    
    b1 = (node *)malloc(sizeof(node));
    b2 = (node *)malloc(sizeof(node));
    b3 = (node *)malloc(sizeof(node));
    
    b1->x=320;
    b1->y=360;
    b2->x=480;
    b2->y=520;
    b3->x=240;
    b3->y=60;
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
    }
    fillcircle(bombLast->x,bombLast->y,radius);
}



/*
 I will get down to creating smart grass
 
 吃到智慧草 ||-> 判断食物相对于蛇的位置
 -> 假设是右上方 -> 判断移动方向 ->  假设是向右边移动 -> 判断右边，上边，下边有没有障碍物 -> 假设都有 -> 吃顺序：毒草>炸弹>自身和墙 ->GG or 吃到食物
                                       上
                                       下
                                       左
 -> 假设是左下方
 
 
 
 -> 假设是右方
 
 
 从上方开始顺时针
 
 
 */


void smartGrass()
{
    if (head->x==food_x&&head->y<food_y) {
        if (oldInput == 'w') {
            if (<#condition#>) {
                <#statements#>
            }
        }
    }
}
