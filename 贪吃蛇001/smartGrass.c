//
//  smartGrass.c
//  Ã∞≥‘…ﬂ001
//
//  Created by macos on 2018/12/14.
//  Copyright ? 2018ƒÍ macos-gyc. All rights reserved.
//

#include "smartGrass.h"
#include "headMove.h"
#include "main.h"
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#define radius 9

extern int food_x,food_y;
extern int poison_x,poison_y;
extern int state[33][33];
extern int smartState;
extern int foodState;


extern node *head,*tail,*p1,*p2,*p3,*p;

extern char input;
extern char oldInput;
extern char smartDirection;
extern int difficulty;
extern int remoteLevel;
extern unsigned long seed;

void smartGrass()
{
    while(smartState == 1  && foodState == 1)
    {
        seed++;
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
        //****************************== Situation 0 ==****************************//
        if (state[head->x/20][head->y/20-1] == 1 )
        {smartDirection = 'w';headMove();}// moving up
        else if (state[head->x/20+1][head->y/20] == 1)
        {smartDirection = 'd';headMove();}// moving right
        else if (state[head->x/20-1][head->y/20] == 1)
        {smartDirection = 'a';headMove();}// moving left
        else if (state[head->x/20][head->y/20+1] == 1)
        {smartDirection = 's';headMove();}// moving down
        //****************************== Situation 1 ==****************************//
        else if (head->x==food_x&&head->y>food_y)       //food is up of the snake
        {
            if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'a')      // snake is moving  left
            {
                if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20-1][head->y/20] == 0 )
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else {break;}//pause,and wait for the user order
            }
        }
        //****************************== Situation 2 ==****************************//
        else if (head->x<food_x&&head->y>food_y)       //food is up and right of the snake
        {
            if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'a')      // snake is moving  left
            {
                if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20-1][head->y/20] == 0 )
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else {break;}//pause,and wait for the user order
            }
        }
        //****************************== Situation 3 ==****************************//
        else if (head->x<food_x&&head->y==food_y)       //food is right of the snake
        {
            if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'a')      // snake is moving  left
            {
                if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else {break;}//pause,and wait for the user order
            }
            
            else if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20-1][head->y/20] == 0 )
                {smartDirection = 'a';headMove();}// moving left
                else {break;}//pause,and wait for the user order
            }
        }
        //****************************== Situation 4 ==****************************//
        else if (head->x<food_x&&head->y<food_y)       //food is right and down of the snake
        {
            if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20-1][head->y/20] == 0 )
                {smartDirection = 'a';headMove();}// moving left
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'a')      // snake is moving  left
            {
                if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else {break;}//pause,and wait for the user order
            }
        }
        //****************************== Situation 5 ==****************************//
        else if (head->x==food_x&&head->y<food_y)       //food is down of the snake
        {
            if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20-1][head->y/20] == 0 )
                {smartDirection = 'a';headMove();}// moving left
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'a')      // snake is moving left
            {
                if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else {break;}//pause,and wait for the user order
            }
        }
        //****************************== Situation 6 ==****************************//
        else if (head->x>food_x&&head->y<food_y)       //food is left and down of the snake
        {
            if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20-1][head->y/20] == 0 )
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'a')      // snake is moving left
            {
                if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else {break;}//pause,and wait for the user order
            }
        }
        //****************************== Situation 7 ==****************************//
        else if (head->x>food_x&&head->y==food_y)       //food is left of the snake
        {
            if (oldInput == 'a')      // snake is moving left
            {
                if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20-1][head->y/20] == 0 )
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else {break;}//pause,and wait for the user order
            }
        }
        //****************************== Situation 8 ==****************************//
        else if (head->x>food_x&&head->y>food_y)       //food is left and up of the snake
        {
            if (oldInput == 'a')      // snake is moving left
            {
                if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20-1][head->y/20] == 0)
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20-1][head->y/20] == 0 )
                {smartDirection = 'a';headMove();}// moving left
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else {break;}//pause,and wait for the user order
            }
            else if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20][head->y/20-1] == 0 )
                {smartDirection = 'w';headMove();}// moving up
                else if (state[head->x/20][head->y/20+1] == 0)
                {smartDirection = 's';headMove();}// moving down
                else if (state[head->x/20+1][head->y/20] == 0)
                {smartDirection = 'd';headMove();}// moving right
                else {break;}//pause,and wait for the user order
            }
        }
        setcolor(YELLOW);
        setfillcolor(GREEN);
        fillcircle(head->x,head->y,radius);
        if (remoteLevel == 1) Sleep(210/difficulty);
        else if (remoteLevel == 2) Sleep(180/difficulty);
        else if (remoteLevel == 2) Sleep(150/difficulty);
        FlushBatchDraw();
    }
    smartState = 0;
    setcolor(YELLOW);
    setfillcolor(GREEN);
    fillcircle(head->x,head->y,radius);
    if (remoteLevel == 1) Sleep(210/difficulty);
    else if (remoteLevel == 2) Sleep(180/difficulty);
    else if (remoteLevel == 3) Sleep(150/difficulty);
    FlushBatchDraw();
}

