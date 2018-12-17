//
//  rankList.c
//  贪吃蛇001
//
//  Created by macos on 2018/12/17.
//  Copyright © 2018年 macos-gyc. All rights reserved.
//

#include "rankList.h"

extern int score;
static int rank[5];
//统计排行榜，判断玩家是否能够进入排行榜
void rankList()
{
    int rank[5]={8000,6000,4000,2000,1000};
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
        FILE *fp;
        fp = fopen(".\\rank.rtf", "w");                     //向文件写入
        fprintf(fp,"%d %d %d %d %d",rank[0],rank[1],rank[2],rank[3],rank[4]);
        fclose(fp);
    }
}
    
    //显示排行榜
    void rankListOpen()
    {
        FILE * fp;
        char sr[6];
        int e;
        fp = fopen(".\\rank.rtf", "r");                 //从文件读入，文件格式可以改变
        fscanf(fp,"%d %d %d %d %d",&rank[0],&rank[1],&rank[2],&rank[3],&rank[4]);
        fclose(fp);
        settextcolor(BLUE);
        settextstyle(30.0,_T("黑体"));
        for (e = 0;e < 5;e++)
        {
            sprintf(sr,"%d",rank[e]);
            outtextxy(400,90*(e+1),sr);
        }
        outtextxy(300,600,“press any key to re~turn”);
        FlushBatchDraw();
        getch();
        cleardevice();
    }
    
