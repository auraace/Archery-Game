#include "Player.h"

Player::Player()
{
	xc=0;
	yc=0;
	width=0;
	height=0;
	player=NULL;
	health=6;
}

Player::Player(int x, int y, int w, int h, char *imgname,int d)
{
	xc=x;
	yc=y;
	width=w;
	height=h;
	top=yc-height/2;
	bottom=yc+height/2;
	left=xc-width/2;
	right=xc+width/2;
	strcpy (fileName,imgname);
	player=load_bitmap(fileName,NULL);
	health=6;
	dir=d;
	/*
	healthBar[0]=load_bitmap(NULL,NULL);
	healthBar[1]=load_bitmap("health1.bmp",NULL);
	healthBar[2]=load_bitmap("health2.bmp",NULL);
	healthBar[3]=load_bitmap("health3.bmp",NULL);
	healthBar[4]=load_bitmap("health4.bmp",NULL);
	healthBar[5]=load_bitmap("health5.bmp",NULL);
	healthBar[6]=load_bitmap("health6.bmp",NULL);
	*/
}

Player::Player(int x, int y, int w, int h,int d)
{
	xc=x;
	yc=y;
	width=w;
	height=h;
	top=yc-height/2;
	bottom=yc+height/2;
	left=xc-width/2;
	right=xc+width/2;
	player=load_bitmap("stick.bmp",NULL);
/*	healthBar[0]=load_bitmap(NULL,NULL);*/
	healthBar[1]=load_bitmap("health1.bmp",NULL);
	healthBar[2]=load_bitmap("health2.bmp",NULL);
	healthBar[3]=load_bitmap("health3.bmp",NULL);
	healthBar[4]=load_bitmap("health4.bmp",NULL);
	healthBar[5]=load_bitmap("health5.bmp",NULL);
	healthBar[6]=load_bitmap("health6.bmp",NULL);
	//bow=load_bitmap("bow.bmp",NULL);
	health=6;
	dir=d;
	moves=0;
	active=false;
	angle=0;
}
Player::~Player()
{
	
}

void Player::setUpBitmaps()
{
	if(dir==0)
	{
		playerBow[0]=load_bitmap("stick0[0].bmp",NULL);
		playerBow[1]=load_bitmap("stick0[5].bmp",NULL);
		playerBow[2]=load_bitmap("stick0[10].bmp",NULL);
		playerBow[3]=load_bitmap("stick0[15].bmp",NULL);
		playerBow[4]=load_bitmap("stick0[20].bmp",NULL);
		playerBow[5]=load_bitmap("stick0[25].bmp",NULL);
		playerBow[6]=load_bitmap("stick0[30].bmp",NULL);
		playerBow[7]=load_bitmap("stick0[35].bmp",NULL);
		playerBow[8]=load_bitmap("stick0[40].bmp",NULL);
		playerBow[9]=load_bitmap("stick0[45].bmp",NULL);
		playerBow[10]=load_bitmap("stick0[50].bmp",NULL);
		playerBow[11]=load_bitmap("stick0[55].bmp",NULL);
		playerBow[12]=load_bitmap("stick0[60].bmp",NULL);
		playerBow[13]=load_bitmap("stick0[65].bmp",NULL);
		playerBow[14]=load_bitmap("stick0[70].bmp",NULL);
		playerBow[15]=load_bitmap("stick0[75].bmp",NULL);
		playerBow[16]=load_bitmap("stick0[80].bmp",NULL);
		playerBow[17]=load_bitmap("stick0[85].bmp",NULL);
		playerBow[18]=load_bitmap("stick0[90].bmp",NULL);
	}
	else
	{
		playerBow[0]=load_bitmap("stick1[0].bmp",NULL);
		playerBow[1]=load_bitmap("stick1[5].bmp",NULL);
		playerBow[2]=load_bitmap("stick1[10].bmp",NULL);
		playerBow[3]=load_bitmap("stick1[15].bmp",NULL);
		playerBow[4]=load_bitmap("stick1[20].bmp",NULL);
		playerBow[5]=load_bitmap("stick1[25].bmp",NULL);
		playerBow[6]=load_bitmap("stick1[30].bmp",NULL);
		playerBow[7]=load_bitmap("stick1[35].bmp",NULL);
		playerBow[8]=load_bitmap("stick1[40].bmp",NULL);
		playerBow[9]=load_bitmap("stick1[45].bmp",NULL);
		playerBow[10]=load_bitmap("stick1[50].bmp",NULL);
		playerBow[11]=load_bitmap("stick1[55].bmp",NULL);
		playerBow[12]=load_bitmap("stick1[60].bmp",NULL);
		playerBow[13]=load_bitmap("stick1[65].bmp",NULL);
		playerBow[14]=load_bitmap("stick1[70].bmp",NULL);
		playerBow[15]=load_bitmap("stick1[75].bmp",NULL);
		playerBow[16]=load_bitmap("stick1[80].bmp",NULL);
		playerBow[17]=load_bitmap("stick1[85].bmp",NULL);
		playerBow[18]=load_bitmap("stick1[90].bmp",NULL);
	}
}

void Player::drawPlayer(BITMAP *Buffer)
{
	//masked_blit(player,Buffer,0,0,left,top,50,111);
	bool inBounds;
	inBounds=angle>=0&&angle<=90;
	if(active&&inBounds)
	{
		masked_blit(playerBow[angle/5],Buffer,0,0,left,top,50,111);
	}
	else
	{
		masked_blit(playerBow[0],Buffer,0,0,left,top,50,111);
	}
	if(health>0)
	{
		//textprintf_ex(Buffer,font,0,40,15,-1,"health bar should be %i full and at %i, %i",health,left,healthY);
		//line(Buffer,left,healthY,left+100,healthY,15);
		masked_blit(healthBar[health],Buffer,0,0,left-25,top-height/2,100,39);
	}	
	//masked_blit(bow,Buffer,0,0,right,top-height/2,100,140);
}

void Player::drawHitbox(BITMAP *Buffer)
{
	rectfill(Buffer,left,top,right,bottom,15);
}
void Player::removeBackground()
{
	int pink = makecol(255,0,255);
	int spec=100;
	for(int i=0;i<width;i++)
	{
		for(int j=0;j<height;j++)
		{
			if(getr(getpixel(player,i,j))>spec&&getg(getpixel(player,i,j))>spec&&getb(getpixel(player,i,j))>spec)
			{
				putpixel(player,i,j,pink);
			}
		}
	}
	spec=150;
	for(int n=0;n<19;n++)
	{
		for(int i=0;i<width;i++)
		{
			for(int j=0;j<height;j++)
			{
				if(getr(getpixel(playerBow[n],i,j))>spec&&getg(getpixel(playerBow[n],i,j))>spec&&getb(getpixel(playerBow[n],i,j))>spec)
				{
					putpixel(playerBow[n],i,j,pink);
				}
			}
		}
	}
	spec=100;
	/**/
	for(int n=1;n<health+1;n++)
	{
		for(int i=0;i<100;i++)
		{
			for(int j=0;j<39;j++)
			{
				if(getr(getpixel(healthBar[n],i,j))>spec&&getg(getpixel(healthBar[n],i,j))>spec&&getb(getpixel(healthBar[n],i,j))>spec)
				{
					putpixel(healthBar[n],i,j,pink);
				}
			}
		}
	}
	
	/*
	for(int i=0;i<654;i++)
	{
		for(int j=0;j<280;j++)
		{
			if(getr(getpixel(bow,i,j))>spec&&getg(getpixel(bow,i,j))>spec&&getb(getpixel(bow,i,j))>spec)
			{
				putpixel(bow,i,j,pink);
			}
		}
	}
	*/
}
int Player::collision(int x,int y,int w,int h)
{
	//for debugging purposes
	if(key[KEY_SPACE])
	{	
		textprintf_ex(screen,font,0,0,15,-1,"The ball's left is %i, The ball's right is %i, The ball's top is %i, the ball's bottom is %i."
		,x-w/2,x+w/2,y-h/2,y+h/2);
		textprintf_ex(screen,font,0,10,15,-1,"The player's left is %i, the player's right is %i, the player's top is %i, the player's bottom is %i."
		,left,right,top,bottom);
		if(right>x-w/2)
		{
			textprintf_ex(screen,font,0,20,15,-1,"true");
		}
		if(left<x+w/2)
		{
			textprintf_ex(screen,font,0,30,15,-1,"true");
		}
		if(bottom>y-h/2)
		{
			textprintf_ex(screen,font,0,40,15,-1,"true");
		}
		if(top<y+h/2)
		{
			textprintf_ex(screen,font,0,50,15,-1,"true");
		}
		Sleep(15000);
		
	}
	if(right>x-w/4&&
		left<x+w/4 &&
		bottom>y-h/2 &&
		top<y+h/2)
		{
			if(y<yc-w/6-15)
			{
				health-=3;
				return 1;
			}
			if(y<yc+w/6+15)
			{
				health-=2;
				return 2;
			}
			health--;
			return 3;
		}
		return 0;
}
int Player::getHealth()
{
	return health;
}
int Player::getArrowX()
{
	if(dir==0)
	{
		return right;
	}
	return left;
}
int Player::getArrowY()
{
	return yc;
}
int Player::getWidth()
{
	return width;
}
int Player::getHeight()
{
	return height;
}
int Player::getX()
{
	return xc;
}
int Player::getY()
{
	return yc;
}
void Player::setActive(bool a)
{
	active=a;
}
void Player::updateAngle(double a)
{
	double temp=a*double(180)/3.1415;
	temp/=5;
	int round=nearbyint(temp);
	angle=round*5;
}
void Player::setMoves(int m)
{
	moves=m;
}
void Player::moveForeward()
{
	if(moves>0)
	{
		if(dir==0)
		{
			xc+=1;
			left+=1;
			right+=1;
		}
		else
		{
			xc-=1;
			left-=1;
			right-=1;
		}
	}
}
void Player::moveBackward()
{
	if(moves>0)
	{
		if(dir==0)
		{
			xc-=1;
			left-=1;
			right-=1;
		}
		else
		{
			xc+=1;
			left+=1;
			right+=1;
		}
	}
}
int Player::getMoves(){return moves;}
