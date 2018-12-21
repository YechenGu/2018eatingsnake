//
//  load.c
//  贪吃蛇001
//
//  Created by macos on 2018/12/18.
//  Copyright © 2018年 macos-gyc. All rights reserved.
//

#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include "load.h"
#include "main.h"
#include "headMove.h"
#include "generate.h"
#include "map1.h"
#include "smartGrass.h"
#include "rankList.h"

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
extern int difficulty;
extern int remoteLevel;
extern int loadStatus;   // 存档状态

extern node *head,*tail;
extern node *bombFirst,*bombLast;

extern char oldInput;
extern unsigned long seed;
extern int state[33][33];


//**************=== 数据存储变量 ===**************//

node *p4,*p5,*p6;
node *b4,*b5;

static int a;

void loadIn()                   //存入数据
{
    FILE *fp;
    fp = fopen(".\\load.txt", "w");    //向txt文件写入
    int i,j;
    p4 = (node *)malloc(sizeof(node));      //用来读取main的头
    loadStatus = 1;
    fprintf(fp, "%d ",loadStatus);
    fprintf(fp,"%d %d %d %d %d %d %d %d %d %d %d %d %d ",score,food_x,food_y,poison_x,poison_y,smart_x,smart_y,foodState,poisonState,bombState,snakeCount,difficulty,remoteLevel);
    fclose(fp);
    fp = fopen(".\\load.txt", "a");    //向txt文件追加
    for (i=0; i<33; i++)
    {
        for (j=0; j<33; j++)
        {
            fprintf(fp, "%d ",state[i][j]);
        }
    }
    fprintf(fp, "%d %d ",head->x,head->y);
    for (p4=head->next; p4!=NULL; p4=p4->next)
    {fprintf(fp, "%d %d ",p4->x,p4->y);}          //fwrite似乎只能存储地址，无法保存成员属性
    fprintf(fp, "%d %d ",bombFirst->x,bombFirst->y);
    fprintf(fp, "%d %d ",(bombFirst->next)->x,(bombFirst->next)->y);
    fprintf(fp, "%d %d ",bombLast->x,bombLast->y);
    fprintf(fp, "%c %c ",oldInput,smartDirection);
    fprintf(fp, "%lu ",seed);
    fclose(fp);
}



void loadOut()
{
    FILE *fp;
    fp = fopen(".\\load.txt", "r");     //从文件读出
    //**************=== 开始读取数据 ===**************//
    int i,j;
    fscanf(fp, "%d ",&loadStatus);
    fseek(fp, 0L, SEEK_CUR);
    fscanf(fp,"%d %d %d %d %d %d %d %d %d %d %d %d %d ",&score,&food_x,&food_y,&poison_x,&poison_y,&smart_x,&smart_y,&foodState,&poisonState,&bombState, &snakeCount,&difficulty,&remoteLevel);
    for (i=0; i<33; i++)
    {
        for (j=0; j<33; j++)
        {
            fseek(fp, 0L, SEEK_CUR);
            fscanf(fp, "%d ",&state[i][j]);
        }
    }
    
    fseek(fp, 0L, SEEK_CUR);
    head = (node *)malloc(sizeof(node));
    fscanf(fp, "%d %d ",&head->x,&head->y);
    head->previous = NULL;
    head->next = NULL;
    p4 = (node *)malloc(sizeof(node));
    p6 = (node *)malloc(sizeof(node));
    for (i = 0,p4=head; i<snakeCount-2; i++,p4=p4->next)
    {
        fseek(fp, 0L, SEEK_CUR);
        p6 = (node *)malloc(sizeof(node));
        p4->next = p6;
        p6->previous = p4;
        p6->next = NULL;
        fscanf(fp, "%d %d ",&p6->x,&p6->y);
    }
    fseek(fp, 0L, SEEK_CUR);
    p5 = (node *)malloc(sizeof(node));
    p6->next = p5;
    p5->previous = p6;
    p5->next = NULL;
    fscanf(fp, "%d %d ",&p5->x,&p5->y);
    tail = p5;
    
    
    fseek(fp, 0L, SEEK_CUR);
    bombFirst = (node *)malloc(sizeof(node));
    fscanf(fp, "%d %d ",&bombFirst->x,&bombFirst->y);
    bombFirst->previous = NULL;
    bombFirst->next = NULL;
    
    fseek(fp, 0L, SEEK_CUR);
    b4 = (node *)malloc(sizeof(node));
    b4->previous = bombFirst;
    b4->next=NULL;
    bombFirst->next = b4;
    fscanf(fp, "%d %d ",&b4->x,&b4->y);
    
    fseek(fp, 0L, SEEK_CUR);
    bombLast = (node *)malloc(sizeof(node));
    b4->next = bombLast;
    bombLast->previous = b4;
    bombLast->next = NULL;
    fscanf(fp, "%d %d ",&bombLast->x,&bombLast->y);
    fseek(fp, 0L, SEEK_CUR);
    fscanf(fp, "%c %c ",&oldInput,&smartDirection);
    fseek(fp, 0L, SEEK_CUR);
    fscanf(fp, "%lu ",&seed);
    fclose(fp);
}
