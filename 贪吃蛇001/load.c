//
//  load.c
//  贪吃蛇001
//
//  Created by macos on 2018/12/18.
//  Copyright © 2018年 macos-gyc. All rights reserved.
//

#include "load.h"
#include "rankList.h"
#include "smartGrass.h"
#include "headMove.h"
#include "main.h"
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#define Width 640
#define Height 640
#define distance 20
#define radius 9

//**************=== 引用外部游戏需要被保存的数据 ===**************//
extern int score;
extern int poison_x,poison_y;
extern int food_x,food_y;
extern int smart_x,smart_y;
extern int foodState;  //  food remaining
extern int poisonState;  // poison remaining
extern int bombState;   // bomb remaining
extern int smartState;
extern int snakeCount;
extern char smartDirection;

extern node *head,*tail;
extern node *bombFirst,*bombLast;

extern char oldInput;
extern unsigned long seed;
extern int state[33][33];


//**************=== 数据存储变量 ===**************//
int scoreLoad;
int poison_xLoad,poison_yLoad;
int food_xLoad,food_yLoad;
int smart_xLoad,smart_yLoad;
int foodStateLoad;  //  依然存在食物
int poisonStateLoad;  // 依然存在毒草
int bombStateLoad;   // 依然存在炸弹
int snakeCountLoad;
int stateLoad[33][33];  // 0 -- empty  1 -- food 2 -- poison  3 -- bomb  4 -- snake or wall  5 -- smartGrass
int smartStateLoad;    // 0--没生成 1--进入智慧模式 2--已经生成还没吃


node *headLoad,*tailLoad,*p,*p2;
node *bombFirstLoad,*bombLastLoad,*b,*b2;
char oldInputLoad;
char smartDirectionLoad;     //智慧模式下的方向
unsigned long seedLoad;
int a;


void loadIn()                   //存入数据
{
    FILE *fp;
    fp = fopen(".\\load.txt", "w");    //向文件写入
    scoreLoad = score;
    poison_xLoad = poison_x;
    poison_yLoad = poison_y;
    food_xLoad = food_x;
    food_yLoad = food_y;
    smart_xLoad = smart_x;
    smart_yLoad = smart_y;
    foodStateLoad = foodState;
    poisonStateLoad = poisonState;
    bombStateLoad = bombState;
    snakeCountLoad = snakeCount;
    int i,j;
    for (i=0; i<33; i++)
    {
        for (j=0; j<33; j++)
        {
            stateLoad[i][j] = state[i][j];
        }
    }
    smartStateLoad = smartState;
    
    headLoad = head;
    for (p=head->next; p->next!=NULL; p=p->next)
    {
        p2 = (node *)malloc(sizeof(node));
        p2 = p;
    }
    tailLoad = tail;
    bombFirstLoad = bombFirst;
    bombFirstLoad->next = bombFirst->next;
    bombLastLoad = bombLast;
    
    
    oldInputLoad = oldInput;
    smartDirectionLoad = smartDirection;
    seedLoad = seed;
    fprintf(fp,"%d %d %d %d %d %d %d %d %d %d %d",scoreLoad,food_xLoad,food_yLoad,poison_xLoad,poison_yLoad,smart_xLoad,smart_yLoad,foodStateLoad,poisonStateLoad,bombStateLoad,snakeCountLoad);
    for (i=0; i<33; i++)
    {
        for (j=0; j<33; j++)
        {
            fprintf(fp, "%d",state[i][j]);
        }
    }
    fwrite(&headLoad,sizeof(headLoad),1,fp);
    for (p=headLoad; p->next!=NULL; p=p->next)
    {fwrite(&p->next,sizeof(p->next),1,fp);}
    fwrite(&bombFirstLoad,sizeof(bombFirstLoad),1,fp);
    fwrite(&(bombFirstLoad->next),sizeof(bombFirstLoad->next),1,fp);
    fwrite(&bombLastLoad,sizeof(bombLastLoad),1,fp);
    fprintf(fp, "%c %c",oldInputLoad,smartDirectionLoad);
    fprintf(fp, "ul",seedLoad);
    //有没有遗漏暂时就不想了
    fclose(fp);
}


void loadOut()
{
    
}
