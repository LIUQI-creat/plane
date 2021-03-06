#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
using namespace std;

#define high 20                      //宏定义游戏画布尺寸 
#define width 50
#define enemyNum 3                   //定义多台敌机 

int can[high][width]={0};            //定义二维数组 

int position_x,position_y;            //飞机位置 
char input;
int bullet_x,bullet_y;               //子弹位置 
int enemy_x[enemyNum],enemy_y[enemyNum] ;                 //敌机位置
int score ;                          //分数 
int bollet;                            //定义子弹宽度 


 
void startup() 
{
	position_x=high-3;                 //初始化飞机 
	position_y=width/2; 
	can[position_x][position_y]=1;
	
	
	int k;
	for(k=0;k<enemyNum;k++)
	{
	    enemy_x[k]=rand()%3 +1;                         //初始化敌机 
	    enemy_y[k]=rand()%width-1;
	    can[enemy_x[k]][enemy_y[k]]=3;		
    } 
	

	
	score = 0;                      //初始化分数=0 
	
	bollet = 16;                   //初始化子弹宽度 
}


 void gotoXY(int x,int y)    //光标定到x，y处 ,就不用一直清屏了 
 {
 	COORD pos ={x,y};
 	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos); 
  } 
  
void HideCursor()            //隐藏光标 
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}


void show()
{
	int i,j;
	HideCursor();
	gotoXY(0, 0);            //光标移到0，0处
	for(i=1;i<high;i++)
	{
		for(j=1;j<width;j++)
		{
			if(can[i][j]==1) cout<<"*";   //打印飞机 
			if(can[i][j]==0) cout<<" ";
			if(can[i][j]==2) cout<<"|";   //输出子弹  
			if(can[i][j]==3) cout<<"@";   //输出敌机 
		}
		cout<<endl;
	}
	cout<<"分数："<<score<<endl; 
 } 



void updateWithInput()
{
	if(kbhit())                             //当按键时执行 ！！！！！很重要，关系到游戏循环执行的时候不需要输入的操作的执行 
	{
		input = _getch();                  //不用按回车即可输入，asdw控制飞机位置 ,修改数组的值，便于输出。 
	    if(input=='a') 
		{
			can[position_x][position_y]=0;
			position_y--;
			can[position_x][position_y]=1;
		}
	    if(input=='s') 
		{
			can[position_x][position_y]=0;
			position_x++;
			can[position_x][position_y]=1;
		}
	    if(input=='w') 
		{
			can[position_x][position_y]=0;
			position_x--;
			can[position_x][position_y]=1;
		}
	    if(input=='d') 
	    {
	    	can[position_x][position_y]=0;
	    	position_y++;
	    	can[position_x][position_y]=1;
		}
	    if(input==' ')                      //空格输出子弹 
		{
			
			can[position_x-1][position_y]=2;
		}	
		if(input=='x')
		{
		    int left,right;
			left= position_y-bollet;
			if(left<0) left=0;
			right=position_y+bollet;
			if(right>width) right=width;
			int x;
			for(x=left;x<right;x++)
			can[position_x-1][x]=2;	
			
			
			
		} 
	    
	    
	}
}

void updateWithoutInput()
{
	int j,i,k;                            //遍历数组，找到子弹，进行改变 
	for(i=1;i<high;i++)
	{
		for(j=1;j<width;j++)
		{   
		    
		    
		        if(can[i][j]==2)            //击中敌机，直接生成新敌机 
			{   
			
			    for(k=0;k<enemyNum;k++) 
			    {
			    	if(i==enemy_x[k]&&j==enemy_y[k])
				    {
					    enemy_x[k]=1;
					    enemy_y[k]=rand()%width-1;
				 	    score ++; 
				    }	
				}
				
			can[i][j]=0;          //子弹上移 
			if(i>-1) 
			can[i-1][j]=2;	
			} 
						    
		}
	}
	
	static int speed=0;       //设置静态变量，控制敌机的下落速度 
	if(speed<10)
	speed++;
	if(speed==10)            //敌机下落 
	{
		int k;
		for(k=0;k<enemyNum;k++)
		{
			can[enemy_x[k]][enemy_y[k]]=0;
		    enemy_x[k]++;
		    can[enemy_x[k]][enemy_y[k]]=3;
		    speed =0;            //更改speed的值 
		}
    } 
    
    
    for(k=0;k<enemyNum;k++)
    {
        if(enemy_x[k]>high)              //敌机下落到底 ，生成新的敌机 
	 {
		enemy_x[k]=1;
		enemy_y[k]=rand()%width-1;
		score --;
	 }    	
	}

	
 } 
int main()
{
	startup();            //游戏初始化 
		 
		
	while (1)             //游戏循环执行 
	{
		show();           //页面展示 
		updateWithoutInput();    //与用户输入无关的操作 
		updateWithInput();      // 与用户输入有关的操作 
	    
	}
}
