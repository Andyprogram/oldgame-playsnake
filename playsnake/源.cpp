/**********************************************
	项目描述：实现一个贪吃蛇
	文件描述：playsnake.cpp
	编译环境：vs2017
	创建日期：2019.10.19
***********************************************/
#include<graphics.h>	//图形库头文件
#include<conio.h>		//按键相关
#include<time.h>		//时间相关

#define MAX  1000   //蛇的最大节数
#define SIZE 20    //蛇的尺寸

struct COOR
{
	int x;
	int y;
};


enum CH
{
	up = 72,	 //键码值
	down = 80,
	left = 75,
	right = 77
};


//蛇类   结构体  自定义类型
struct SNAKE
{
	int n;  //蛇的节数
	COOR scr[MAX];  //蛇的坐标
	CH ch;  //蛇的方向
}snake;

//结构体学习
/*
struct PEOPLE                 尝试理解结构体
{
	int shenggao;
	char name[10];
	...
}Andy;

Andy.shenggao=180;

*/

//食物类
struct FOOD
{
	COOR fcr; //食物的坐标
	int flag; //食物是否生成的标志	0为需要生成食物  1为不需要生成食物
}food;

//绘制蛇
void SnakePaint()
{
	//蛇头
	setlinecolor(RGB(0, 0, 255));
	setfillcolor(RGB(255, 255, 255));
	fillrectangle(snake.scr[0].x, snake.scr[0].y, snake.scr[0].x + SIZE, snake.scr[0].y + SIZE);

	//蛇身
	for (int i = snake.n - 1; i > 0; i--)
	{
		setlinecolor(RGB(0, 0, 255));
		setfillcolor(RGB(255, 255, 255));
		fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + SIZE, snake.scr[i].y + SIZE);
	}

}

//初始化
void initGame()
{
	initgraph(640, 480);    //宽度：640    高度：480
	snake.n = 1;		//

	//数组下标是从0
	snake.scr[0].x = 0;
	snake.scr[0].y = 0;
	snake.ch = right;
	food.flag = 0;  //生成食物 0
}


//蛇的移动
void SnakeMove()
{
	for (int i = snake.n - 1; i > 0; i--)
	{
		snake.scr[i].x = snake.scr[i - 1].x;
		snake.scr[i].y = snake.scr[i - 1].y;
	}

	switch (snake.ch)
	{
	case up:
		snake.scr[0].y -= SIZE;
		break;
	case down:
		snake.scr[0].y += SIZE;
		break;
	case left:
		snake.scr[0].x -= SIZE;
		break;
	case right:
		snake.scr[0].x += SIZE;
		break;
	default:
		break;
	}

}

//控制蛇的方向
void ChangeSnakeCh()
{
	switch (getch())  //获取一个字符
	{
	case 72:	//上
		if (snake.ch != down)
			snake.ch = up;
		break;
	case 80:	//下
		if (snake.ch != up)
			snake.ch = down;
		break;
	case 75:	//左
		if (snake.ch != right)
			snake.ch = left;
		break;
	case 77:	//右
		if (snake.ch != left)
			snake.ch = right;
		break;
	default:
		break;
	}
}

//生成食物坐标
void FoodCoor()
{
	//随机数种子
	srand((unsigned)time(NULL));

	food.fcr.x = rand() % 32 * SIZE;	//0-31   20   0-620
	food.fcr.y = rand() % 24 * SIZE;	//0-23   20   0-460

	food.flag = 1;	//生成坐标以后先不生成食物
}

//绘制食物
void FoodPaint()
{
	setlinecolor(RGB(255, 0, 0));
	roundrect(food.fcr.x, food.fcr.y, food.fcr.x + SIZE, food.fcr.y + SIZE, 10, 10); //绘制圆角矩形

}

//吃食物
void EatFood()
{
	//表示蛇吃到了食物
	if (snake.scr[0].x == food.fcr.x&&snake.scr[0].y == food.fcr.y)
	{
		snake.n++;
		food.flag = 0;
	}
}


int judge()
{
	cleardevice();
	outtextxy(400, 400, "game over");
	Sleep(2000);
	exit(0);
}


//判断游戏输赢
void GameOver()
{
	//蛇头撞到了墙
	if (snake.scr[0].x < 0 || snake.scr[0].x>620 || snake.scr[0].y < 0 || snake.scr[0].y>460)
	{
		judge();
	}

	//蛇头撞到了蛇身
	for (int i = snake.n - 1; i > 0; i--)
	{
		if (snake.scr[i].x == snake.scr[0].x&&snake.scr[i].y == snake.scr[0].y)
		{
			judge();
		}
	}
}




//主函数，程序的入口
int main()
{
	
	initGame();
	while (1)	 
	{
		while (!kbhit())  //检测按键  当你按下按键 就退出循环
		{
			if (food.flag == 0)
				FoodCoor();
			cleardevice();//刷新屏幕
			FoodPaint();
			SnakeMove();
			SnakePaint();
			Sleep(200);  //200毫秒
			EatFood();
			GameOver();
			
		}
		ChangeSnakeCh();
	}
	return 0;
}