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
extern int food_x,food_y;
extern int foodState;  //  food remaining
extern int poisonState;  // poison remaining
extern int bombState;   // bomb remaining
extern int snakeCount;
extern int preSnakeCount;
extern int state[32][32];


extern node *head,*tail,*p1,*p2,*p3,*p;
extern node *bombFirst,*bombLast,*b1,*b2,*b3,*b;

extern char input;
extern char oldInput;
extern unsigned long seed;


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
    state[head->x/20][head ->y/20] = 4;
    //=========== not deal yet
    if ((head->x-bombFirst->x<20 && bombFirst->x-head->x<20)&&(head->y-bombFirst->y<20 && bombFirst->y-head->y<20)) {           //eat the bomb
        bombState = 0;
        setcolor(BLACK);
        setfillcolor(BLACK);
        fillcircle(bombFirst->x,bombFirst->y,radius);
        (bombFirst->next)->previous = NULL;
        bombFirst = bombFirst->next;
        if (snakeCount % 2 == 0)
        {
            snakeCount /= 2;
        }
        else
        {
            snakeCount = (snakeCount+1)/2;
        }
    }
    for (b = bombFirst->next;b->next!=NULL;b=b->next){
        if ((head->x-b->x<20 && b->x-head->x<20)&&(head->y-b->y<20 && b->y-head->y<20)) {           //eat the bomb
            bombState = 0;
            setcolor(BLACK);
            setfillcolor(BLACK);
            fillcircle(b->x,b->y,radius);
            (b->previous)->next = b->next;
            (b->next)->previous = b->previous;
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
    if ((head->x-bombLast->x<20 && bombLast->x-head->x<20)&&(head->y-bombLast->y<20 && bombLast->y-head->y<20)) {           //eat the bomb
        foodState = 0;
        setcolor(BLACK);
        setfillcolor(BLACK);
        fillcircle(bombLast->x,bombLast->y,radius);
        (bombLast->previous)->next = NULL;
        bombLast = bombLast->previous;
        if (snakeCount % 2 == 0)
        {
            snakeCount /= 2;
        }
        else
        {
            snakeCount = (snakeCount+1)/2;
        }
    }
    
    
    if ((head->x-poison_x<20 && poison_x-head->x<20)&&(head->y-poison_y<20 && poison_y-head->y<20)) {      //eat the poison
        poisonState = 0;
        setcolor(BLACK);
        setfillcolor(BLACK);
        fillcircle(poison_x,poison_y,radius);
        snakeCount--;
    }
    
    if ((head->x-bomb_x<20 && bomb_x-head->x<20)&&(head->y-bomb_y<20 && bomb_y-head->y<20)) {      //eat the food
        foodState = 0;
        setcolor(BLACK);
        setfillcolor(BLACK);
        fillcircle(food_x,food_y,radius);
        snakeCount++;
    }
    
    
}



