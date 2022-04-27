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
int bolletwidth;                            //�����ӵ���� 
int scoreSpeed ;                       //��������ٶ�
int enemyboss;                         //����л�boss 
int vectory;                         //������Ϸʤ�� 

void plane(int position_x,int position_y ,int n)
{   int k;
	if(n==1)                                   //���� 
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
	else                                //��� 
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
{   int k;                                            //��������boss�л� 
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
	{                                            //��� 
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
	position_x=high-3;                 //��ʼ�����ӵķɻ� 
	position_y=width/2; 
	plane(position_x,position_y,1);
	
	
	
	for(k=0;k<enemyNum;k++)
	{
	    enemy_x[k]=rand()%3 +1;                         //��ʼ���л� 
	    enemy_y[k]=rand()%width-2;
	    can[enemy_x[k]][enemy_y[k]]=3;
    } 
		
	score = 0;                      //��ʼ������=0 
	
	scoreSpeed=10;                  //��ʼ�������ٶ� 
	
	bolletwidth=0;                  //��ʼ���ӵ���� 
	 
	enemyboss=1;                    //��ʼ��boss
	
	vectory=0;                      //��ʼ��ʤ����� 
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
	cout<<"������"<<score<<endl;                    //�����Ϸ��� 
	if(vectory==1) 
	{
		cout<<"��Ϸʤ����"<<endl; 
		system("pause");
	}
	if(vectory==-1) 
	{
		cout<<"��Ϸʧ�ܣ�"<<endl; 
		system("pause");
	}
 } 



void updateWithInput()
{
	if(kbhit())                             //������ʱִ�� ��������������Ҫ����ϵ����Ϸѭ��ִ�е�ʱ����Ҫ����Ĳ�����ִ�� 
	{
		input = _getch();                  //���ð��س��������룬asdw���Ʒɻ�λ�� ,�޸������ֵ����������� 
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
	    if(input==' ')                      //�ո�����ӵ� 
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
		if(input=='x')                      //����x�Ŵ��У������� 
		{
		    
			int x;
			for(x=0;x<width;x++)
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
		    
		    
		        if(can[i][j]==2)            
			{   
			
			    for(k=0;k<enemyNum;k++) 
			    {
			    	if(i==enemy_x[k]&&j==enemy_y[k])
				    {
					    score ++; 
				    	if(score%5==1&&scoreSpeed>5)
					   {   
					        scoreSpeed--;                       //���ŷ�������ߣ��л������ٶȼӿ졣
						}                                       
	                    if(score%10==1)  bolletwidth++;         //��������ߣ��ӵ���ȱ�� 
					    enemy_x[k]=1;
					    enemy_y[k]=rand()%width-1;              //���ел���ֱ�������µл� 
				 	    
				    }
					
					
						
				}
				if(score>=50)
					{                                      //�л�boss������ֵ��Ҫ����� 
						static int l=60;
						if(l==0) 
						{
							enemyPlane(5,width/2,0);
							enemyboss=0;
							vectory=1;                        //����boss����Ϸʤ�� 
						}
						else if(i==5&&j<=width/2+3&&j>=width/2-3)
						{
							l--;
						}
						
					}
			can[i][j]=0;          //�ӵ����� 
			if(i>-1) 
			can[i-1][j]=2;	
			} 
						    
		}
	}
	
	static int speed=0;       //���þ�̬���������Ƶл��������ٶ� 
	if(speed<scoreSpeed)
	speed++;
	if(speed==scoreSpeed)            //�л����� 
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
		enemy_y[k]=rand()%width-2;
		score --;
	 }
	    if(enemy_x[k]==position_x&&enemy_y[k]==position_y)      //�л�ײ���ɻ��������� �������µл� 
		{
		    score--;
		    can[position_x][position_y]=1; 
			enemy_x[k]=1;
		    enemy_y[k]=rand()%width-2;	
		}    	
	}
	if(score>=50&&enemyboss==1) enemyPlane(5,width/2,3);    //��������߷֣�����boss
    
    if(score<=-5) vectory=-1;                              //�����ϵͣ���Ϸʧ�� 
	
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
