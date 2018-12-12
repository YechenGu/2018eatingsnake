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
extern int bomb_x,bomb_y;
extern int foodState;  //  food remaining
extern int poisonState;  // poison remaining
extern int bombState;   // bomb remaining
extern int snakeCount;
extern int preSnakeCount;


extern node *head,*tail,*p1,*p2,*p3,*p;
extern node *foodFirst,*foodLast,*f1,*f2,*f3,*f;

extern char input;
extern char oldInput;
extern unsigned long seed;
extern int map1[10][2];
extern int loopTime1;




void generatefood()     // not must execute
{
    f1 = (node *)malloc(sizeof(node));
    srand(seed);
    f1->x=rand()%(Width-20)+10;
    f1->x-=(f1->x%20);
    if (f1->x == 0)
    {
        f1->x = 20;
    }
    f1->y=rand()%(Height-20)+10;
    f1->y-=(f1->y%20);
    if (f1->y == 0)
    {
        f1->y = 20;
    }
    
    
    for (int a = 0; a<loopTime1; a++) {
        if  ((f1->x-map1[a][0]<15&&map1[a][0]-f1->x<15)&&(f1->y-map1[a][1]<15&&map1[a][1]-f1->y<15))
            generatefood();
    }
    if (((poison_x-f1->x<20&&f1->x-poison_x<20)&&(poison_y-f1->y<20&&f1->y-poison_y<20))||((bomb_x-f1->x<20&&f1->x-bomb_x<20)&&(f1->y-bomb_y<20&&bomb_y-f1->y<20)))
    {
        seed++;
        generatefood();
    }
    for (p = head;p ->next != NULL ; p = p->next )
    {
        if ((p->x-f1->x<20&&f1->x-p->x<20)&&(p->y-f1->y<20&&f1->y-p->y<20))
        {
            seed++;
            generatefood();
        }
    }
    if ((tail->x-f1->x<20&&f1->x-tail->x<20)&&(tail->y-f1->y<20&&f1->y-tail->y<20))
    {
        seed++;
        generatefood();
    }
    //  ++++++++++++++++++++++++++++++++++food self
    for (f = foodFirst;f ->next != NULL ; f = f->next )
    {
        if ((f->x-f1->x<20&&f1->x-f->x<20)&&(f->y-f1->y<20&&f1->y-f->y<20))
        {
            seed++;
            generatefood();
        }
    }
    if ((foodLast->x-f1->x<20&&f1->x-foodLast->x<20)&&(foodLast->y-f1->y<20&&f1->y-foodLast->y<20))
    {
        seed++;
        generatefood();
    }
    foodLast->next = f1;
    f1->previous = foodLast;
    f1->next = NULL;
    foodLast = f1;
    setcolor(GREEN);
    setfillcolor(BLUE);
    fillcircle(f1->x,f1->y,radius);
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
    
    
    for (int a = 0; a<loopTime1; a++) {
        if  ((poison_x-map1[a][0]<15&&map1[a][0]-poison_x<15)&&(poison_y-map1[a][1]<15&&map1[a][1]-poison_y<15))
            generatefood();
    }
    if ((poison_x-bomb_x<20&&bomb_x-poison_x<20)&&(poison_y-bomb_y<20&&bomb_y-poison_y<20))
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
    
    for (f = foodFirst;f ->next != NULL ; f = f->next )
    {
        
        if ((f->x-poison_x<20&&poison_x-f->x<20)&&(f->y-poison_y<20&&poison_y-f->y<20))
        {
            seed++;
            generatepoison();
        }
    }
    if ((foodLast->x-poison_x<20&&poison_x-foodLast->x<20)&&(foodLast->y-poison_y<20&&poison_y-foodLast->y<20))
    {
        seed++;
        generatepoison();
    }
    setcolor(GREEN);
    setfillcolor(YELLOW);
    fillcircle(poison_x,poison_y,radius);
    poisonState = 1;
}

//**********************************************************************************************************************************************************************************
void generatebomb()
{
    seed++;
    srand(seed);
    bomb_x=rand()%(Width-20)+10;
    bomb_x-=(bomb_x%20);
    if (bomb_x == 0)
    {
        bomb_x = distance;
    }
    bomb_y=rand()%(Height-20)+10;
    bomb_y-=(bomb_x%20);
    if (bomb_y == 0)
    {
        bomb_y = distance;
    }
    
    for (int a = 0; a<loopTime1; a++) {
        if  ((bomb_x-map1[a][0]<15&&map1[a][0]-bomb_x<15)&&(bomb_y-map1[a][1]<15&&map1[a][1]-bomb_y<15))
            generatefood();
    }
    if ((poison_x-bomb_x<20&&bomb_x-poison_x<20)&&(poison_y-bomb_y<20&&bomb_y-poison_y<20))
    {
        seed++;
        generatebomb();
    }
    for (p = head;p ->next != NULL ; p = p->next )
    {
        
        if ((p->x-bomb_x<20&&bomb_x-p->x<20)&&(p->y-bomb_y<20&&bomb_y-p->y<20))
        {
            seed++;
            generatebomb();
        }
    }
    if ((tail->x-bomb_x<20&&bomb_x-tail->x<20)&&(tail->y-bomb_y<20&&bomb_y-tail->y<20))
    {
        seed++;
        generatebomb();
    }
    
    for (f = foodFirst;f ->next != NULL ; f = f->next )
    {
        
        if ((f->x-bomb_x<20&&bomb_x-f->x<20)&&(f->y-bomb_y<20&&bomb_y-f->y<20))
        {
            seed++;
            generatepoison();
        }
    }
    if ((foodLast->x-bomb_x<20&&bomb_x-foodLast->x<20)&&(foodLast->y-bomb_y<20&&bomb_y-foodLast->y<20))
    {
        seed++;
        generatepoison();
    }
    setcolor(BROWN);
    setfillcolor(RED);
    fillcircle(bomb_x,bomb_y,radius);
    bombState = 1;
}








