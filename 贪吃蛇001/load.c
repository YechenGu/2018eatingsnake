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

node *headLoad,*tailLoad,*p4,*p5,*p6;
node *bombFirstLoad,*bombLastLoad,*b4,*b5;

static int a;

void loadIn()                   //存入数据
{
    FILE *fp;
    fp = fopen(".\\load.txt", "w");    //向txt文件写入
    int i,j;
    p4 = (node *)malloc(sizeof(node));      //用来读取main的头
    fprintf(fp,"%d %d %d %d %d %d %d %d %d %d %d %d %d",score,food_x,food_y,poison_x,poison_y,smart_x,smart_y,foodState,poisonState,bombState,snakeCount,difficulty,remoteLevel);
    fclose(fp);
    fp = fopen(".\\load.txt", "a");    //向txt文件追加
    for (i=0; i<33; i++)
    {
        for (j=0; j<33; j++)
        {
            fprintf(fp, "%d",state[i][j]);
        }
    }
    fwrite(&head,sizeof(head),1,fp);
    for (p4=head; p4->next!=NULL; p4=p4->next)
    {fwrite(&p4->next,sizeof(p4->next),1,fp);}          //fwrite似乎只能存储地址，无法保存成员属性
    fwrite(&bombFirst,sizeof(bombFirst),1,fp);
    fwrite(&(bombFirst->next),sizeof(bombFirst->next),1,fp);
    fwrite(&bombLast,sizeof(bombLast),1,fp);
    fprintf(fp, "%c %c",oldInput,smartDirection);
    fprintf(fp, "%lu",seed);
    fclose(fp);
}



void loadOut()
{
    FILE *fp;
    fp = fopen(".\\load.txt", "r");     //从文件读出
    //**************=== 开始读取数据 ===**************//
    int i,j;
    fscanf(fp,"%d %d %d %d %d %d %d %d %d %d %d %d %d",&score,&food_x,&food_y,&poison_x,&poison_y,&smart_x,&smart_y,&foodState,&poisonState,&bombState, &snakeCount,&difficulty,&remoteLevel);
    fseek(fp, 0L, SEEK_CUR);
    for (i=0; i<33; i++)
    {
        for (j=0; j<33; j++)
        {
            fseek(fp, 0L, SEEK_CUR);
            fscanf(fp, "%d",&state[i][j]);
        }
    }
    fseek(fp, 0L, SEEK_CUR);
    fread(&head,sizeof(head),1,fp);             //fread似乎只能读出地址，读不出成员属性
    p4 = (node *)malloc(sizeof(node));
    p6 = (node *)malloc(sizeof(node));
    for (p4=head,p6=head->next; p6->next!=NULL; p4=p4->next,p6=p6->next)  //p4代表将要返回main函数的节点
    {
        fseek(fp, 0L, SEEK_CUR);
        p6 = (node *)malloc(sizeof(node));
        fread(&p6,sizeof(p6),1,fp);
        p4->next = p6;
        p6->previous = p4;
    }
    fseek(fp, 0L, SEEK_CUR);
    fread(&tail,sizeof(tail),1,fp);
    tail->previous = p6;
    tail->next = NULL;
    
    fseek(fp, 0L, SEEK_CUR);
    fread(&bombFirst,sizeof(bombFirst),1,fp);
    fseek(fp, 0L, SEEK_CUR);
    b4 = (node *)malloc(sizeof(node));
    fread(&b4,sizeof(b4),1,fp);
    bombFirst->next=b4;
    b4->previous=bombFirst;
    fseek(fp, 0L, SEEK_CUR);
    fread(&bombLast,sizeof(bombLast),1,fp);
    bombLast->previous = b4;
    b4->next = bombLast;
    b4->next = NULL;
    fseek(fp, 0L, SEEK_CUR);
    fscanf(fp, "%c %c",&oldInputLoad,&smartDirectionLoad);
    fseek(fp, 0L, SEEK_CUR);
    fscanf(fp, "ul",&seedLoad);
    loadStatus = 1;
    fclose(fp);
}
