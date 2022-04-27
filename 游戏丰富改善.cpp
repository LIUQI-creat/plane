#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
using namespace std;

#define high 20                      //�궨����Ϸ�����ߴ� 
#define width 50
#define enemyNum 3                   //�����̨�л� 

int can[high][width]={0};            //�����ά���� 

int position_x,position_y;            //�ɻ�λ�� 
char input;
int bullet_x,bullet_y;               //�ӵ�λ�� 
int enemy_x[enemyNum],enemy_y[enemyNum] ;                 //�л�λ��
int score ;                          //���� 
int bollet;                            //�����ӵ���� 


 
void startup() 
{
	position_x=high-3;                 //��ʼ���ɻ� 
	position_y=width/2; 
	can[position_x][position_y]=1;
	
	
	int k;
	for(k=0;k<enemyNum;k++)
	{
	    enemy_x[k]=rand()%3 +1;                         //��ʼ���л� 
	    enemy_y[k]=rand()%width-1;
	    can[enemy_x[k]][enemy_y[k]]=3;		
    } 
	

	
	score = 0;                      //��ʼ������=0 
	
	bollet = 16;                   //��ʼ���ӵ���� 
}


 void gotoXY(int x,int y)    //��궨��x��y�� ,�Ͳ���һֱ������ 
 {
 	COORD pos ={x,y};
 	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos); 
  } 
  
void HideCursor()            //���ع�� 
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}


void show()
{
	int i,j;
	HideCursor();
	gotoXY(0, 0);            //����Ƶ�0��0��
	for(i=1;i<high;i++)
	{
		for(j=1;j<width;j++)
		{
			if(can[i][j]==1) cout<<"*";   //��ӡ�ɻ� 
			if(can[i][j]==0) cout<<" ";
			if(can[i][j]==2) cout<<"|";   //����ӵ�  
			if(can[i][j]==3) cout<<"@";   //����л� 
		}
		cout<<endl;
	}
	cout<<"������"<<score<<endl; 
 } 



void updateWithInput()
{
	if(kbhit())                             //������ʱִ�� ��������������Ҫ����ϵ����Ϸѭ��ִ�е�ʱ����Ҫ����Ĳ�����ִ�� 
	{
		input = _getch();                  //���ð��س��������룬asdw���Ʒɻ�λ�� ,�޸������ֵ����������� 
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
	    if(input==' ')                      //�ո�����ӵ� 
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
	int j,i,k;                            //�������飬�ҵ��ӵ������иı� 
	for(i=1;i<high;i++)
	{
		for(j=1;j<width;j++)
		{   
		    
		    
		        if(can[i][j]==2)            //���ел���ֱ�������µл� 
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
				
			can[i][j]=0;          //�ӵ����� 
			if(i>-1) 
			can[i-1][j]=2;	
			} 
						    
		}
	}
	
	static int speed=0;       //���þ�̬���������Ƶл��������ٶ� 
	if(speed<10)
	speed++;
	if(speed==10)            //�л����� 
	{
		int k;
		for(k=0;k<enemyNum;k++)
		{
			can[enemy_x[k]][enemy_y[k]]=0;
		    enemy_x[k]++;
		    can[enemy_x[k]][enemy_y[k]]=3;
		    speed =0;            //����speed��ֵ 
		}
    } 
    
    
    for(k=0;k<enemyNum;k++)
    {
        if(enemy_x[k]>high)              //�л����䵽�� �������µĵл� 
	 {
		enemy_x[k]=1;
		enemy_y[k]=rand()%width-1;
		score --;
	 }    	
	}

	
 } 
int main()
{
	startup();            //��Ϸ��ʼ�� 
		 
		
	while (1)             //��Ϸѭ��ִ�� 
	{
		show();           //ҳ��չʾ 
		updateWithoutInput();    //���û������޹صĲ��� 
		updateWithInput();      // ���û������йصĲ��� 
	    
	}
}
