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
int bolletwidth;                            //定义子弹宽度 
int scoreSpeed ;                       //定义分数速度
int enemyboss;                         //定义敌机boss 
int vectory;                         //定义游戏胜利 

void plane(int position_x,int position_y ,int n)
{   int k;
	if(n==1)                                   //创建 
	{
		can[position_x][position_y]=1;
	    int left,right;
	    left =position_y-2;
	    if(left<0) left=0;
	    right= position_y+2;
	    if(right>width)
	    right=width;
	    for(k=left;k<=right;k++)
	    can[position_x+1][k]=1;
	    left = position_y-1;
	    if(left<0) left=0;
	    right=position_y+1;
	    if(right>width)
	    right=width;
	    can[position_x+2][left]=1;
	    can[position_x+2][right]=1;
	}
	else                                //清除 
	{                                    
		can[position_x][position_y]=0;
	    int left,right;
	    left =position_y-2;
	    if(left<0) left=0;
	    right= position_y+2;
	    if(right>width)
	    right=width;
	    for(k=left;k<=right;k++)
	    can[position_x+1][k]=0;
	    left = position_y-1;
	    if(left<0) left=0;
	    right=position_y+1;
	    if(right>width)
	    right=width;
	    can[position_x+2][left]=0;
	    can[position_x+2][right]=0;
	}
	
} 

void enemyPlane(int enemy_x,int enemy_y,int n)     
{   int k;                                            //创建复杂boss敌机 
	if(n==3)
	{
		can[enemy_x][enemy_y]=3;
		
		int left,right;
	    left =enemy_y-1;	    
	    right= enemy_y+1;	    
	    for(k=left;k<=right;k++)
	    can[enemy_x-1][k]=3;
	    
	    left =enemy_y-3;	    
	    right= enemy_y+3;	    
	    for(k=left;k<=right;k++)
	    can[enemy_x-2][k]=3;
	    
	    left =enemy_y-2;	    
	    right= enemy_y+2;	    
	    for(k=left;k<=right;k++)
	    can[enemy_x-3][k]=3;
	    can[enemy_x-3][enemy_y]=0;
	}
	else 
	{                                            //清除 
		can[enemy_x][enemy_y]=0;
				
		int left,right;
	    left =enemy_y-1;	    
	    right= enemy_y+1;	    
	    for(k=left;k<=right;k++)
	    can[enemy_x-1][k]=0;
	    
	    left =enemy_y-3;	    
	    right= enemy_y+3;	    
	    for(k=left;k<=right;k++)
	    can[enemy_x-2][k]=0;
	    
	    left =enemy_y-2;	    
	    right= enemy_y+2;	    
	    for(k=left;k<=right;k++)
	    can[enemy_x-3][k]=0;
	    can[enemy_x-3][enemy_y]=0;
	}
}
void startup() 
{   
    int k;
	position_x=high-3;                 //初始化复杂的飞机 
	position_y=width/2; 
	plane(position_x,position_y,1);
	
	
	
	for(k=0;k<enemyNum;k++)
	{
	    enemy_x[k]=rand()%3 +1;                         //初始化敌机 
	    enemy_y[k]=rand()%width-2;
	    can[enemy_x[k]][enemy_y[k]]=3;
    } 
		
	score = 0;                      //初始化分数=0 
	
	scoreSpeed=10;                  //初始化分数速度 
	
	bolletwidth=0;                  //初始化子弹宽度 
	 
	enemyboss=1;                    //初始化boss
	
	vectory=0;                      //初始化胜利结果 
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
	cout<<"分数："<<score<<endl;                    //输出游戏结果 
	if(vectory==1) 
	{
		cout<<"游戏胜利！"<<endl; 
		system("pause");
	}
	if(vectory==-1) 
	{
		cout<<"游戏失败！"<<endl; 
		system("pause");
	}
 } 



void updateWithInput()
{
	if(kbhit())                             //当按键时执行 ！！！！！很重要，关系到游戏循环执行的时候不需要输入的操作的执行 
	{
		input = _getch();                  //不用按回车即可输入，asdw控制飞机位置 ,修改数组的值，便于输出。 
	    if(input=='a') 
		{
			plane(position_x,position_y,0);
			position_y--;
			plane(position_x,position_y,1);
		}
	    if(input=='s') 
		{
			plane(position_x,position_y,0);
			position_x++;
			plane(position_x,position_y,1);
		}
	    if(input=='w') 
		{
			plane(position_x,position_y,0);
			position_x--;
			plane(position_x,position_y,1);
		}
	    if(input=='d') 
	    {
	    	plane(position_x,position_y,0);
	    	position_y++;
	    	plane(position_x,position_y,1);
		}
	    if(input==' ')                      //空格输出子弹 
		{
			int x;
			int left,right;
			left=position_y-bolletwidth;
			if(left<0) left=0;
			right=position_y+bolletwidth;
			if(right>width) right=width;
			for(x=left;x<=right;x++)
			can[position_x-1][x]=2;
		}	
		if(input=='x')                      //输入x放大招，清屏。 
		{
		    
			int x;
			for(x=0;x<width;x++)
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
		    
		    
		        if(can[i][j]==2)            
			{   
			
			    for(k=0;k<enemyNum;k++) 
			    {
			    	if(i==enemy_x[k]&&j==enemy_y[k])
				    {
					    score ++; 
				    	if(score%5==1&&scoreSpeed>5)
					   {   
					        scoreSpeed--;                       //随着分数的提高，敌机下落速度加快。
						}                                       
	                    if(score%10==1)  bolletwidth++;         //随分数增高，子弹宽度变宽。 
					    enemy_x[k]=1;
					    enemy_y[k]=rand()%width-1;              //击中敌机，直接生成新敌机 
				 	    
				    }
					
					
						
				}
				if(score>=50)
					{                                      //敌机boss有生命值，要多打几下 
						static int l=60;
						if(l==0) 
						{
							enemyPlane(5,width/2,0);
							enemyboss=0;
							vectory=1;                        //击败boss，游戏胜利 
						}
						else if(i==5&&j<=width/2+3&&j>=width/2-3)
						{
							l--;
						}
						
					}
			can[i][j]=0;          //子弹上移 
			if(i>-1) 
			can[i-1][j]=2;	
			} 
						    
		}
	}
	
	static int speed=0;       //设置静态变量，控制敌机的下落速度 
	if(speed<scoreSpeed)
	speed++;
	if(speed==scoreSpeed)            //敌机下落 
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
		enemy_y[k]=rand()%width-2;
		score --;
	 }
	    if(enemy_x[k]==position_x&&enemy_y[k]==position_y)      //敌机撞到飞机，减分数 ，生成新敌机 
		{
		    score--;
		    can[position_x][position_y]=1; 
			enemy_x[k]=1;
		    enemy_y[k]=rand()%width-2;	
		}    	
	}
	if(score>=50&&enemyboss==1) enemyPlane(5,width/2,3);    //分数到达高分，出现boss
    
    if(score<=-5) vectory=-1;                              //分数较低，游戏失败 
	
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
