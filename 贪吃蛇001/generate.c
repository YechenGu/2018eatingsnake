//
//  generate.c
//
//
//  Created by macos on 2018/12/10.
//  Copyright @ 2018 macos-gyc. All rights reserved.
//

#include "main.h"
#include "generate.h"
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#define Width 640
#define Height 640
#define distance 20
#define radius 10

extern int poison_x,poison_y;
extern int food_x,food_y;
extern int smart_x,smart_y;
extern int foodState;  //  food remaining
extern int poisonState;  // poison remaining
extern int bombState;   // bomb remaining
extern int smartState;
extern int snakeCount;
extern int preSnakeCount;


extern node *head,*tail,*p1,*p2,*p3,*p;
extern node *bombFirst,*bombLast,*b1,*b2,*b3,*b;

extern char input;
extern char oldInput;
extern unsigned long seed;
extern int map1[2][2];
extern int loopTime1;
extern int map2[12][2];
extern int loopTime2;
extern int map3[129][2];
extern int loopTime3;
extern int remoteLevel;
extern int state[33][33];



void generatefood()     // not must execute
{
    seed++;
    srand(seed);
    food_x=rand()%(Width-20)+10;
    food_x-=(food_x%20);
    if (food_x == 0)
    {
        food_x = distance;
    }
    food_y=rand()%(Height-20)+10;
    food_y-=(food_y%20);
    if (food_y == 0)
    {
        food_y = distance;
    }
    if  (state[food_x/20][food_y/20] != 0)
    {seed++; generatefood();}
    /*if (remoteLevel == 1) {
        for (int a = 0; a<loopTime1; a++)
        {
            if  ((food_x-map1[a][0]<20&&map1[a][0]-food_x<20)&&(food_y-map1[a][1]<20&&map1[a][1]-food_y<20))
                generatefood();
        }
    }
    else if (remoteLevel == 2) {
        for (int a = 0; a<loopTime2; a++)
        {
            if  ((food_x-map2[a][0]<20&&map2[a][0]-food_x<20)&&(food_y-map2[a][1]<20&&map2[a][1]-food_y<20))
                generatefood();
        }
    }
     if necessary , add descripyions about level3
    
    if ((poison_x-food_x<20&&food_x-poison_x<20)&&(poison_y-food_y<20&&food_y-poison_y<20))
    {
        seed++;
        generatefood();
    }
    for (p = head;p ->next != NULL ; p = p->next )
    {
        if ((p->x-food_x<20&&food_x-p->x<20)&&(p->y-food_y<20&&food_y-p->y<20))
        {
            seed++;
            generatefood();
        }
    }
    if ((tail->x-food_x<20&&food_x-tail->x<20)&&(tail->y-food_y<20&&food_y-tail->y<20))
    {
        seed++;
        generatefood();
    }
    
    for (b = bombFirst;b ->next != NULL ; b = b->next )
    {
        
        if ((b->x-food_x<20&&food_x-b->x<20)&&(b->y-food_y<20&&food_y-b->y<20))
        {
            seed++;
            generatefood();
        }
    }
    if ((bombLast->x-food_x<20&&food_x-bombLast->x<20)&&(bombLast->y-food_y<20&&food_y-bombLast->y<20))
    {
        seed++;
        generatefood();
    }*/
    setcolor(GREEN);
    setfillcolor(BLUE);
    fillcircle(food_x,food_y,radius);
    state[food_x/20][food_y/20] = 1;
    foodState = 1;
}
//*********************************************************************************************************************************************************************************

void generatepoison()     // not must execute
{
    seed++;
    srand(seed);
    poison_x=rand()%(Width-20)+10;
    poison_x-=(poison_x%20);
    if (poison_x == 0)
    {
        poison_x = 20;
    }
    poison_y=rand()%(Height-20)+10;
    poison_y-=(poison_y%20);
    if (poison_y == 0)
    {
        poison_y = 20;
    }
    if (state[poison_x/20][poison_y/20] != 0)
    {seed++: generatepoison();}
    /*if (remoteLevel == 1)
    {
        for (int a = 0; a<loopTime1; a++)
        {
            if  ((poison_x-map1[a][0]<20&&map1[a][0]-poison_x<20)&&(poison_y-map1[a][1]<20&&map1[a][1]-poison_y<20))
                generatepoison();
        }
    }
    else if (remoteLevel == 2)
    {
        for (int a = 0; a<loopTime2; a++)
        {
            if  ((poison_x-map2[a][0]<20&&map2[a][0]-poison_x<20)&&(poison_y-map2[a][1]<20&&map2[a][1]-poison_y<20))
                generatepoison();
        }
    }
    
    if ((poison_x-food_x<20&&food_x-poison_x<20)&&(poison_y-food_y<20&&food_y-poison_y<20))
    {
        seed++;
        generatepoison();
    }
    
    for (p = head;p ->next != NULL ; p = p->next )
    {
        
        if ((p->x-poison_x<20&&poison_x-p->x<20)&&(p->y-poison_y<20&&poison_y-p->y<20))
        {
            seed++;
            generatepoison();
        }
    }
    if ((tail->x-poison_x<20&&poison_x-tail->x<20)&&(tail->y-poison_y<20&&poison_y-tail->y<20))
    {
        seed++;
        generatepoison();
    }
    
    for (b = bombFirst;b ->next != NULL ; b = b->next )
    {
        
        if ((b->x-poison_x<20&&poison_x-b->x<20)&&(b->y-poison_y<20&&poison_y-b->y<20))
        {
            seed++;
            generatepoison();
        }
    }
    if ((bombLast->x-poison_x<20&&poison_x-bombLast->x<20)&&(bombLast->y-poison_y<20&&poison_y-bombLast->y<20))
    {
        seed++;
        generatepoison();
    }*/
    setcolor(GREEN);
    setfillcolor(YELLOW);
    fillcircle(poison_x,poison_y,radius);
    state[poison_x/20][poison_y/20] = 2;
    poisonState = 1;
}

//**********************************************************************************************************************************************************************************
void generatebomb()
{
    b1 = (node *)malloc(sizeof(node));
    b1->x=rand()%(Width-20)+10;
    b1->x-=(b1->x%20);
    if (b1->x == 0)
    {
        b1->x = 20;
    }
    b1->y=rand()%(Height-20)+10;
    b1->y-=(b1->y%20);
    if (b1->y == 0)
    {
        b1->y = 20;
    }
    if (state[b1->x/20][b1->y/20] != 0)
    {  seed++; generatebomb();}
    /*if (remoteLevel == 1)
    {
        for (int a = 0; a<loopTime1; a++)
        {
            if  ((b1->x-map1[a][0]<20&&map1[a][0]-b1->x<20)&&(b1->y-map1[a][1]<20&&map1[a][1]-b1->y<20))
                generatebomb();
        }
    }
    else if (remoteLevel == 2)
    {
        for (int a = 0; a<loopTime1; a++)
        {
            if  ((b1->x-map2[a][0]<20&&map2[a][0]-b1->x<20)&&(b1->y-map2[a][1]<20&&map2[a][1]-b1->y<20))
                generatebomb();
        }
    }
    
    if (((poison_x-b1->x<20&&b1->x-poison_x<20)&&(poison_y-b1->y<20&&b1->y-poison_y<20))||((food_x-b1->x<20&&b1->x-food_x<20)&&(b1->y-food_y<20&&food_y-b1->y<20)))
    {
        seed++;
        generatebomb();
    }
    for (p = head;p ->next != NULL ; p = p->next )
    {
        if ((p->x-b1->x<20&&b1->x-p->x<20)&&(p->y-b1->y<20&&b1->y-p->y<20))
        {
            seed++;
            generatebomb();
        }
    }
    if ((tail->x-b1->x<20&&b1->x-tail->x<20)&&(tail->y-b1->y<20&&b1->y-tail->y<20))
    {
        seed++;
        generatebomb();
    }
    //  ++++++++++++++++++++++++++++++++++food self
    for (b = bombFirst;b ->next != NULL ; b = b->next )
    {
        if ((b->x-b1->x<20&&b1->x-b->x<20)&&(b->y-b1->y<20&&b1->y-b->y<20))
        {
            seed++;
            generatebomb();
        }
    }
    if ((bombLast->x-b1->x<20&&b1->x-bombLast->x<20)&&(bombLast->y-b1->y<20&&b1->y-bombLast->y<20))
    {
        seed++;
        generatebomb();
    }*/
    (bombLast->previous)->next = b1;
    b1->previous = (bombLast->previous);
    b1->next = NULL;
    bombLast = b1;
    setcolor(BROWN);
    setfillcolor(RED);
    fillcircle(b1->x,b1->y,radius);
    state[b1->x/20][b1->y/20] = 3;
    bombState = 1;
}

//*************************************************************************************
void generatesmart()
{
    seed++;
    srand(seed);
    if (seed%4 == 0  )
    {
        if (state[1][1] == 0)
        {
            smart_x = 20;
            smart_y = 20;
        }
        else { smartState = 0;}
    }
    else if(seed%4 == 1)
    {
        if (state[31][1] == 0)
        {
            smart_x = 620;
            smart_y = 20;
        }
        else { smartState = 0;}
    }
    else if(seed%4 == 2)
    {
        if (state[1][31] == 0)
        {
            smart_x = 20;
            smart_y = 620;
        }
        else { smartState = 0;}
    }
    else if(seed%4 == 3)
    {
        if (state[31][31] == 0)
        {
            smart_x = 620;
            smart_y = 620;
        }
        else { smartState = 0;}
    }
    
    setcolor(BLUE);
    setfillcolor(WHITE);
    state[smart_x/20][smart_y/20] = 5;
    fillcircle(smart_x,smart_y,radius);
}

