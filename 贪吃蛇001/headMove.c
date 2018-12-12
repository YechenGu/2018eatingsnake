//
//  headMove.c
//  Ã∞≥‘…ﬂ001
//
//  Created by macos on 2018/12/10.
//  Copyright ? 2018ƒÍ macos-gyc. All rights reserved.
//

#include "headMove.h"
#include "main.h"
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

extern node *head,*tail,*p1,*p2,*p3,*p;
extern node *foodFirst,*foodLast,*f1,*f2,*f3,*f;

void headMove()
{
    p1 = (node *)malloc(sizeof(node));
    //
    if (kbhit())
    {
        input = getch();
        
        if (input == 'a' )
        {
            if (oldInput == 'd')
            {
                p1->x = head->x+distance;
                p1->y = head->y;
            }
            else
            {
                p1->x = head->x-distance;
                p1->y = head->y;
                oldInput = input;
            }
        }
        else if (input == 'd' )
        {
            if (oldInput == 'a')
            {
                p1->x = head->x-distance;
                p1->y = head->y;
            }
            else
            {
                p1->x = head->x+distance;
                p1->y = head->y;
                oldInput = input;
            }
        }
        else if (input == 'w' )
        {
            if (oldInput == 's')
            {
                p1->x = head->x;
                p1->y = head->y+distance;
            }
            else
            {
                p1->x = head->x;
                p1->y = head->y-distance;
                oldInput = input;
            }
        }
        else if (input == 's' )
        {
            if (oldInput == 'w')
            {
                p1->x = head->x;
                p1->y = head->y-distance;
            }
            else
            {
                p1->x = head->x;
                p1->y = head->y+distance;
                oldInput = input;
            }
        }
        
        else
        {
            if (oldInput == 'a' )
            {
                p1->x = head->x-distance;
                p1->y = head->y;
            }
            else if (oldInput == 'd' )
            {
                p1->x = head->x+distance;
                p1->y = head->y;
            }
            else if (oldInput == 'w' )
            {
                p1->x = head->x;
                p1->y = head->y-distance;
            }
            else if (oldInput == 's' )
            {
                p1->x = head->x;
                p1->y = head->y+distance;
            }
        }
    }
    else
    {
        if (oldInput == 'a' )
        {
            p1->x = head->x-distance;
            p1->y = head->y;
        }
        else if (oldInput == 'd' )
        {
            p1->x = head->x+distance;
            p1->y = head->y;
        }
        else if (oldInput == 'w' )
        {
            p1->x = head->x;
            p1->y = head->y-distance;
        }
        else if (oldInput == 's' )
        {
            p1->x = head->x;
            p1->y = head->y+distance;
        }
    }
    //
    p1->previous = NULL;
    p1 ->next = head;
    head->previous = p1;
    head = p1;
    
    if ((head->x-foodFirst->x<20 && foodFirst->x-head->x<20)&&(head->y-foodFirst->y<20 && foodFirst->y-head->y<20)) {           //eat the food
        foodState = 0;
        setcolor(BLACK);
        setfillcolor(BLACK);
        fillcircle(foodFirst->x,foodFirst->y,radius);
        (foodFirst->next)->previous = NULL;
        foodFirst = foodFirst->next;
        snakeCount++;
    }
    for (f = foodFirst->next;f->next!=NULL;f=f->next){
        if ((head->x-f->x<20 && f->x-head->x<20)&&(head->y-f->y<20 && f->y-head->y<20)) {           //eat the food
            foodState = 0;
            setcolor(BLACK);
            setfillcolor(BLACK);
            fillcircle(f->x,f->y,radius);
            (f->previous)->next = f->next;
            (f->next)->previous = f->previous;
            snakeCount++;
        }
    }
    if ((head->x-foodLast->x<20 && foodLast->x-head->x<20)&&(head->y-foodLast->y<20 && foodLast->y-head->y<20)) {           //eat the food
        foodState = 0;
        setcolor(BLACK);
        setfillcolor(BLACK);
        fillcircle(foodLast->x,foodLast->y,radius);
        (foodLast->previous)->next = NULL;
        foodLast = foodLast->previous;
        snakeCount++;
    }
    
    
    if ((head->x-poison_x<20 && poison_x-head->x<20)&&(head->y-poison_y<20 && poison_y-head->y<20)) {      //eat the poison
        poisonState = 0;
        setcolor(BLACK);
        setfillcolor(BLACK);
        fillcircle(poison_x,poison_y,radius);
        snakeCount--;
    }
    
    if ((head->x-bomb_x<20 && bomb_x-head->x<20)&&(head->y-bomb_y<20 && bomb_y-head->y<20)) {      //eat the bomb
        bombState = 0;
        setcolor(BLACK);
        setfillcolor(BLACK);
        fillcircle(bomb_x,bomb_y,radius);
        if (snakeCount % 2 == 0)
        {
            snakeCount /= 2;
        }
        else
        {
            snakeCount = (snakeCount+1)/2;
        }
    }
    
    
}



