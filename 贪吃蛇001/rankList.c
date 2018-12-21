//
//  rankList.c
//  贪吃蛇001
//
//  Created by macos on 2018/12/17.
//  Copyright © 2018年 macos-gyc. All rights reserved.
//  改变了radius的值，有一点小方

#include "rankList.h"
#include "smartGrass.h"
#include "headMove.h"
#include "main.h"
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib,"winmm.lib")
extern int score;
static int rank[5];
//统计排行榜，判断玩家是否能够进入排行榜
void rankList()
{
    FILE *fp;
    fp = fopen(".\\rank.txt", "r");                 //从文件读出，文件格式可以改变
    fscanf(fp,"%d %d %d %d %d",&rank[0],&rank[1],&rank[2],&rank[3],&rank[4]);   //后面的参数是接受文件数值的地址
    fclose(fp);
    int point,k,transmit,n;  //本次分数，计数变量，中转量，超过的量
    point = score;
    if (point > rank[4])
    {
        rank[4] = point;
        for(k=3;k>=0;k--)
        {
            if (point>rank[k])
            {
                transmit=rank[k];
                rank[k]=rank[k+1];
                rank[k+1]=transmit;
                n++;
            }
            else
                break;
        }
        
        fp = fopen(".\\rank.txt", "w");                     //向文件写入
        fprintf(fp,"%d %d %d %d %d",rank[0],rank[1],rank[2],rank[3],rank[4]);   //后面参数用于代表向文件写入的数值
        fclose(fp);
    }
}

//显示排行榜
void rankListOpen()
{
    FILE * fp;
    char sr[6];
    int e;
    fp = fopen(".\\rank.txt", "r");                 //从文件读出，文件格式可以改变
    fscanf(fp,"%d %d %d %d %d",&rank[0],&rank[1],&rank[2],&rank[3],&rank[4]);
    fclose(fp);
    settextstyle(30, 0, _T("宋体"));
    settextcolor(GREEN);
    outtextxy(300,90,"第一名");
    outtextxy(300,180,"第二名");
    outtextxy(300,270,"第三名");
    outtextxy(300,360,"第四名");
    outtextxy(300,450,"第五名");
    for (e = 0;e < 5;e++)
    {
        sprintf(sr,"%d",rank[e]);
        outtextxy(500,90*(e+1),sr);
    }
    outtextxy(280,560," 输 入 任 意 键 返 回 ");
    FlushBatchDraw();
    mciSendString("close dingdongmusic",NULL,0,NULL);
    mciSendString("open .\\dingdong.mp3 alias dingdongmusic",NULL,0,NULL);
    mciSendString("play dingdongmusic",NULL,0,NULL);
    Sleep(3000);
    getch();
    cleardevice();
}

