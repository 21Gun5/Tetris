//�ļ�����
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

//�궨��
#define FrameX 13       //��Ϸ�������Ͻǵ�x����
#define FrameY 3        //����y����
#define Frame_height 20     //��Ϸ���ڵĸ߶�
#define Frame_width 18     //��Ϸ���ڵĿ��

//����ȫ�ֱ���
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

//��������
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

//����������ɫ
int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
    return 0;
}

//��ȡ���λ��
void gotoxy(int x,int y)
{
     COORD pos;
     pos.X = x;
     pos.Y = y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

//����
void title()
{
     color(15);
     gotoxy(30,3);
     printf("�� �� ˹ �� ��\n");

     color(11);
     gotoxy(18,5);
     printf("��");
     gotoxy(18,6);
     printf("����");
     gotoxy(18,7);
     printf("��");

     color(14);
     gotoxy(26,6);
     printf("����");
     gotoxy(28,7);
     printf("����");

     color(10);
     gotoxy(36,6);
     printf("����");
     gotoxy(36,7);
     printf("����");

     color(13);
     gotoxy(45,5);
     printf("��");
     gotoxy(45,6);
     printf("��");
     gotoxy(45,7);
     printf("��");
     gotoxy(45,8);
     printf("��");

     color(12);
     gotoxy(56,6);
     printf("��");
     gotoxy(52,7);
     printf("������");

}

//װ��
void flower()
{
    color(5);
    gotoxy(65,19);
    printf("Just 4 CPra");
}

//�˵�ѡ��
void welcome()
{
    //�߿�
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

    //����
    color(12);
    gotoxy(25,12);
    printf("1.��ʼ��Ϸ");
    gotoxy(40,12);
    printf("2.����˵��");
    gotoxy(25,17);
    printf("3.��Ϸ����");
    gotoxy(40,17);
    printf("4.�˳�");
    color(3);
    gotoxy(21,22);
    printf("��ѡ��[1 2 3 4]:[ ]\b\b");
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
    ��ӡ�⼸���ֵ�˳�����Ҫ����Ӱ����ʾЧ������ð�������������
    ���ü����ϵ��ַ��Ͳ������뷨���������ַ���
*/
{
    //��Ϸ����
    gotoxy(FrameX+Frame_width-7,FrameY-2);
    color(11);
    printf("����˹����");
    //��һ���ַ���
    gotoxy(FrameX+2*Frame_width+3,FrameY+7);
    color(2);
    printf("**********");
    gotoxy(FrameX+2*Frame_width+13,FrameY+7);
    color(3);
    printf("��һ���ַ���");
    gotoxy(FrameX+2*Frame_width+3,FrameY+13);
    color(2);
    printf("**********");
    //��Ҫ����˵��
    gotoxy(FrameX+2*Frame_width+3,FrameY+15);
    color(14);
    printf("Esc:�˳���Ϸ");
    gotoxy(FrameX+2*Frame_width+3,FrameY+17);
    printf("����:��ת");
    gotoxy(FrameX+2*Frame_width+3,FrameY+19);
    printf("�ո���ͣ��Ϸ");
    //����ģ�
    a[FrameX][FrameY+Frame_height]=2;
    a[FrameX+2*Frame_width-2][FrameY+Frame_height]=2;
    //��Ϸ�߿�
    color(12);
    //���Ͽ��
    gotoxy(FrameX,FrameY);
    printf("+");
    //�ϱ߿�
    for(i=2;i<2*Frame_width-2;i+=2)
    {
        gotoxy(FrameX+i,FrameY);
        printf("-");
    }
    //���Ͽ��
    gotoxy(FrameX+2*Frame_width-2,FrameY);
    printf("+");
    //��ӡ������
    for(i=1;i<Frame_height;i++)
    {
        gotoxy(FrameX,FrameY+i);
        printf("|");
        a[FrameX][FrameY+i]=2;       //�����߿�Ϊ��Ϸ�߿򣬷�ֹ�������
    }
    //��ӡ�ұ߿�
    for(i=1;i<Frame_height;i++)
    {
        gotoxy(FrameX+2*Frame_width-2,FrameY+i);
        printf("|");
        a[FrameX+2*Frame_width-2][FrameY+i]=2;      //����ұ߿�Ϊ��Ϸ�߿򣬷�ֹ�������
    }
    //���¿��
    gotoxy(FrameX,FrameY+Frame_height);
    printf("+");
    //��ӡ�º��
    for(i=2;i<2*Frame_width-2;i+=2)
    {
        gotoxy(FrameX+i,FrameY+Frame_height);
        printf("-");
        a[FrameX+i][FrameY+Frame_height]=2;     //����º��Ϊ��Ϸ�߿򣬷�ֹ�������
    }
    //���¿��
    gotoxy(FrameX+2*Frame_width-2,FrameY+Frame_height);
    printf("+");
}
//������
int main(int argc, char *argv[])
{
    title();
    flower();
    welcome();
}
