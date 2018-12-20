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
#define Width 640
#define Height 640
#define distance 20
#define radius 9
#define initScore 800

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
int scoreLoad;
int poison_xLoad,poison_yLoad;
int food_xLoad,food_yLoad;
int smart_xLoad,smart_yLoad;
int foodStateLoad;  //  依然存在食物
int poisonStateLoad;  // 依然存在毒草
int bombStateLoad;   // 依然存在炸弹
int snakeCountLoad;
int stateLoad[33][33];  // 0 -- empty  1 -- food 2 -- poison  3 -- bomb  4 -- snake  5 -- smartGrass  6 -- wall
int smartStateLoad;    // 0--没生成 1--进入智慧模式 2--已经生成还没吃
int difficultyLoad;
int remoteLevelLoad;

node *headLoad,*tailLoad,*p4,*p5,*p6;
node *bombFirstLoad,*bombLastLoad,*b4,*b5;
char oldInputLoad;
char smartDirectionLoad;     //智慧模式下的方向
unsigned long seedLoad;
static int a;


void loadIn()                   //存入数据
{
    FILE *fp;
    fp = fopen(".\\load.txt", "w");    //向txt文件写入
    scoreLoad = score;
    poison_xLoad = poison_x;
    poison_yLoad = poison_y;
    food_xLoad = food_x;
    food_yLoad = food_y;
    smart_xLoad = smart_x;
    smart_yLoad = smart_y;
    smartStateLoad = smartState;
    foodStateLoad = foodState;
    poisonStateLoad = poisonState;
    bombStateLoad = bombState;
    snakeCountLoad = snakeCount;
    difficultyLoad = difficulty;
    remoteLevelLoad = remoteLevel;
    int i,j;
    for (i=0; i<33; i++)
    {
        for (j=0; j<33; j++)
        {
            stateLoad[i][j] = state[i][j];
        }
    }
    
    //     保存蛇的身体
    headLoad = (node *)malloc(sizeof(node));
    headLoad->x = head->x;
    headLoad->y = head->y;
    headLoad->previous = NULL;
    headLoad->next = NULL;
    p4 = (node *)malloc(sizeof(node));      //用来读取main的头
    p6 = (node *)malloc(sizeof(node));      //用来存取存档的头
    p4=head->next;                          //获得main文件里面头之后的一个节点
    for (p6=headLoad; p4->next!=NULL; p4=p4->next,p6=p6->next)    //从头之后一节直到倒数第二节
    {
        p5 = (node *)malloc(sizeof(node));
        p5->x = p4->x;
        p5->y = p4->y;
        p5->previous = p6;
        p5->next=NULL;
        p6->next=p5;
    }
    tailLoad = (node *)malloc(sizeof(node));
    tailLoad->x = tail->x;
    tailLoad->y = tail->y;
    tailLoad->previous = p5;
    tailLoad->next = NULL;
    p5->next = tailLoad;
    
    //    保存炸弹
    bombFirstLoad = (node *)malloc(sizeof(node));
    bombFirstLoad->x = bombFirst->x;
    bombFirstLoad->y = bombFirst->y;
    bombFirstLoad->previous = NULL;
    bombFirstLoad->next = NULL;
    b5 = (node *)malloc(sizeof(node));
    b5->previous = bombFirstLoad;
    b5->next = NULL;
    b5->x = (bombFirst->next)->x;
    b5->y = (bombFirst->next)->y;
    bombFirstLoad->next = b5;
    bombLastLoad = (node *)malloc(sizeof(node));
    bombLastLoad->previous = b5;
    bombLastLoad->next = NULL;
    bombLastLoad->x = bombLast->x;
    bombLastLoad->y = bombLast->y;
    b5->next = bombLastLoad;
    
    
    oldInputLoad = oldInput;
    smartDirectionLoad = smartDirection;
    seedLoad = seed;
    fprintf(fp,"%d %d %d %d %d %d %d %d %d %d %d %d %d",scoreLoad,food_xLoad,food_yLoad,poison_xLoad,poison_yLoad,smart_xLoad,smart_yLoad,foodStateLoad,poisonStateLoad,bombStateLoad,snakeCountLoad,difficultyLoad,remoteLevelLoad);
    fclose(fp);
    fp = fopen(".\\load.txt", "a");    //向txt文件追加
    for (i=0; i<33; i++)
    {
        for (j=0; j<33; j++)
        {
            fprintf(fp, "%d",state[i][j]);
        }
    }
    fwrite(&headLoad,sizeof(headLoad),1,fp);
    for (p4=headLoad; p4->next!=NULL; p4=p4->next)     
    {fwrite(&p4->next,sizeof(p4->next),1,fp);}
    fwrite(&bombFirstLoad,sizeof(bombFirstLoad),1,fp);
    fwrite(&(bombFirstLoad->next),sizeof(bombFirstLoad->next),1,fp);
    fwrite(&bombLastLoad,sizeof(bombLastLoad),1,fp);
    fprintf(fp, "%c %c",oldInputLoad,smartDirectionLoad);
    fprintf(fp, "ul",seedLoad);
    fclose(fp);
}



void loadOut()
{
    FILE *fp;
    fp = fopen(".\\load.txt", "r");     //从文件读出
    //**************=== 开始读取数据 ===**************//
    int i,j;
    fscanf(fp,"%d %d %d %d %d %d %d %d %d %d %d %d %d",&scoreLoad,&food_xLoad,&food_yLoad,&poison_xLoad,&poison_yLoad,&smart_xLoad,&smart_yLoad,&foodStateLoad,&poisonStateLoad,&bombStateLoad,&snakeCountLoad,&difficultyLoad,&remoteLevelLoad);
    for (i=0; i<33; i++)
    {
        for (j=0; j<33; j++)
        {
            fscanf(fp, "%d",&stateLoad[i][j]);
        }
    }
    
    fread(&headLoad,sizeof(headLoad),1,fp);
    for (p4=headLoad; p4->next!=NULL; p4=p4->next)
    {p4 = (node *)malloc(sizeof(node));fread(&p4->next,sizeof(p4->next),1,fp);}
    fread(&bombFirstLoad,sizeof(bombFirstLoad),1,fp);
    fread(&(bombFirstLoad->next),sizeof(bombFirstLoad->next),1,fp);
    fread(&bombLastLoad,sizeof(bombLastLoad),1,fp);
    fscanf(fp, "%c %c",&oldInputLoad,&smartDirectionLoad);
    fscanf(fp, "ul",&seedLoad);
    
    //***************=== 结束读取数据 ===**************//
    score = scoreLoad;
    poison_x = poison_xLoad;
    poison_y = poison_yLoad;
    food_x = food_xLoad;
    food_y = food_yLoad;
    smart_x = smart_xLoad;
    smart_y = smart_yLoad;
    smartState = smartStateLoad;
    foodState = foodStateLoad;
    poisonState = poisonStateLoad;
    bombState = bombStateLoad;
    snakeCount = snakeCountLoad;
    difficulty = difficultyLoad;
    remoteLevel = remoteLevelLoad;
    loadStatus = 1;
    for (i=0; i<33; i++)
    {
        for (j=0; j<33; j++)
        {
            state[i][j] = stateLoad[i][j];
        }
    }
    
    //     读出蛇的身体
    head->x = headLoad->x;
    head->y = headLoad->y;
    head->previous=NULL;
    head->next=NULL;
    p6 = (node *)malloc(sizeof(node));
    for (p4=headLoad->next,p6=head; p4->next!=NULL; p4=p4->next,p6=p6->next)    //从头之后一节直到倒数第二节
    {
        p5 = (node *)malloc(sizeof(node));
        p5->previous = p6;
        p5->next=NULL;
        p5->x=p4->x;
        p5->y=p4->y;
        p6->next=p5;
    }
    tail->x = tailLoad->x;
    tail->y = tailLoad->y;
    tail->previous = p5;
    tail->next = NULL;
    p5->next = tail;
    
    //    读出炸弹
    bombFirstLoad = (node *)malloc(sizeof(node));
    b5 = (node *)malloc(sizeof(node));
    bombLastLoad = (node *)malloc(sizeof(node));
    bombFirst->x = bombFirstLoad->x;
    bombFirst->y = bombFirstLoad->y;
    bombFirst->previous = NULL;
    bombFirst->next = NULL;
    b5->previous = bombFirst;
    b5->next = NULL;
    b5->x = (bombFirstLoad->next)->x;
    b5->y = (bombFirstLoad->next)->y;
    bombFirst->next = b5;
    bombLast->previous = b5;
    bombLast->next = NULL;
    bombLast->x = bombLastLoad->x;
    bombLast->y = bombLastLoad->y;
    b5->next = bombLast;
    
    
    oldInput = oldInputLoad;
    smartDirection = smartDirectionLoad;
    seed = seedLoad ;
    fclose(fp);
}
