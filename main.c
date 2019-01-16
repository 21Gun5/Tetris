//文件引用
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

//宏定义
#define FrameX 13       //游戏窗口左上角的x坐标
#define FrameY 3        //……y坐标
#define Frame_height 20     //游戏窗口的高度
#define Frame_width 18     //游戏窗口的宽度

//定义全局变量
int i,j,Temp,Temp1,Temp2;
int a[80][80]={0};
int b[4];
struct Tetris
{
       int x;
       int y;
       int flag;
       int next;
       int speed;
       int number;
       int scorae;
       int level;
};
HANDLE hOut;

//函数声明
int color(int c);
void gotoxy(int x,int y);
void DrawGameframe();
void MakeTetris(struct Tetris *);
void PrintTetris(struct Tetris *);
void CleanTetris(struct Tetris *);
int ifMove(struct Tetris *);
void Del_Fullline(struct Tetris *);
void Gmaeplay();
void rugulation();
void welcome();
void Replay(struct Tetris * tetris);
void title();
void flower();
void close();

//设置文字颜色
int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
    return 0;
}

//获取光标位置
void gotoxy(int x,int y)
{
     COORD pos;
     pos.X = x;
     pos.Y = y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

//标题
void title()
{
     color(15);
     gotoxy(30,3);
     printf("俄 罗 斯 方 块\n");

     color(11);
     gotoxy(18,5);
     printf("■");
     gotoxy(18,6);
     printf("■■");
     gotoxy(18,7);
     printf("■");

     color(14);
     gotoxy(26,6);
     printf("■■");
     gotoxy(28,7);
     printf("■■");

     color(10);
     gotoxy(36,6);
     printf("■■");
     gotoxy(36,7);
     printf("■■");

     color(13);
     gotoxy(45,5);
     printf("■");
     gotoxy(45,6);
     printf("■");
     gotoxy(45,7);
     printf("■");
     gotoxy(45,8);
     printf("■");

     color(12);
     gotoxy(56,6);
     printf("■");
     gotoxy(52,7);
     printf("■■■");

}

//装饰
void flower()
{
    color(5);
    gotoxy(65,19);
    printf("Just 4 CPra");
}

//菜单选项
void welcome()
{
    //边框
    int n;
    int i,j=1;
    color(14);
    for(i=9;i<=20;i++)
    {
        for(j=15;j<=60;j++)
        {
            gotoxy(j,i);
            if(i==9||i==20) printf("=");
            else if(j==15||j==59) printf("||");
        }
    }

    //文字
    color(12);
    gotoxy(25,12);
    printf("1.开始游戏");
    gotoxy(40,12);
    printf("2.按键说明");
    gotoxy(25,17);
    printf("3.游戏规则");
    gotoxy(40,17);
    printf("4.退出");
    color(3);
    gotoxy(21,22);
    printf("请选择[1 2 3 4]:[ ]\b\b");
    color(14);
    scanf("%d",&n);
    switch(n)
    {
        case 1:
            system("cls");
            DrawGameframe();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
    }

}

void DrawGameframe()
/*
    打印这几部分的顺序很重要，会影响显示效果，最好按上下左右来；
    能用键盘上的字符就不用输入法带的特殊字符；
*/
{
    //游戏名称
    gotoxy(FrameX+Frame_width-7,FrameY-2);
    color(11);
    printf("俄罗斯方块");
    //下一出现方块
    gotoxy(FrameX+2*Frame_width+3,FrameY+7);
    color(2);
    printf("**********");
    gotoxy(FrameX+2*Frame_width+13,FrameY+7);
    color(3);
    printf("下一出现方块");
    gotoxy(FrameX+2*Frame_width+3,FrameY+13);
    color(2);
    printf("**********");
    //主要按键说明
    gotoxy(FrameX+2*Frame_width+3,FrameY+15);
    color(14);
    printf("Esc:退出游戏");
    gotoxy(FrameX+2*Frame_width+3,FrameY+17);
    printf("↑键:旋转");
    gotoxy(FrameX+2*Frame_width+3,FrameY+19);
    printf("空格：暂停游戏");
    //干嘛的？
    a[FrameX][FrameY+Frame_height]=2;
    a[FrameX+2*Frame_width-2][FrameY+Frame_height]=2;
    //游戏边框
    color(12);
    //左上框角
    gotoxy(FrameX,FrameY);
    printf("+");
    //上边框
    for(i=2;i<2*Frame_width-2;i+=2)
    {
        gotoxy(FrameX+i,FrameY);
        printf("-");
    }
    //右上框角
    gotoxy(FrameX+2*Frame_width-2,FrameY);
    printf("+");
    //打印左竖框
    for(i=1;i<Frame_height;i++)
    {
        gotoxy(FrameX,FrameY+i);
        printf("|");
        a[FrameX][FrameY+i]=2;       //标记左边框为游戏边框，防止方块出界
    }
    //打印右边框
    for(i=1;i<Frame_height;i++)
    {
        gotoxy(FrameX+2*Frame_width-2,FrameY+i);
        printf("|");
        a[FrameX+2*Frame_width-2][FrameY+i]=2;      //标记右边框为游戏边框，防止方块出界
    }
    //左下框角
    gotoxy(FrameX,FrameY+Frame_height);
    printf("+");
    //打印下横框
    for(i=2;i<2*Frame_width-2;i+=2)
    {
        gotoxy(FrameX+i,FrameY+Frame_height);
        printf("-");
        a[FrameX+i][FrameY+Frame_height]=2;     //标记下横框为游戏边框，防止方块出界
    }
    //右下框角
    gotoxy(FrameX+2*Frame_width-2,FrameY+Frame_height);
    printf("+");
}
//主函数
int main(int argc, char *argv[])
{
    title();
    flower();
    welcome();
}
