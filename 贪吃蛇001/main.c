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
int bomb_x,bomb_y;
int foodState = 1;  //  food remaining
int poisonState = 1;  // poison remaining
int bombState = 1;   // bomb remaining
int snakeCount = 3;
int preSnakeCount = 3;


node *head,*tail,*p1,*p2,*p3,*p;
node *foodFirst,*foodLast,*f1,*f2,*f3,*f;
char input;
char oldInput = 'd';
unsigned long seed = 2;
int a;
int score = 300;

void startUp();

extern int loopTime1;
extern int map1[10][2];
extern int loopTime2;
extern int map2[50][2];
//***********************************************************************************************************************
void main()
{
    startUp();   //–¬Ω®ª≠≤º£¨ø™ º≈˙¡øª≠Õº£¨“‘º∞ª≠≥ˆ…ﬂµƒ3∏ˆΩ⁄µ„
    for (a=0; a<loopTime1; a++)
    {
        solidrectangle(map1[a][0]-5,map1[a][1]-5,map1[a][0]+3,map1[a][1]+3);
    }
    generatepoison();
    generatebomb();
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
            break;
        for (a = 0; a<loopTime1; a++) {
            if ((head->x-map1[a][0]<15&&map1[a][0]-head->x<15)&&(head->y-map1[a][1]<15&&map1[a][1]-head->y<15))
            {
                goto label1;
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
        
        for (p = head->next;p->next != NULL; p = p->next)        //…ﬂ≥‘µΩ¡À◊‘º∫
        {
            if ((head->x-p->x<20&&p->x-head->x<20)&&(head->y-p->y<20&&p->y-head->y<20))
            {
                goto label1;
            }
            
        }
        if ((head->x-tail->x<20&&tail->x-head->x<20)&&(head->y-tail->y<20&&tail->y-head->y<20))    //…ﬂ≥‘µΩ¡ÀŒ≤∞Õ
        {
            break;
        }
        if ( snakeCount<=2)
        {
            break;
        }
        Sleep(100);
        
        if (score > 2000) //====================================================================================
        {
            startUp();
            for (a=0; a<loopTime2; a++)
            {
                solidrectangle(map2[a][0]-5,map2[a][1]-5,map2[a][0]+3,map2[a][1]+3);
            }
            generatepoison();
            generatebomb();
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
                    goto label1;
                for (a = 0; a<loopTime2; a++) {
                    if ((head->x-map2[a][0]<15&&map2[a][0]-head->x<15)&&(head->y-map2[a][1]<15&&map2[a][1]-head->y<15))
                    {
                        goto label1;
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
                    for (int k = 0;k <= preSnakeCount - snakeCount;k++)      // i∫Õj±‰¡ø√˚≥ÂÕª
                    {
                        fillcircle(tail->x,tail->y,radius);
                        (tail->previous)->next=NULL;
                        tail=tail->previous;
                    }
                    score -= 400;
                    generatebomb();
                }
                
                for (p = head->next;p->next != NULL; p = p->next)        //…ﬂ≥‘µΩ¡À◊‘º∫
                {
                    if ((head->x-p->x<20&&p->x-head->x<20)&&(head->y-p->y<20&&p->y-head->y<20))
                    {
                        goto label1;
                    }
                    
                }
                if ((head->x-tail->x<20&&tail->x-head->x<20)&&(head->y-tail->y<20&&tail->y-head->y<20))    //…ﬂ≥‘µΩ¡ÀŒ≤∞Õ
                {
                    goto label1;
                }
                if ( snakeCount<=2)
                {
                    goto label1;
                }
                Sleep(100);
                
                preSnakeCount = snakeCount;
                
                seed++;
                
                FlushBatchDraw();
            }
        }
        
        preSnakeCount = snakeCount;
        
        seed++;
        
        FlushBatchDraw();
    }
    
label1:EndBatchDraw();
    
    getch();
    
    closegraph();
    
    printf("ƒ„π“¡À!!!\n");
}


//************************************************************************************************************************************************
void startUp()
{
    initgraph(960,Height);
    
    BeginBatchDraw();
    
    setfillcolor(BROWN);                     //draw the wall
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
    
    //=======================================
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
    
    //==================================
    
    f1 = (node *)malloc(sizeof(node));
    f2 = (node *)malloc(sizeof(node));
    f3 = (node *)malloc(sizeof(node));
    
    f1->x=320;
    f1->y=360;
    f2->x=480;
    f2->y=520;
    f3->x=240;
    f3->y=60;
    f1->next = f2;
    f2->next = f3;
    f3->next = NULL;
    f1->previous = NULL;
    f2->previous = f1;
    f3->previous = f2;
    foodFirst = f1;
    foodLast = f3;
    
    setcolor(GREEN);
    setfillcolor(BLUE);
    
    for (f = foodFirst;f ->next != NULL ;f = f->next )
    {
        fillcircle(f->x,f->y,radius);
    }
    fillcircle(foodLast->x,foodLast->y,radius);
}




