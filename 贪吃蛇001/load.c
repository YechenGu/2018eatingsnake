//
//  load.c
//  贪吃蛇001
//
//  Created by macos on 2018/12/18.
//  Copyright © 2018年 macos-gyc. All rights reserved.
//

#include "load.h"
#include "main.h"
#include <graphics.h>
#include <stdlib.h>

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

node *headLoad,*tailLoad,*p,*p2,*p3;
node *bombFirstLoad,*bombLastLoad,*b,*b2;
char oldInputLoad;
char smartDirectionLoad;     //智慧模式下的方向
unsigned long seedLoad;
int a;


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
    headLoad = head;
    for (p=head->next,p3=headLoad; p->next!=NULL; p=p->next,p3=p3->next)    //从头之后一节直到倒数第二节
    {
        p2 = (node *)malloc(sizeof(node));
        p2->previous = p3;
        p2->next=NULL;
        p2->x=p->x;
        p2->y=p->y;
        p3->next=p2;
    }
    tailLoad->x = tail->x;
    tailLoad->y = tail->y;
    tailLoad->previous = p2;
    tailLoad->next = NULL;
    p2->next = tailLoad;
    
//    保存炸弹
    bombFirstLoad = bombFirst;
    b2->previous = bombFirstLoad;
    b2->next = NULL;
    b2->x = (bombFirst->next)->x;
    b2->y = (bombFirst->next)->y;
    bombFirstLoad->next = b2;
    bombLastLoad->previous = b2;
    bombLastLoad->next = NULL;
    bombLastLoad->x = bombLast->x;
    bombLastLoad->y = bombLast->y;
    b2->next = bombLastLoad;
    
    
    oldInputLoad = oldInput;
    smartDirectionLoad = smartDirection;
    seedLoad = seed;
    fprintf(fp,"%d %d %d %d %d %d %d %d %d %d %d" "%d" "%d",scoreLoad,food_xLoad,food_yLoad,poison_xLoad,poison_yLoad,smart_xLoad,smart_yLoad,foodStateLoad,poisonStateLoad,bombStateLoad,snakeCountLoad,difficultyLoad,remoteLevelLoad);
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
    fclose(fp);
}



void loadOut()
{
    FILE *fp;
    fp = fopen(".\\load.txt", "r");     //从文件读出
    //**************=== 开始读取数据 ===**************//
    int i,j;
    fscanf(fp,"%d %d %d %d %d %d %d %d %d %d %d" "%d" "%d",&scoreLoad,&food_xLoad,&food_yLoad,&poison_xLoad,&poison_yLoad,&smart_xLoad,&smart_yLoad,&foodStateLoad,&poisonStateLoad,&bombStateLoad,&snakeCountLoad,&difficultyLoad,&remoteLevelLoad);
    for (i=0; i<33; i++)
    {
        for (j=0; j<33; j++)
        {
            fscanf(fp, "%d",&stateLoad[i][j]);
        }
    }
    fread(&headLoad,sizeof(headLoad),1,fp);
    for (p=headLoad; p->next!=NULL; p=p->next)
    {fread(&p->next,sizeof(p->next),1,fp);}
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
    head = headLoad;
    for (p=headLoad->next,p3=head; p->next!=NULL; p=p->next,p3=p3->next)    //从头之后一节直到倒数第二节
    {
        p2 = (node *)malloc(sizeof(node));
        p2->previous = p3;
        p2->next=NULL;
        p2->x=p->x;
        p2->y=p->y;
        p3->next=p2;
    }
    tail->x = tailLoad->x;
    tail->y = tailLoad->y;
    tail->previous = p2;
    tail->next = NULL;
    p2->next = tail;
    
    //    读出炸弹
    bombFirst = bombFirstLoad;
    b2->previous = bombFirst;
    b2->next = NULL;
    b2->x = (bombFirstLoad->next)->x;
    b2->y = (bombFirstLoad->next)->y;
    bombFirst->next = b2;
    bombLast->previous = b2;
    bombLast->next = NULL;
    bombLast->x = bombLastLoad->x;
    bombLast->y = bombLastLoad->y;
    b2->next = bombLast;
    
    
    oldInput = oldInputLoad;
    smartDirection = smartDirectionLoad;
    seed = seedLoad ;
    fclose(fp);
}
