# 课程设计报告书

## 1 选题：贪吃蛇

## 2 需求分析: 
* 为了让玩家与程序之间能够完成交互，设计不同**键盘输入**所对应的**不同响应**。
* 根据传统贪吃蛇的必备功能，设计**食物，毒草，炸弹以及智慧草**功能。  
其中，毒草一段时间后会自动消失，智慧草随机产生，吃下后可以自己寻找食物。
* 为了良好的用户体验，设计**实时计分，游戏说明，场景过渡，背景音乐以及特殊音效**。
* 为了及时保存进度，设计**存档读档**功能。其中，存档可以在游戏场景中进行，读档在选择游戏模式时进行。
* 为了让玩家拥有高分的成就感，设计**排行榜**功能。


## 3 系统设计
###（1）基本数据结构  
蛇身的每一个节点通过结构体完成实现，其定义如下:

    struct node{
     int x;
     int y;
     node *previous;
     node *next;
     };
x,y代表蛇每一个节点的x,y坐标，previous,next分别代表该蛇节点的上一节点和下一节点。  
通过查询每一个节点的属性，我们便可以获得该节点的在地图中以及在蛇身体中的位置。 

地图中每一个点的状态通过数组实现:

    int state[33][33]; 
    // 0--空  1--食物  2--毒草  3--炸弹  4--蛇身  5--智慧草  6--墙
这样，只需要判断蛇头坐标上的数值，便可以判断出小蛇所触发的事件

### (2) 接口描述
* 通过extern,static等关键字描述数据关系，从而实现不同文件中数据的调用。  
* 通过include相关头文件，来实现不同文件中函数的调用。
* 通过对键盘输入进行处理，实现用户与程序之间的连接。

## 4 界面设计
* 主界面吸收了Mojave 14.1 暗黑主题的设计经验，选取黑色作为底色，并将主题文字设计为深蓝色，给人以古典厚重之感。在高端大气上档次的同时，又不失低调奢华有内涵。  
* 在文字配色方面，使用了色彩学的相关知识。一方面，使用红色作为提醒颜色，以给人醒目感；另一方面，使用蓝色作为说明文字，不仅让人感到舒适，也能保护视力，不易感到疲劳。

## 5 系统实现

### （1）主函数（省略部分修饰性代码）

    int main() {
    initgraph(960,Height);     //画布初始化
    BeginBatchDraw();
    labelWelcome:welcomeMain();  //进入主页面
    if (gameState == 1){         //选择新游戏
    remoteLevel = 1;
    Game();
    }
    else if (gameState == 2){     // 选择读档
    if (loadStatus == 1){
     loadOut();
     Game();
     }
    else{                   
    outtextxy(360,310," 暂  时  没  有  存  档  ！");
    FlushBatchDraw();
    goto labelWelcome;
    } 
    }
    else if (gameState == 3){      //选择查看排行榜  
    rankListOpen();
    goto labelWelcome;
    }
    else if (gameState == 4)      //选择查看说明书
    {cleardevice(); goto labelWelcome;}
    goto labelWelcome;
    EndBatchDraw();
    closegraph();
    return 0;
    }
### （2）游戏函数（省略部分修饰性代码）
    void Game(){    
    if (gameState == 1) {newStartUp();}      //新游戏模式下的初始化
    else if (gameState == 2) {oldStartUp();} //读档模式下的初始化   

    while(1) {
    headMove();                            //蛇头移动
    if(snake_death == 1)                  //进行小蛇死亡判定
    goto labelGameover
    if (smartState == 1){            
    smartGrass();                    //进入智慧模式
    }

    if (foodState == 1 && poisonState == 1 && bombState == 1 )
    {···}
    else if (foodState == 0)
    {···}
    else if (poisonState == 0)
    {···}
    else if (bombState == 0)
    {···}

    sprintf(s,"%d",score);               //打印分数
    outtextxy(850,100,s);

    if (remoteLevel==2&&score >= 3000)   //升级进入第三关
    {
    goto labelGame3;
    }
    if (remoteLevel==1&&score >= 2000)   //升级进入第二关
    {
    goto labelGame2;
    }

    //设定每轮循环休眠时间
    if (remoteLevel == 1) Sleep(210/difficulty);
    else if (remoteLevel == 2) Sleep(180/difficulty);
    else if (remoteLevel == 3) Sleep(150/difficulty);

    preSnakeCount = snakeCount;
    seed++;

    FlushBatchDraw();
    }

    labelGameOver:FlushBatchDraw();
    rankList();                             //储存入排行榜
    gameOver();
    }


## 6 测试与调试
### 更新日志
1. 12-10 完成食物，毒草以及炸弹的设计
2. 12-12 完成智慧草的设计
3. 12-15 优化智慧草，修复bug
4. 12-17 完成地图的导入
5. 12-19 完成排行榜设计
6. 12-21 完成存档的设计
7. 12-22 修复读档异常的bug
8. 12-24 引入音效，优化场景衔接
9. 12-26 优化用户体验

### 调试工具
主要使用VC+6.0携带的debug工具 





