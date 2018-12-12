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

static int m;

extern char input;
extern char oldInput;
extern unsigned long seed;

int loopTime1 = 10;
int map1[10][2]={{475,315},{475,325},{485,315},{485,325},{185,55},{185,65},{195,55},{195,65},{205,55},{205,65}};  //center of the map

int loopTime2 = 50;
int map2[50][2];

for (m = 0;m < 20;m = m+2)
{
    map2[m][0] = 275;
    map2[m][1] = 175+5*m;
    map2[m+1][0] = 285;
    map2[m+1][1] = 175+5*m;
}
for (m = 20;m < 30;m += 2)
{
    map2[m] = {5*m-25,375};
    map2[m+1] = {5*m-25,385};
}
for (m=30;m<40;m+=2)
{
    map2[m] = {315+5*m,35};
    map2[m+1] = {315+5*m,45};
}
for (m=40;m<50;m+=2)
{
    map2[m] = {395,225+5*m};
    map2[m+1] = {405,225+5*m};
}

