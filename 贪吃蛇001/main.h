//
//  main.h
//  贪吃蛇001
//
//  Created by macos on 2018/12/12.
//  Copyright © 2018年 macos-gyc. All rights reserved.
//

#ifndef main_h
#define main_h

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#define Width 640
#define Height 640
#define distance 20
#define radius 10
struct node
{
    int x;
    int y;
    node *previous;
    node *next;
};


#endif /* main_h */
