//
//  smartGrass.c
//  贪吃蛇001
//
//  Created by macos on 2018/12/14.
//  Copyright © 2018年 macos-gyc. All rights reserved.
//

#include "smartGrass.h"
#include "main.h"
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#define Width 640
#define Height 640
#define distance 20
#define radius 10

extern int food_x,food_y;
extern int state[32][32];


extern node *head,*tail,*p1,*p2,*p3,*p;

extern char input;
extern char oldInput;

void smartGrass()
{
    while(head->x!=food_x && head->y!=food_y)
    {
        //****************************== Situation 1 ==****************************//
        if (head->x==food_x&&head->y<food_y)       //food is up of the snake
        {
            if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'a')      // snake is moving  left
            {
                if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20-1][head->y/20] == 0 )
                {}// moving left
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else {}//pause,and wait for the user order
            }
        }
        //****************************== Situation 2 ==****************************//
        if (head->x<food_x&&head->y<food_y)       //food is up and right of the snake
        {
            if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'a')      // snake is moving  left
            {
                if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20-1][head->y/20] == 0 )
                {}// moving left
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else {}//pause,and wait for the user order
            }
        }
        //****************************== Situation 3 ==****************************//
        if (head->x<food_x&&head->y==food_y)       //food is right of the snake
        {
            if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'a')      // snake is moving  left
            {
                if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else {}//pause,and wait for the user order
            }
            
            else if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20-1][head->y/20] == 0 )
                {}// moving left
                else {}//pause,and wait for the user order
            }
        }
        //****************************== Situation 4 ==****************************//
        if (head->x<food_x&&head->y>food_y)       //food is right and down of the snake
        {
            if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20-1][head->y/20] == 0 )
                {}// moving left
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'a')      // snake is moving  left
            {
                if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else {}//pause,and wait for the user order
            }
        }
        //****************************== Situation 5 ==****************************//
        if (head->x==food_x&&head->y>food_y)       //food is down of the snake
        {
            if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20-1][head->y/20] == 0 )
                {}// moving left
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'a')      // snake is moving left
            {
                if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else {}//pause,and wait for the user order
            }
        }
        //****************************== Situation 6 ==****************************//
        if (head->x>food_x&&head->y>food_y)       //food is left and down of the snake
        {
            if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20-1][head->y/20] == 0 )
                {}// moving left
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'a')      // snake is moving left
            {
                if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else {}//pause,and wait for the user order
            }
        }
        //****************************== Situation 7 ==****************************//
        if (head->x>food_x&&head->y==food_y)       //food is left of the snake
        {
            if (oldInput == 'a')      // snake is moving left
            {
                if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20-1][head->y/20] == 0 )
                {}// moving left
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else {}//pause,and wait for the user order
            }
        }
        //****************************== Situation 8 ==****************************//
        if (head->x>food_x&&head->y==food_y)       //food is left and up of the snake
        {
            if (oldInput == 'a')      // snake is moving left
            {
                if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'w')      // snake is moving up
            {
                if (state[head->x/20-1][head->y/20] == 0)
                {}// moving left
                else if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 's')      // snake is moving down
            {
                if (state[head->x/20-1][head->y/20] == 0 )
                {}// moving left
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else {}//pause,and wait for the user order
            }
            else if (oldInput == 'd')      // snake is moving right
            {
                if (state[head->x/20][head->y/20+1] == 0 )
                {}// moving up
                else if (state[head->x/20][head->y/20-1] == 0)
                {}// moving down
                else if (state[head->x/20+1][head->y/20] == 0)
                {}// moving right
                else {}//pause,and wait for the user order
            }
        }
    }
}
