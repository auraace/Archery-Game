#include <allegro.h>
#include <winalleg.h>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "Player.h"
#include "Arrow.h"
#include <time.h>
using namespace std;

void drawPath(double angle, int power, int scy, int scx,BITMAP *Buffer,BITMAP *background,Player &p1, Player &p2,int dir, int windv,BITMAP *FlagRight,BITMAP *FlagLeft);
void drawPathSeeker(double angle, int power, int scy, int scx,BITMAP *Buffer,BITMAP *background,Player &p1, Player &p2,int dir, int windv,BITMAP *FlagRight,BITMAP *FlagLeft);
void drawPathScatter(double angle, int power, int scy, int scx,BITMAP *Buffer,BITMAP *background,Player &p1, Player &p2,int dir, int windv,BITMAP *FlagRight,BITMAP *FlagLeft);
void drawPathRain(double angle, int power, int scy, int scx,BITMAP *Buffer,BITMAP *background,Player &p1, Player &p2,int dir, int windv,BITMAP *FlagRight,BITMAP *FlagLeft);
void setup();
void drawBitmaps(BITMAP *Buffer,BITMAP *background,Player p1, Player p2,BITMAP *FlagRight, BITMAP *FlagLeft);
void drawBitmaps(BITMAP *Buffer,BITMAP *background,Player p1, Player p2, Arrow a,BITMAP *FlagRight,BITMAP *FlagLeft);
bool collision(int x,int y,int w, int h,Player &p2);
//bool p1Turn(BITMAP *Buffer,BITMAP *background,Player &p1,Player &p2);
//bool p2Turn(BITMAP *Buffer,BITMAP *background,Player &p1,Player &p2);
bool p1TurnOnePlayer(BITMAP *Buffer,BITMAP *background,Player &p1,Player &p2,BITMAP *FlagRight,BITMAP *FlagLeft);
bool p1TurnTwoPlayer(BITMAP *Buffer,BITMAP *background,Player &p1,Player &p2,BITMAP *FlagRight,BITMAP *FlagLeft);
bool p2TurnOnePlayer(BITMAP *Buffer,BITMAP *background,Player &p1,Player &p2,BITMAP *FlagRight,BITMAP *FlagLeft);
bool p2TurnTwoPlayer(BITMAP *Buffer,BITMAP *background,Player &p1,Player &p2,BITMAP *FlagRight,BITMAP *FlagLeft);
int findAngle(double hv, double vv);
void removeBackgrounds(BITMAP *startP1, BITMAP *startP2,BITMAP *gameOver,BITMAP *FlagRight,BITMAP *FlagLeft);
void removeMenuBackground(BITMAP *menu);
double fRand(double fMin, double fMax);
int sign(double num1, double num2);
bool simulatePath(double angle, int power, int scy, int scx,BITMAP *Buffer,BITMAP *background,Player &p1, Player &p2,int dir, int windv,BITMAP *FlagRight,BITMAP *FlagLeft);
int getTreshold(Player &p);
bool menuSelect();

const int ScreenW=1366;
const int ScreenH=768;
const int scale=10;//scale between pixels and meters
const int MAXPOW=40;
//const int MAXPOW=60;
//const double MAXWINDSPEED=6.7;
//const double MINWINDSPEED=-6.7;
const double MAXWINDSPEED=30;
const double MINWINDSPEED=-30;
double wind;

int invintory1[3];
int quantity1[3];
int invintory2[3];
int quantity2[3];
int sizeI=3;

bool onePlayer;
int main(void)
{
	srand((unsigned)time(NULL));
	
	invintory1[0]=1;
	invintory1[1]=2;
	invintory1[2]=3;
	invintory2[0]=1;
	invintory2[1]=2;
	invintory2[2]=3;
	quantity1[0]=3;
	quantity1[1]=1;
	quantity1[2]=1;
	quantity2[0]=3;
	quantity2[1]=1;
	quantity2[2]=1;
	//quantity2=[3,1];
	
	int rand1,rand2;
	rand1=rand() % 350 + 50;
	rand2=(1366-50) - rand() % 350;
	bool gameOver=false;
	double angle;
	int power;
	//angle=1;
	//power=50;
	int x1,x2,y1,y2,dx,dy;
	setup();
	//char* stick[]="stick.bpm";
	Player p1(rand1,ScreenH-50-111/2,50,111,0);
	Player p2(rand2,ScreenH-50-111/2,50,111,1);
	p1.setUpBitmaps();
	p2.setUpBitmaps();
	p1.removeBackground();
	p2.removeBackground();
	BITMAP *Buffer = create_bitmap(ScreenW,ScreenH);
	BITMAP *background=NULL;
	background=load_bitmap("grassbg.bmp",NULL);
	BITMAP *startP1;
	BITMAP *startP2;
	startP1=load_bitmap("P1.bmp",NULL);
	startP2=load_bitmap("P2.bmp",NULL);
	BITMAP *menu;
	menu=load_bitmap("menu.bmp",NULL);
	BITMAP *Over;
	Over=load_bitmap("gameOver.bmp",NULL);
	int imagex=1366/2;
	int imagey=50;
	BITMAP *FlagRight;
	BITMAP *FlagLeft;
	FlagRight=load_bitmap("FlagRight.bmp",NULL);
	FlagLeft=load_bitmap("FlagLeft.bmp",NULL);
	removeMenuBackground(menu);
	removeBackgrounds(startP1,startP2,Over,FlagRight,FlagLeft);
	//blit(background,Buffer,0,0,0,0,ScreenW,ScreenH);
	//p2.drawPlayer(Buffer);
	drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagRight);
	masked_blit(menu,Buffer,0,0,358,269,650,230);
	blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
	//bool onePlayer=true;
	onePlayer = menuSelect();
	//textprintf_ex(screen,font,0,80,15,-1,"one player? %d",onePlayer);
	//Sleep(2000);
	while(!gameOver&&!key[KEY_ESC])
	{
		wind=fRand(MINWINDSPEED,MAXWINDSPEED);
		//wind=30;
		clear_bitmap(Buffer);
		drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
		
		masked_blit(startP1,Buffer,0,0,imagex-167/2,imagey,167,52);
		blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
		//
		//wind=rand() % int(2*MAXWINDSPEED)+MINWINDSPEED;
		if(onePlayer)
		{
			if(p1TurnOnePlayer(Buffer,background,p1,p2,FlagRight,FlagLeft))
			{			
				gameOver=true;
			}
		}
		else
		{
			if(p1TurnTwoPlayer(Buffer,background,p1,p2,FlagRight,FlagLeft))
			{			
				gameOver=true;
			}
		}
		
		//wind=rand() % int(2*MAXWINDSPEED)+MINWINDSPEED;
		wind=fRand(MINWINDSPEED,MAXWINDSPEED);
		//wind=30;
		if(!gameOver&&!key[KEY_ESC])
		{
			clear_bitmap(Buffer);
			drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
			masked_blit(startP2,Buffer,0,0,imagex-167/2,imagey,167,52);
			blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
			if(onePlayer)
			{
				//Sleep(750);
				if(p2TurnOnePlayer(Buffer,background,p1,p2,FlagRight,FlagLeft))
				{
					gameOver=true;
				}
			}
			else
			{
				if(p2TurnTwoPlayer(Buffer,background,p1,p2,FlagRight,FlagLeft))
				{
					gameOver=true;
				}
			}
			
		}
		clear_bitmap(Buffer);
		drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
		blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
	}
	masked_blit(Over,screen,5,0,imagex-930/2,imagey,930,350);
	while(!key[KEY_ESC]);
	allegro_exit();
	return 0;
}
END_OF_MAIN()

bool p1TurnOnePlayer(BITMAP *Buffer,BITMAP *background,Player &p1,Player &p2,BITMAP *FlagRight,BITMAP *FlagLeft)
{
	bool gameOver=false;
	double angle;
	int power;
	int x1,x2,y1,y2,dx,dy;
//	textprintf_ex(screen,font,0,10,15,-1,"p1's turn");
	bool inBounds=false;
	p1.setMoves(5);
	while(!gameOver && (!mouse_b&1 || !inBounds))
	{
		int x=p1.getX(),y=p1.getY(),width=p1.getWidth(),height=p1.getHeight();
		inBounds=mouse_x>x-width/2 && mouse_x<x+width/2 && mouse_y>y-height/2 && mouse_y<y+height/2;
		gameOver=key[KEY_ESC];
		if(key[KEY_D])
		{
			for(int i=0;i<10;i++)
			{
				p1.moveForeward();
				drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
				textprintf_ex(Buffer,font,0,0,15,-1,"",wind);
				textprintf_ex(screen,font,0,0,15,-1,"");
				blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
				clear_bitmap(Buffer);
				Sleep(20);
			}
			p1.setMoves(p1.getMoves()-1);
		}
		if(key[KEY_A])
		{
			for(int i=0;i<10;i++)
			{
				p1.moveBackward();
				drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
				textprintf_ex(Buffer,font,0,0,15,-1,"",wind);
				textprintf_ex(screen,font,0,0,15,-1,"");
				blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
				clear_bitmap(Buffer);
				Sleep(20);
			}
			p1.setMoves(p1.getMoves()-1);
		}
	}
	x1=mouse_x;
	y1=mouse_y;
	Sleep(500);
	p1.setActive(true);
	while(!mouse_b&1 && !gameOver)
	{
		int tpow=sqrt((mouse_x-x1)*(mouse_x-x1)+(y1-mouse_y)*(y1-mouse_y))/scale;
		int tempx=mouse_x-x1;
		int tempy=y1-mouse_y;
		p1.updateAngle(atan(double(tempy)/tempx));
		//blit(background,Buffer,0,0,0,0,ScreenW,ScreenH);
		//p2.drawPlayer(Buffer);
		drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
		//textprintf_ex(Buffer,font,0,10,15,-1,"power (max %i): %i, angle: %f",MAXPOW,tpow,atan(double(tempy)/tempx)*180/3.1415);
		textprintf_ex(Buffer,font,0,10,15,-1,"power (max %i): %i",MAXPOW,tpow);
		textprintf_ex(Buffer,font,0,0,15,-1,"",wind);
		line(Buffer,x1,y1,mouse_x,mouse_y,15);
		blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
		Sleep(50);
		clear_bitmap(Buffer);
		gameOver=key[KEY_ESC];
	}
	p1.setActive(false);
	x2=mouse_x;
	y2=mouse_y;
	dx=x1-x2;
	dy=y2-y1;
	//double tx=(double)dx;
	//double ty=(double)dy;
	double temp=1.0;
	temp=(double)dy/dx;
	angle=atan(temp);
	//textprintf_ex(screen,font,0,0,15,-1,"x1:%i, y1:%i, x2:%i, y2:%i, dx:%i, dy:%i, temp:%d, angle:%d",x1,y1,x2,y2,dx,dy,temp,angle);
	power=sqrt(dx*dx+dy*dy);
	power/=scale;
	if(power>MAXPOW)
	{
		power=MAXPOW;
	}
	//textprintf_ex(screen,font,0,10,15,-1,"The power is - %i the angle is - %d",power,angle);
	//angle+=1;
	clear_bitmap(Buffer);
	//blit(background,Buffer,0,0,0,0,ScreenW,ScreenH);
	//blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
	drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
	if(!gameOver)
	{
		drawPath(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,0,0,FlagRight,FlagLeft);
	}
	if(!(p1.getHealth()>0&&p2.getHealth()>0))
	{
		gameOver=true;
	}
	return gameOver;
}

bool p1TurnTwoPlayer(BITMAP *Buffer,BITMAP *background,Player &p1,Player &p2,BITMAP *FlagRight,BITMAP *FlagLeft)
{
	int curArrow=0;
	string names [sizeI];
	for(int n=0;n<sizeI;n++)
	{
		switch(invintory1[n])
		{
			case 1:
				names[n]="seek arrows";
				break;
			case 2:
				names[n]="scatter arrows";
				break;
			case 3:
				names[n]="rain arrows";
				break;
		}
	}
	textprintf_ex(screen,font,0,0,15,-1,"invintory: 1:%s(%i) 2:%s(%i) 3:%s(%i)",names[0].c_str(),quantity1[0],names[1].c_str(),quantity1[1],names[2].c_str(),quantity1[2]);
	
	bool gameOver=false;
	double angle;
	int power;
	int x1,x2,y1,y2,dx,dy;
//	textprintf_ex(screen,font,0,10,15,-1,"p1's turn");
	bool inBounds=false;
	p1.setMoves(5);
	while(!gameOver && (!mouse_b&1 || !inBounds))
	{
		int x=p1.getX(),y=p1.getY(),width=p1.getWidth(),height=p1.getHeight();
		inBounds=mouse_x>x-width/2 && mouse_x<x+width/2 && mouse_y>y-height/2 && mouse_y<y+height/2;
		gameOver=key[KEY_ESC];
		if(key[KEY_D])
		{
			for(int i=0;i<10;i++)
			{
				p1.moveForeward();
				drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
				textprintf_ex(screen,font,0,0,15,-1,"invintory: 1:%s(%i) 2:%s(%i) 3:%s(%i)",names[0].c_str(),quantity1[0],names[1].c_str(),quantity1[1],names[2].c_str(),quantity1[2]);
				textprintf_ex(Buffer,font,0,0,15,-1,"",wind);
				textprintf_ex(screen,font,0,0,15,-1,"");
				blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
				clear_bitmap(Buffer);
				Sleep(20);
			}
			p1.setMoves(p1.getMoves()-1);
		}
		if(key[KEY_A])
		{
			for(int i=0;i<10;i++)
			{
				p1.moveBackward();
				drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
				textprintf_ex(screen,font,0,0,15,-1,"invintory: 1:%s(%i) 2:%s(%i) 3:%s(%i)",names[0].c_str(),quantity1[0],names[1].c_str(),quantity1[1],names[2].c_str(),quantity1[2]);
				textprintf_ex(Buffer,font,0,0,15,-1,"",wind);
				textprintf_ex(screen,font,0,0,15,-1,"");
				blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
				clear_bitmap(Buffer);
				Sleep(20);
			}
			p1.setMoves(p1.getMoves()-1);
		}
		if(key[KEY_1]&&quantity1[0]>0)
		{
			curArrow=invintory1[0];
			//quantity1[0]--;
		}
		if(key[KEY_2]&&quantity1[1]>0)
		{
			curArrow=invintory1[1];
			//quantity1[1]--;
		}
		if(key[KEY_3]&&quantity1[2]>0)
		{
			curArrow=invintory1[2];
		}
	}
	
	/*switch(curArrow)
	{
		case 1:
			textprintf_ex(Buffer,font,0,0,15,-1,"currnet arrow: seek arrow");
			break;
		case 2:
			textprintf_ex(Buffer,font,0,0,15,-1,"currnet arrow: scatter arrow");
			break;
		default:
			textprintf_ex(Buffer,font,0,0,15,-1,"currnet arrow: normal arrow");
			break;
	}*/
	
	x1=mouse_x;
	y1=mouse_y;
	Sleep(500);
	p1.setActive(true);
	while(!mouse_b&1 && !gameOver)
	{
		int tpow=sqrt((mouse_x-x1)*(mouse_x-x1)+(y1-mouse_y)*(y1-mouse_y))/scale;
		int tempx=mouse_x-x1;
		int tempy=y1-mouse_y;
		p1.updateAngle(atan(double(tempy)/tempx));
		//blit(background,Buffer,0,0,0,0,ScreenW,ScreenH);
		//p2.drawPlayer(Buffer);
		drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
		//textprintf_ex(Buffer,font,0,10,15,-1,"power (max %i): %i, angle: %f",MAXPOW,tpow,atan(double(tempy)/tempx)*180/3.1415);
		textprintf_ex(Buffer,font,0,10,15,-1,"power (max %i): %i",MAXPOW,tpow);
		switch(curArrow)
		{
			case 1:
				textprintf_ex(Buffer,font,0,0,15,-1,"currnet arrow: seek arrow");
				break;
			case 2:
				textprintf_ex(Buffer,font,0,0,15,-1,"currnet arrow: scatter arrow");
				break;
			case 3:
				textprintf_ex(Buffer,font,0,0,15,-1,"currnet arrow: rain arrow");
				break;
			default:
				textprintf_ex(Buffer,font,0,0,15,-1,"currnet arrow: normal arrow");
				break;
		}
		textprintf_ex(Buffer,font,0,0,15,-1,"",wind);
		line(Buffer,x1,y1,mouse_x,mouse_y,15);
		blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
		Sleep(50);
		clear_bitmap(Buffer);
		gameOver=key[KEY_ESC];
	}
	p1.setActive(false);
	x2=mouse_x;
	y2=mouse_y;
	dx=x1-x2;
	dy=y2-y1;
	//double tx=(double)dx;
	//double ty=(double)dy;
	double temp=1.0;
	temp=(double)dy/dx;
	angle=atan(temp);
	//textprintf_ex(screen,font,0,0,15,-1,"x1:%i, y1:%i, x2:%i, y2:%i, dx:%i, dy:%i, temp:%d, angle:%d",x1,y1,x2,y2,dx,dy,temp,angle);
	power=sqrt(dx*dx+dy*dy);
	power/=scale;
	if(power>MAXPOW)
	{
		power=MAXPOW;
	}
	//textprintf_ex(screen,font,0,10,15,-1,"The power is - %i the angle is - %d",power,angle);
	//angle+=1;
	clear_bitmap(Buffer);
	//blit(background,Buffer,0,0,0,0,ScreenW,ScreenH);
	//blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
	drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
	if(!gameOver)
	{
		switch(curArrow)
		{
			case 1:
				drawPathSeeker(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,0,0,FlagRight,FlagLeft);
				quantity1[0]--;
				break;
			case 2:
				drawPathScatter(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,0,0,FlagRight,FlagLeft);
				quantity1[1]--;
				break;
			case 3:
				drawPathRain(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,0,0,FlagRight,FlagLeft);
				quantity1[2]--;
				break;
			default:
				drawPath(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,0,0,FlagRight,FlagLeft);
				break;
		}
		//drawPathScatter(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,0,0,FlagRight,FlagLeft);
	}
	if(!(p1.getHealth()>0&&p2.getHealth()>0))
	{
		gameOver=true;
	}
	return gameOver;
}

bool p2TurnOnePlayer(BITMAP *Buffer,BITMAP *background,Player &p1,Player &p2,BITMAP *FlagRight,BITMAP *FlagLeft)
{

	bool gameOver=false;
	double angle;
	int power;
	int x1,x2,y1,y2,dx,dy;
//	textprintf_ex(screen,font,0,10,15,-1,"p2's turn");
	bool inBounds=false;
	p2.setMoves(5);
	int randPower=rand() % 20 + 20;
	double randAngle=fRand(0.5236,1.0472);//in radians
	//textprintf_ex(screen,font,0,30,15,-1,"power (max %i): %i, angle: %f",MAXPOW,randPower,randAngle);
	//Sleep(500);
	bool AI_Path=simulatePath(randAngle,randPower,ScreenH,ScreenW,Buffer,background,p1,p2,1,0,FlagRight,FlagLeft);
	while(!AI_Path)
	{
		int randPower=rand() % 20 + 20;
		double randAngle=fRand(0.5236,1.0472);//in radians
		angle=randAngle;
		power=randPower;
		if(power>40)
		{
			
		}
		//AI_Path=simulatePath(randAngle,randPower,ScreenH,ScreenW,Buffer,background,p1,p2,1,0,FlagRight,FlagLeft);
		AI_Path=simulatePath(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,1,0,FlagRight,FlagLeft);
	}
	
	drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
	if(!gameOver)
	{
		drawPath(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,1,0,FlagRight,FlagLeft);
	}
	if(!(p1.getHealth()>0&&p2.getHealth()>0))
	{
		gameOver=true;
	}
	return gameOver;
}

bool p2TurnTwoPlayer(BITMAP *Buffer,BITMAP *background,Player &p1,Player &p2,BITMAP *FlagRight,BITMAP *FlagLeft)
{
	int curArrow=0;
	string names [sizeI];
	for(int n=0;n<sizeI;n++)
	{
		switch(invintory2[n])
		{
			case 1:
				names[n]="seek arrows";
				break;
			case 2:
				names[n]="scatter arrows";
				break;
			case 3:
				names[n]="rain arrows";
				break;
		}
	}
	textprintf_ex(screen,font,0,0,15,-1,"invintory: 1:%s(%i) 2:%s(%i) 3:%s(%i)",names[0].c_str(),quantity2[0],names[1].c_str(),quantity2[1],names[2].c_str(),quantity2[2]);
	

	bool gameOver=false;
	double angle;
	int power;
	int x1,x2,y1,y2,dx,dy;
//	textprintf_ex(screen,font,0,10,15,-1,"p2's turn");
	bool inBounds=false;
	p2.setMoves(5);
	while(!gameOver && (!mouse_b&1 || !inBounds))
	{
		int x=p2.getX(),y=p2.getY(),width=p2.getWidth(),height=p2.getHeight();
		inBounds=mouse_x>x-width/2 && mouse_x<x+width/2 && mouse_y>y-height/2 && mouse_y<y+height/2;
		gameOver=key[KEY_ESC];
		if(key[KEY_D])
		{
			for(int i=0;i<10;i++)
			{
				p2.moveBackward();
				drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
				textprintf_ex(screen,font,0,0,15,-1,"invintory: 1:%s(%i) 2:%s(%i) 3:%s(%i)",names[0].c_str(),quantity2[0],names[1].c_str(),quantity2[1],names[2].c_str(),quantity2[2]);
				textprintf_ex(Buffer,font,0,0,15,-1,"",wind);
				textprintf_ex(screen,font,0,0,15,-1,"");
				blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
				clear_bitmap(Buffer);
				Sleep(20);
			}
			p2.setMoves(p2.getMoves()-1);
		}
		if(key[KEY_A])
		{
			for(int i=0;i<10;i++)
			{
				p2.moveForeward();
				drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
				textprintf_ex(screen,font,0,0,15,-1,"invintory: 1:%s(%i) 2:%s(%i) 3:%s(%i)",names[0].c_str(),quantity2[0],names[1].c_str(),quantity2[1],names[2].c_str(),quantity2[2]);
				textprintf_ex(Buffer,font,0,0,15,-1,"",wind);
				textprintf_ex(screen,font,0,0,15,-1,"");
				blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
				clear_bitmap(Buffer);
				Sleep(20);
			}
			p2.setMoves(p2.getMoves()-1);
		}
		if(key[KEY_1]&&quantity2[0]>0)
		{
			curArrow=invintory2[0];
			//quantity1[0]--;
		}
		if(key[KEY_2]&&quantity2[1]>0)
		{
			curArrow=invintory2[1];
			//quantity1[1]--;
		}
		if(key[KEY_3]&&quantity2[2]>0)
		{
			curArrow=invintory2[2];
			//quantity1[1]--;
		}
	}
	x1=mouse_x;
	y1=mouse_y;
	Sleep(500);
	p2.setActive(true);
	while(!mouse_b&1 && !gameOver)
	{
		int tpow=sqrt((mouse_x-x1)*(mouse_x-x1)+(y1-mouse_y)*(y1-mouse_y))/scale;
		int tempx=x1-mouse_x;
		int tempy=y1-mouse_y;
		p2.updateAngle(atan(double(tempy)/tempx));
		//blit(background,Buffer,0,0,0,0,ScreenW,ScreenH);
		//p2.drawPlayer(Buffer);
		drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
		//textprintf_ex(Buffer,font,0,10,15,-1,"power (max %i): %i, angle: %f",MAXPOW,tpow,atan(double(tempy)/tempx)*180/3.1415);
		textprintf_ex(Buffer,font,0,10,15,-1,"power (max %i): %i",MAXPOW,tpow);
		textprintf_ex(Buffer,font,0,0,15,-1,"",wind);
		switch(curArrow)
		{
			case 1:
				textprintf_ex(Buffer,font,0,0,15,-1,"currnet arrow: seek arrow");
				break;
			case 2:
				textprintf_ex(Buffer,font,0,0,15,-1,"currnet arrow: scatter arrow");
				break;
			case 3:
				textprintf_ex(Buffer,font,0,0,15,-1,"currnet arrow: rain arrow");
				break;
			default:
				textprintf_ex(Buffer,font,0,0,15,-1,"currnet arrow: normal arrow");
				break;
		}
		line(Buffer,x1,y1,mouse_x,mouse_y,15);
		blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
		Sleep(50);
		clear_bitmap(Buffer);
		gameOver=key[KEY_ESC];
	}
	p2.setActive(false);
	x2=mouse_x;
	y2=mouse_y;
	dx=x2-x1;
	dy=y2-y1;
	//double tx=(double)dx;
	//double ty=(double)dy;
	double temp=1.0;
	temp=(double)dy/dx;
	angle=atan(temp);
	//textprintf_ex(screen,font,0,0,15,-1,"x1:%i, y1:%i, x2:%i, y2:%i, dx:%i, dy:%i, temp:%d, angle:%d",x1,y1,x2,y2,dx,dy,temp,angle);
	power=sqrt(dx*dx+dy*dy);
	power/=scale;
	if(power>MAXPOW)
	{
		power=MAXPOW;
	}
	//textprintf_ex(screen,font,0,10,15,-1,"The power is - %i the angle is - %d",power,angle);
	//textprintf_ex(screen,font,0,10,15,-1,"The power is - %i",power);
	//angle+=1;
	clear_bitmap(Buffer);
	//blit(background,Buffer,0,0,0,0,ScreenW,ScreenH);
	//blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
	drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
	if(!gameOver)
	{
		switch(curArrow)
		{
			case 1:
				drawPathSeeker(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,1,0,FlagRight,FlagLeft);
				quantity2[0]--;
				break;
			case 2:
				drawPathScatter(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,1,0,FlagRight,FlagLeft);
				quantity2[1]--;
				break;
			case 3:
				drawPathRain(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,1,0,FlagRight,FlagLeft);
				quantity2[2]--;
				break;
			default:
				drawPathRain(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,1,0,FlagRight,FlagLeft);
				break;
		}
		//drawPath(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,1,0,FlagRight,FlagLeft);
	}
	if(!(p1.getHealth()>0&&p2.getHealth()>0))
	{
		gameOver=true;
	}
	return gameOver;
}

void drawPath(double angle, int power, int scy, int scx,BITMAP *Buffer,BITMAP *background,Player &p1, Player &p2,int dir, int windv,BITMAP *FlagRight,BITMAP *FlagLeft)
{
	//textprintf_ex(screen,font,0,60,15,-1,"angle: %f, power: %i",angle, power);
	//Sleep(1000);
	if(power>41)
	{
		//int randPower=rand() % 20 + 20;
		//double randAngle=fRand(0.5236,1.0472);//in radians
		//textprintf_ex(screen,font,0,30,15,-1,"power (max %i): %i, angle: %f",MAXPOW,randPower,randAngle);
		//Sleep(500);
		//bool AI_Path=simulatePath(randAngle,randPower,ScreenH,ScreenW,Buffer,background,p1,p2,1,0,FlagRight,FlagLeft);
		bool AI_Path=false;
		int count=0;
		int randPower=0;
		double randAngle=0;	
		while(count<10&&!AI_Path)
		{
			while(!AI_Path)
			{
				Sleep(20);
				randPower=rand() % 20 + 20;
				randAngle=fRand(0.5236,1.0472);//in radians
				angle=randAngle;
				power=randPower;
				//AI_Path=simulatePath(randAngle,randPower,ScreenH,ScreenW,Buffer,background,p1,p2,1,0,FlagRight,FlagLeft);
				AI_Path=simulatePath(angle,power,ScreenH,ScreenW,Buffer,background,p1,p2,1,0,FlagRight,FlagLeft);
			}
			//textprintf_ex(screen,font,0,50,15,-1,"angle: %f, power: %i",randAngle, randPower);
			//Sleep(1000);
			count++;
		}
		
		if(power>41)
		{
			power=15;
			angle=.7;
		}
		
	}

	double ha,va;
	double ang=angle;
	int ang2;
	double temp=1.0;
	bool collide=false;
	double tint=0.03;
	double height=1,time=tint,hdis=0;
	int sx, sy=scy-50;
	double hv;
	if(dir==0)
	{
		sx=p1.getX()+p1.getWidth()/2;
		//hv=power*cos(angle)+wind;
		hv=power*cos(angle);
		
	}
	else
	{
		sx=p2.getX()-p2.getWidth()/2;
		//hv=power*cos(angle)-wind;
		hv=power*cos(angle);
	}
	double vv=power*sin(angle);
	int screenx,screeny;
	double vv2;
	height=p1.getHeight()/(2*scale);
	hdis=hv*time;
	clear_bitmap(Buffer);
	drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
	blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
	screeny=sy-(scale*height);
	if(dir==0)
	{
		screenx=sx+(scale*hdis);
	}
	else
	{
		screenx=sx-(scale*hdis);
	}
	Arrow a(screenx,screeny,60,6,dir);
	a.removeBackground();
	while(height>0&&!key[KEY_ESC]&&!collide)
	{	
		screeny=sy-(scale*height);
		if(dir==0)
		{
			screenx=sx+(scale*hdis);
		}
		else
		{
			screenx=sx-(scale*hdis);
		}
		clear_bitmap(Buffer);
		
		//wind=50;
		if(dir==0)
		{
			ha=sign(hv,wind)*(-.5*1.225*(hv+wind)*(hv+wind)*0.001963*0.04)/0.032;
		}
		else
		{
			ha=sign(hv,wind)*(-.5*1.225*(hv+wind)*(hv+wind)*0.001963*0.04)/0.032;
		}
		hdis=hdis+hv*tint+0.5*ha*tint*tint;
		hv=hv+ha*tint;
		
		
		va=(-.5*1.225*vv*vv*0.001963*0.04 + 0.032*-9.8)/0.032;
		height=height + vv*tint + 0.5*va*tint*tint;
		vv=vv+va*tint;
			
		drawBitmaps(Buffer,background,p1,p2,a,FlagRight,FlagLeft);
		//textprintf_ex(Buffer,font,0,30,15,-1,"power (max %i): %i, angle: %f",MAXPOW,power,angle);
			
		//textprintf_ex(Buffer,font,0,20,15,-1,"hv: %f",hv);
		a.updateArrow(screenx,screeny,atan(vv/hv));
		textprintf_ex(screen,font,0,10,15,-1,"");
		time+=tint;
		blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
		Sleep((tint*1000));
		if(time>1)
		{
			collide=collision(screenx,screeny,4,4,p1)||collision(screenx,screeny,4,4,p2);
		}
	}	
}

int sign(double num1, double num2)
{
	if(num1-num2>0)
	{
		return 1;
	}
	else if(num1-num2<0)
	{
		return -1;
	}
	return 0;
}

void setup()
{
	allegro_init();
	set_color_depth(24);
	set_gfx_mode(GFX_SAFE, ScreenW, ScreenH, 0 , 0);
	install_keyboard();
	install_mouse();
	show_mouse(screen);

}
void drawBitmaps(BITMAP *Buffer,BITMAP *background,Player p1, Player p2,BITMAP *FlagRight, BITMAP *FlagLeft)
{
	blit(background,Buffer,0,0,0,0,ScreenW,ScreenH);
	p1.drawPlayer(Buffer);
	p2.drawPlayer(Buffer);
	/*
	if(wind>0.0)
	{
		if(wind>3.0)
		{
			masked_blit(FlagRight,Buffer,0,0,ScreenW-155,0,100,75);
		}
		masked_blit(FlagRight,Buffer,0,0,ScreenW-100,0,100,75);
		//textprintf_ex(Buffer,font,0,30,15,-1,"flag right");
	}
	else
	{
		if(wind<-3.0)
		{
			masked_blit(FlagLeft,Buffer,0,0,ScreenW-155,0,100,75);
		}
		masked_blit(FlagLeft,Buffer,0,0,ScreenW-100,0,100,75);
		//textprintf_ex(Buffer,font,0,30,15,-1,"flag left");
	}*/
	if(wind>0.0)
	{
		if(wind>MAXWINDSPEED/2)
		{
			masked_blit(FlagRight,Buffer,0,0,ScreenW-155,0,100,75);
		}
		masked_blit(FlagRight,Buffer,0,0,ScreenW-100,0,100,75);
		//textprintf_ex(Buffer,font,0,30,15,-1,"flag right");
	}
	else
	{
		if(wind<MINWINDSPEED/2)
		{
			masked_blit(FlagLeft,Buffer,0,0,ScreenW-155,0,100,75);
		}
		masked_blit(FlagLeft,Buffer,0,0,ScreenW-100,0,100,75);
		//textprintf_ex(Buffer,font,0,30,15,-1,"flag left");
	}
}
void drawBitmaps(BITMAP *Buffer,BITMAP *background,Player p1, Player p2,Arrow a,BITMAP *FlagRight,BITMAP *FlagLeft)
{
	blit(background,Buffer,0,0,0,0,ScreenW,ScreenH);
	p1.drawPlayer(Buffer);
	p2.drawPlayer(Buffer);
	a.drawArrow(Buffer);
	/*
	if(wind>0.0)
	{
		if(wind>3.0)
		{
			masked_blit(FlagRight,Buffer,0,0,ScreenW-155,0,100,75);
		}
		masked_blit(FlagRight,Buffer,0,0,ScreenW-100,0,100,75);
		//textprintf_ex(Buffer,font,0,30,15,-1,"flag right");
	}
	else
	{
		if(wind<-3.0)
		{
			masked_blit(FlagLeft,Buffer,0,0,ScreenW-155,0,100,75);
		}
		masked_blit(FlagLeft,Buffer,0,0,ScreenW-100,0,100,75);
		//textprintf_ex(Buffer,font,0,30,15,-1,"flag left");
	}*/
	if(wind>0.0)
	{
		if(wind>MAXWINDSPEED/2)
		{
			masked_blit(FlagRight,Buffer,0,0,ScreenW-155,0,100,75);
		}
		masked_blit(FlagRight,Buffer,0,0,ScreenW-100,0,100,75);
		//textprintf_ex(Buffer,font,0,30,15,-1,"flag right");
	}
	else
	{
		if(wind<MINWINDSPEED/2)
		{
			masked_blit(FlagLeft,Buffer,0,0,ScreenW-155,0,100,75);
		}
		masked_blit(FlagLeft,Buffer,0,0,ScreenW-100,0,100,75);
		//textprintf_ex(Buffer,font,0,30,15,-1,"flag left");
	}
}
bool collision(int x,int y,int w, int h,Player &p2)
{
	int res;
	res=p2.collision(x,y,w,h);
	if(res==1)
	{
		textprintf_ex(screen,font,0,0,15,-1,"Headshot! Health: %i",p2.getHealth());
		return true;
	}
	if(res==2)
	{
		textprintf_ex(screen,font,0,0,15,-1,"Upper Body Shot! Health: %i",p2.getHealth());
		return true;
	}
	if(res==3)
	{
		textprintf_ex(screen,font,0,0,15,-1,"Lower Body Shot! Health: %i",p2.getHealth());
		return true;
	}
	return false;
}
int findAngle(double hv, double vv)
{
	double rang=atan(vv/hv);
	int dang=(int)(rang*180/3.1415);
	return dang;
}
void removeBackgrounds(BITMAP *startP1, BITMAP *startP2,BITMAP *gameOver,BITMAP *FlagRight,BITMAP *FlagLeft)
{
	int width=167;
	int height=52;
	int pink = makecol(255,0,255);
	int spec=70;
	for(int i=0;i<width;i++)
	{
		for(int j=0;j<height;j++)
		{
			if(getr(getpixel(startP1,i,j))>spec&&getg(getpixel(startP1,i,j))>spec&&getb(getpixel(startP1,i,j))>spec)
			{
				putpixel(startP1,i,j,pink);
			}
		}
	}
	for(int i=0;i<width;i++)
	{
		for(int j=0;j<height;j++)
		{
			if(getr(getpixel(startP2,i,j))>spec&&getg(getpixel(startP2,i,j))>spec&&getb(getpixel(startP2,i,j))>spec)
			{
				putpixel(startP2,i,j,pink);
			}
		}
	}
	spec=150;
	for(int i=0;i<930;i++)
	{
		for(int j=0;j<350;j++)
		{
			if(getr(getpixel(gameOver,i,j))<spec&&getg(getpixel(gameOver,i,j))<spec&&getb(getpixel(gameOver,i,j))<spec)
			{
				putpixel(gameOver,i,j,pink);
			}
		}
	}
	spec=248;
	for(int i=0;i<100;i++)
	{
		for(int j=0;j<75;j++)
		{
			if(getr(getpixel(FlagRight,i,j))>spec&&getg(getpixel(FlagRight,i,j))>spec&&getb(getpixel(FlagRight,i,j))>spec)
			{
				putpixel(FlagRight,i,j,pink);
			}
		}
	}
	for(int i=0;i<100;i++)
	{
		for(int j=0;j<75;j++)
		{
			if(getr(getpixel(FlagLeft,i,j))>spec&&getg(getpixel(FlagLeft,i,j))>spec&&getb(getpixel(FlagLeft,i,j))>spec)
			{
				putpixel(FlagLeft,i,j,pink);
			}
		}
	}
}
void removeMenuBackground(BITMAP *menu)
{
	int pink = makecol(255,0,255);
	for(int y=104;y<=126;y++)
	{
		for(int x=0;x<650;x++)
		{
			putpixel(menu,x,y,pink);
		}
	}
}
double fRand(double fMin, double fMax)
{
	
    double f = ((double)rand()) / RAND_MAX;
    return fMin + f * (fMax - fMin);
     
}
bool simulatePath(double angle, int power, int scy, int scx,BITMAP *Buffer,BITMAP *background,Player &p1, Player &p2,int dir, int windv,BITMAP *FlagRight,BITMAP *FlagLeft)
{
	double ha,va;
	double ang=angle;
	int ang2;
	double temp=1.0;
	bool collide=false;
	double tint=0.03;
	double height=1,time=tint,hdis=0;
	int sx, sy=scy-50;
	double hv;
	if(dir==0)
	{
		sx=p1.getX()+p1.getWidth()/2;
		//hv=power*cos(angle)+wind;
		hv=power*cos(angle);
		
	}
	else
	{
		sx=p2.getX()-p2.getWidth()/2;
		//hv=power*cos(angle)-wind;
		hv=power*cos(angle);
	}
	double vv=power*sin(angle);
	int screenx,screeny;
	double vv2;
	height=p1.getHeight()/(2*scale);
	hdis=hv*time;
	clear_bitmap(Buffer);
	drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
	blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
	screeny=sy-(scale*height);
	if(dir==0)
	{
		screenx=sx+(scale*hdis);
	}
	else
	{
		screenx=sx-(scale*hdis);
	}
	Arrow a(screenx,screeny,60,6,dir);
	a.removeBackground();
	while(height>0&&!key[KEY_ESC]&&!collide)
	{	
		screeny=sy-(scale*height);
		if(dir==0)
		{
			screenx=sx+(scale*hdis);
		}
		else
		{
			screenx=sx-(scale*hdis);
		}
		clear_bitmap(Buffer);
		
		//wind=50;
		if(dir==0)
		{
			ha=sign(hv,wind)*(-.5*1.225*(hv+wind)*(hv+wind)*0.001963*0.04)/0.032;
		}
		else
		{
			ha=sign(hv,wind)*(-.5*1.225*(hv+wind)*(hv+wind)*0.001963*0.04)/0.032;
		}
		hdis=hdis+hv*tint+0.5*ha*tint*tint;
		hv=hv+ha*tint;
		
		
		va=(-.5*1.225*vv*vv*0.001963*0.04 + 0.032*-9.8)/0.032;
		height=height + vv*tint + 0.5*va*tint*tint;
		vv=vv+va*tint;
			
		//drawBitmaps(Buffer,background,p1,p2,a,FlagRight,FlagLeft);
		textprintf_ex(Buffer,font,0,30,15,-1,"power (max %i): %i, angle: %f",MAXPOW,power,angle);
			
		//textprintf_ex(Buffer,font,0,20,15,-1,"hv: %f",hv);
		a.updateArrow(screenx,screeny,atan(vv/hv));
		textprintf_ex(screen,font,0,10,15,-1,"");
		time+=tint;
		//blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
		//Sleep((tint*1000));
		if(time>1)
		{
			//collide=collision(screenx,screeny,4,4,p1)||collision(screenx,screeny,4,4,p2);
		}
	}	
	/*
	double ha,va;
	double ang=angle;
	int ang2;
	double temp=1.0;
	bool collide=false;
	double tint=0.03;
	double height=1,time=tint,hdis=0;
	int sx, sy=scy-50;
	double hv;
	if(dir==0)
	{
		sx=p1.getX()+p1.getWidth()/2;
		//hv=power*cos(angle)+wind;
		hv=power*cos(angle);
		
	}
	else
	{
		sx=p2.getX()-p2.getWidth()/2;
		//hv=power*cos(angle)-wind;
		hv=power*cos(angle);
	}
	double vv=power*sin(angle);
	int screenx,screeny;
	double vv2;
	height=p1.getHeight()/(2*scale);
	hdis=hv*time;
	clear_bitmap(Buffer);

	//blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
	screeny=sy-(scale*height);
	if(dir==0)
	{
		screenx=sx+(scale*hdis);
	}
	else
	{
		screenx=sx-(scale*hdis);
	}
	Arrow a(screenx,screeny,60,6,dir);
	a.removeBackground();
	while(height>0&&!key[KEY_ESC]&&!collide)
	{	
		screeny=sy-(scale*height);
		if(dir==0)
		{
			screenx=sx+(scale*hdis);
		}
		else
		{
			screenx=sx-(scale*hdis);
		}
		clear_bitmap(Buffer);
		

		if(dir==0)
		{
			ha=sign(hv,wind)*(-.5*1.225*(hv+wind)*(hv+wind)*0.001963*0.04)/0.032;
		}
		else
		{
			ha=sign(hv,wind)*(-.5*1.225*(hv+wind)*(hv+wind)*0.001963*0.04)/0.032;
		}
		hdis=hdis+hv*tint+0.5*ha*tint*tint;
		hv=hv+ha*tint;
		
		
		va=(-.5*1.225*vv*vv*0.001963*0.04 + 0.032*-9.8)/0.032;
		height=height + vv*tint + 0.5*va*tint*tint;
		vv=vv+va*tint;
			
		//textprintf_ex(Buffer,font,0,20,15,-1,"hv: %f",hv);
		a.updateArrow(screenx,screeny,atan(vv/hv));
		textprintf_ex(screen,font,0,10,15,-1,"");
		time+=tint;
		
	}*/
	bool ret=false;
	int thresh=getTreshold(p2);
	
	int xPos=sx-(hdis*scale);
	//textprintf_ex(screen,font,0,40,15,-1,"x: %i, p1x: %i, error: %i, distance: %i",xPos, p1.getX(), abs(xPos-p1.getX()), hdis*scale);
	//Sleep(2000);
	//clear_bitmap(Buffer);
	//blit(background,Buffer,0,0,0,0,ScreenW,ScreenH);	
	//blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
	if(xPos<p1.getX()+thresh && xPos>p1.getX()-3*thresh)
	{
		ret=true;
		//textprintf_ex(screen,font,0,70,15,-1,"angle: %f, power: %i",angle, power);
		//Sleep(3000);
	}
	
	return ret;
}

int getTreshold(Player &p)
{
	int ret;
	int health=p.getHealth();
	if(health>4)
	{
		ret=200;
	}
	else if(health>2)
	{
		ret=150;
	}
	else
	{
		ret=100;
	}
	return ret;
}
bool menuSelect()
{
	bool ret;
	bool valid=false;
	while(!valid)
	{
		while(!mouse_b&1)
		{
			
		}
		int x=mouse_x;
		int y=mouse_y;
		if(x>358 && x<1008 && y>269 && y<499)
		{
			if(y<373)
			{
				valid=true;
				ret=true;
			}
			else if(y>395)
			{
				valid=true;
				ret=false;
			}
			
		}	
		//textprintf_ex(screen,font,0,90,15,-1,"x: %i, y: %i",x,y);
		//Sleep(2000);
	}
	return ret;
}

void drawPathSeeker(double angle, int power, int scy, int scx,BITMAP *Buffer,BITMAP *background,Player &p1, Player &p2,int dir, int windv,BITMAP *FlagRight,BITMAP *FlagLeft)
{
	
	int moves=1;

	double ha,va;
	double ang=angle;
	int ang2;
	double temp=1.0;
	bool collide=false;
	double tint=0.03;
	double height=1,time=tint,hdis=0;
	int sx, sy=scy-50;
	double hv;
	if(dir==0)
	{
		sx=p1.getX()+p1.getWidth()/2;
		//hv=power*cos(angle)+wind;
		hv=power*cos(angle);
		
	}
	else
	{
		sx=p2.getX()-p2.getWidth()/2;
		//hv=power*cos(angle)-wind;
		hv=power*cos(angle);
	}
	double vv=power*sin(angle);
	int screenx,screeny;
	double vv2;
	height=p1.getHeight()/(2*scale);
	hdis=hv*time;
	clear_bitmap(Buffer);
	drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
	blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
	screeny=sy-(scale*height);
	if(dir==0)
	{
		screenx=sx+(scale*hdis);
	}
	else
	{
		screenx=sx-(scale*hdis);
	}
	Arrow a(screenx,screeny,60,6,dir);
	a.removeBackground();
	while(height>0&&!key[KEY_ESC]&&!collide)
	{	
		screeny=sy-(scale*height);
		if(dir==0)
		{
			screenx=sx+(scale*hdis);
		}
		else
		{
			screenx=sx-(scale*hdis);
		}
		clear_bitmap(Buffer);
		
		//wind=50;
		if(dir==0)
		{
			ha=sign(hv,wind)*(-.5*1.225*(hv+wind)*(hv+wind)*0.001963*0.04)/0.032;
		}
		else
		{
			ha=sign(hv,wind)*(-.5*1.225*(hv+wind)*(hv+wind)*0.001963*0.04)/0.032;
		}
		hdis=hdis+hv*tint+0.5*ha*tint*tint;
		hv=hv+ha*tint;
		
		
		va=(-.5*1.225*vv*vv*0.001963*0.04 + 0.032*-9.8)/0.032;
		height=height + vv*tint + 0.5*va*tint*tint;
		vv=vv+va*tint;
		
		if(key[KEY_W] && moves>0)
		{
			vv+=7;
			//hv-=2;
			moves--;
		}
		else if(key[KEY_S] && moves>0)
		{
			vv-=5;
			//hv+=1;
			moves--;
		}
			
		drawBitmaps(Buffer,background,p1,p2,a,FlagRight,FlagLeft);
		//textprintf_ex(Buffer,font,0,30,15,-1,"power (max %i): %i, angle: %f",MAXPOW,power,angle);
			
		//textprintf_ex(Buffer,font,0,20,15,-1,"hv: %f",hv);
		a.updateArrow(screenx,screeny,atan(vv/hv));
		textprintf_ex(screen,font,0,10,15,-1,"");
		time+=tint;
		blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
		Sleep((tint*1000));
		if(time>1)
		{
			collide=collision(screenx,screeny,4,4,p1)||collision(screenx,screeny,4,4,p2);
		}
	}	
}

void drawPathScatter(double angle, int power, int scy, int scx,BITMAP *Buffer,BITMAP *background,Player &p1, Player &p2,int dir, int windv,BITMAP *FlagRight,BITMAP *FlagLeft)
{
	//new variables
	bool collide2=true;
	bool collide3=true;
	double height2=-1;
	double height3=-1;
	double vv2,va2,vv3,va3;
	bool split=false;
	Arrow a2(0,0,60,6,dir);
	a2.removeBackground();
	Arrow a3(0,0,60,6,dir);
	a3.removeBackground();
	int screenx2,screeny2,screenx3,screeny3;
	bool alive=true;
	bool alive2=true;
	bool alive3=true;
	
	double ha,va;
	double ang=angle;
	int ang2;
	double temp=1.0;
	bool collide=false;
	double tint=0.03;
	double height=1,time=tint,hdis=0;
	int sx, sy=scy-50;
	double hv;
	if(dir==0)
	{
		sx=p1.getX()+p1.getWidth()/2;
		//hv=power*cos(angle)+wind;
		hv=power*cos(angle);
		
	}
	else
	{
		sx=p2.getX()-p2.getWidth()/2;
		//hv=power*cos(angle)-wind;
		hv=power*cos(angle);
	}
	double vv=power*sin(angle);
	int screenx,screeny;
	height=p1.getHeight()/(2*scale);
	hdis=hv*time;
	clear_bitmap(Buffer);
	drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
	blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
	screeny=sy-(scale*height);
	if(dir==0)
	{
		screenx=sx+(scale*hdis);
	}
	else
	{
		screenx=sx-(scale*hdis);
	}
	Arrow a(screenx,screeny,60,6,dir);
	a.removeBackground();
	while(!key[KEY_ESC] && (height>0 || height2>0 || height3>0) && (!(collide && collide2 && collide3)))
	{
		if(!split && (hdis>(p2.getX()-p1.getX())/(2*scale)))
		{
			double tempA = a.getAngle();
			double angle2 = tempA + 0.2617;
			double angle3 = tempA - 0.2617;
			a2.updateArrow(screenx,screeny,angle2);
			a3.updateArrow(screenx,screeny,angle3);
			vv2=hv*tan(angle2);
			vv3=hv*tan(angle3);
			
			height2=height;
			height3=height;
			collide2=false;
			collide3=false;
			split=true;
		}
		
		

		screeny=sy-(scale*height);
		if(dir==0)
		{
			screenx=sx+(scale*hdis);
		}
		else
		{
			screenx=sx-(scale*hdis);
		}
	
			
		clear_bitmap(Buffer);

		if(dir==0)
		{
			ha=sign(hv,wind)*(-.5*1.225*(hv+wind)*(hv+wind)*0.001963*0.04)/0.032;
		}
		else
		{
			ha=sign(hv,wind)*(-.5*1.225*(hv+wind)*(hv+wind)*0.001963*0.04)/0.032;
		}
		hdis=hdis+hv*tint+0.5*ha*tint*tint;
		hv=hv+ha*tint;
		va=(-.5*1.225*vv*vv*0.001963*0.04 + 0.032*-9.8)/0.032;
		height=height + vv*tint + 0.5*va*tint*tint;
		vv=vv+va*tint;
		if(split)
		{
			screeny2=sy-(scale*height2);
			va2=(-.5*1.225*vv2*vv2*0.001963*0.04 + 0.032*-9.8)/0.032;
			height2=height2 + vv2*tint + 0.5*va2*tint*tint;
			vv2=vv2+va2*tint;
			screeny3=sy-(scale*height3);
			va3=(-.5*1.225*vv3*vv3*0.001963*0.04 + 0.032*-9.8)/0.032;
			height3=height3 + vv3*tint + 0.5*va3*tint*tint;
			vv3=vv3+va3*tint;
		}
		
		//drawBitmaps(Buffer,background,p1,p2,a,FlagRight,FlagLeft);
		drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
		//textprintf_ex(Buffer,font,0,30,15,-1,"power (max %i): %i, angle: %f",MAXPOW,power,angle);
			
		//textprintf_ex(Buffer,font,0,20,15,-1,"hv: %f",hv);
		if(alive)
		{
			a.drawArrow(Buffer);
			a.updateArrow(screenx,screeny,atan(vv/hv));
			if(time>0.5)
			{
				collide=collision(screenx,screeny,4,4,p1)||collision(screenx,screeny,4,4,p2);
			}
		}	
		if(split&&alive2)
		{
			a2.drawArrow(Buffer);
			a2.updateArrow(screenx,screeny2,atan(vv2/hv));
			if(time>0.5)
			{
				collide2=collision(screenx,screeny2,4,4,p1)||collision(screenx,screeny2,4,4,p2);
			}			
		}
		if(split&&alive3)
		{
			a3.drawArrow(Buffer);
			a3.updateArrow(screenx,screeny3,atan(vv3/hv));
			if(time>0.5)
			{
				collide3=collision(screenx,screeny3,4,4,p1)||collision(screenx,screeny3,4,4,p2);
			}
		}
		
		textprintf_ex(screen,font,0,10,15,-1,"");
		time+=tint;
		blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
		Sleep((tint*1000));
		/*
		if(time>.5)
		{
			if(alive)
			{
				
			}
			if(alive)
			
		}*/
		
		if(collide||height<0)
		{
			alive=false;
		}
		if(split && (collide2||height2<0))
		{
			alive2=false;
		}
		if(split && (collide3||height3<0))
		{
			alive3=false;
		}
	}	
}

void drawPathRain(double angle, int power, int scy, int scx,BITMAP *Buffer,BITMAP *background,Player &p1, Player &p2,int dir, int windv,BITMAP *FlagRight,BITMAP *FlagLeft)
{
	//new variables
	bool collide2=true;
	bool collide3=true;
	double height2=-1;
	double height3=-1;
	double hv2,ha2,hv3,ha3;
	double hdis2,hdis3;
	bool split=false;
	Arrow a2(0,0,60,6,dir);
	a2.removeBackground();
	Arrow a3(0,0,60,6,dir);
	a3.removeBackground();
	Arrow a4(0,0,60,6,dir);
	a4.removeBackground();
	int screenx2,screenx3;
	bool alive=true;
	bool alive2=true;
	bool alive3=true;
	// bool alive4=true;
	
	double ha,va;
	double ang=angle;
	int ang2;
	double temp=1.0;
	bool collide=false;
	double tint=0.03;
	double height=1,time=tint,hdis=0;
	int sx, sy=scy-50;
	double hv;
	if(dir==0)
	{
		sx=p1.getX()+p1.getWidth()/2;
		//hv=power*cos(angle)+wind;
		hv=power*cos(angle);
		
	}
	else
	{
		sx=p2.getX()-p2.getWidth()/2;
		//hv=power*cos(angle)-wind;
		hv=power*cos(angle);
	}
	double vv=power*sin(angle);
	int screenx,screeny;
	height=p1.getHeight()/(2*scale);
	hdis=hv*time;
	clear_bitmap(Buffer);
	drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
	blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
	screeny=sy-(scale*height);
	if(dir==0)
	{
		screenx=sx+(scale*hdis);
	}
	else
	{
		screenx=sx-(scale*hdis);
	}
	Arrow a(screenx,screeny,60,6,dir);
	a.removeBackground();
	while(!key[KEY_ESC] && (height>0) && (!(collide && collide2 && collide3)))
	{
		if(!split && key[KEY_S])
		{
			hv=0;
			vv=-10;
			double tempA = -.7853; //atan(vv/hv);
			double angle2 = tempA + 0.2617;
			double angle3 = tempA - 0.2617;
			a2.updateArrow(screenx,screeny,angle2);
			a3.updateArrow(screenx,screeny,angle3);
			//vv2=hv*tan(angle2);
			//vv3=hv*tan(angle3);
			//hv2=tan(angle2)/vv;
			//hv3=tan(angle3)/vv;
			hv2=5;
			hv3=-5;
			hdis2=hdis;
			hdis3=hdis;
			/*
			if(dir==0)
			{
				a3.setDir(1);
			}
			else
			{
				a3.setDir(0);
			}*/
			
			
			
			height2=height;
			height3=height;
			collide2=false;
			collide3=false;
			split=true;
		}
		
		

		screeny=sy-(scale*height);
		if(dir==0)
		{
			screenx=sx+(scale*hdis);
		}
		else
		{
			screenx=sx-(scale*hdis);
		}
	
			
		clear_bitmap(Buffer);

		if(dir==0)
		{
			ha=sign(hv,wind)*(-.5*1.225*(hv+wind)*(hv+wind)*0.001963*0.04)/0.032;
		}
		else
		{
			ha=sign(hv,wind)*(-.5*1.225*(hv+wind)*(hv+wind)*0.001963*0.04)/0.032;
		}
		hdis=hdis+hv*tint+0.5*ha*tint*tint;
		hv=hv+ha*tint;
		va=(-.5*1.225*vv*vv*0.001963*0.04 + 0.032*-9.8)/0.032;
		height=height + vv*tint + 0.5*va*tint*tint;
		vv=vv+va*tint;
		if(split)
		{
			/*
			screeny2=sy-(scale*height2);
			va2=(-.5*1.225*vv2*vv2*0.001963*0.04 + 0.032*-9.8)/0.032;
			height2=height2 + vv2*tint + 0.5*va2*tint*tint;
			vv2=vv2+va2*tint;
			screeny3=sy-(scale*height3);
			va3=(-.5*1.225*vv3*vv3*0.001963*0.04 + 0.032*-9.8)/0.032;
			height3=height3 + vv3*tint + 0.5*va3*tint*tint;
			vv3=vv3+va3*tint;*/
			
			if(dir==0)
			{
				screenx2=sx+(scale*hdis2);
				screenx3=sx+(scale*hdis3);
			}
			else
			{
				screenx3=sx-(scale*hdis3);
				screenx2=sx-(scale*hdis2);
			}
			hdis2=hdis2+hv2*tint+0.5*ha2*tint*tint;
			ha2=sign(hv2,wind)*(-.5*1.225*(hv2+wind)*(hv2+wind)*0.001963*0.04)/0.032;
			hv2=hv2+ha2*tint;
			hdis3=hdis3+hv3*tint+0.5*ha3*tint*tint;
			ha3=sign(hv3,wind)*(-.5*1.225*(hv3+wind)*(hv3+wind)*0.001963*0.04)/0.032;
			hv3=hv3+ha3*tint;
		}
		
		//drawBitmaps(Buffer,background,p1,p2,a,FlagRight,FlagLeft);
		drawBitmaps(Buffer,background,p1,p2,FlagRight,FlagLeft);
		//textprintf_ex(Buffer,font,0,30,15,-1,"power (max %i): %i, angle: %f",MAXPOW,power,angle);
			
		//textprintf_ex(Buffer,font,0,20,15,-1,"hv: %f",hv);
		if(alive)
		{
			a.drawArrow(Buffer);
			if(hv>=0)
			{
				a.updateArrow(screenx,screeny,atan(vv/hv));
			}
			else
			{
				a.updateArrow(screenx,screeny,atan(vv/hv)+3.1415);
			}			
			if(time>0.5)
			{
				collide=collision(screenx,screeny,4,4,p1)||collision(screenx,screeny,4,4,p2);
			}
		}	
		if(split&&alive2)
		{
			a2.drawArrow(Buffer);
			if(hv2>=0)
			{
				a2.updateArrow(screenx2,screeny,atan(vv/hv2));
			}
			else
			{
				a2.updateArrow(screenx2,screeny,atan(vv/hv2)+3.1415);
			}
			if(time>0.5)
			{
				collide2=collision(screenx2,screeny,4,4,p1)||collision(screenx2,screeny,4,4,p2);
			}			
		}
		if(split&&alive3)
		{
			a3.drawArrow(Buffer);
			if(hv3>=0)
			{
				a3.updateArrow(screenx3,screeny,atan(vv/hv3));
			}
			else
			{
				a3.updateArrow(screenx3,screeny,atan(vv/hv3)+3.1415);
			}
			if(time>0.5)
			{
				collide3=collision(screenx3,screeny,4,4,p1)||collision(screenx3,screeny,4,4,p2);
			}
		}
		
		textprintf_ex(screen,font,0,10,15,-1,"");
		time+=tint;
		blit(Buffer,screen,0,0,0,0,ScreenW,ScreenH);
		Sleep((tint*1000));
		/*
		if(time>.5)
		{
			if(alive)
			{
				
			}
			if(alive)
			
		}*/
		
		if(collide||height<0)
		{
			alive=false;
		}
		if(split && (collide2||height<0))
		{
			alive2=false;
		}
		if(split && (collide3||height<0))
		{
			alive3=false;
		}
	}	
}
/*
Image Links/Bibliography:
Backgrounnd:
https://sumedh.files.wordpress.com/2013/08/background.png
Stickfigure:
https://uxfactor.files.wordpress.com/2012/12/stick-figure1.jpg
Arrow:
https://pixabay.com/p-310675/?no_redirect
Health Bar:
https://www.pinterest.com/pin/261138478368421376/
Player Start Images:
http://sandbox.yoyogames.com/games/139927-block-rain
*/
