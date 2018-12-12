//
//  map1.c
//  Ã∞≥‘…ﬂ001
//
//  Created by macos on 2018/12/10.
//  Copyright ? 2018ƒÍ macos-gyc. All rights reserved.
//

#include "map1.h"
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#define Width 640
#define Height 640
#define distance 20
#define radius 10

int m;

extern char input;
extern char oldInput;
extern unsigned long seed;

int loopTime1 = 2;
int map1[2][2]={{480,320},{200,60}};  //a larger type of wall

int loopTime2 = 12;
int map2[12][2]={{280,180},{280,200},{280,220},{280,240},{280,260},{80,380},{100,380},{120,380},{320,40},{340,40},{400,420},{400,440}};

