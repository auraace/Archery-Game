#include "Arrow.h"

Arrow::Arrow()
{
	xc=0;
	yc=0;
	dir=0;
	arrow=NULL;
}
Arrow::Arrow(int x,int y,int w,int h,int d)
{
	xc=x;
	yc=y;
	width=w;
	height=h;
	dir=d;
	right=xc+width/2;
	left=xc-width/2;
	bottom=yc+height/2;
	top=yc-height/2;
	arrow=load_bitmap("arrow.bmp",NULL);
	stop=false;
}
Arrow::~Arrow()
{
	stop=false;
}
void Arrow::drawArrow(BITMAP *Buffer)
{
	if(!stop)
	{
		double dang=/*(int)*/angle*(double(180)/3.1415);
		int aang=int(dang*(double(255)/double(360)));
		left=xc-width/2;
		top=yc-width/2;
		//masked_blit(arrow,Buffer,0,0,left,top,width,height);
		//textprintf_ex(Buffer,font,0,20,15,-1,"radians: %d, degrees: %i",angle,dang);
		//textprintf_ex(Buffer,font,0,20,15,-1,"%f rads, %f deg, %i all",angle,dang,aang);
		if(key[KEY_T])
		{
			Sleep(1000);
		}
		if(dir==0)
		{
			rotate_sprite(Buffer,arrow,xc-width/2,yc, itofix(-aang));
		}
		else
		{
			rotate_sprite(Buffer,arrow,xc-width/2,yc, itofix(128+aang));
		}
	}
	
		
	
	
}
void Arrow::removeBackground()
{
	int pink = makecol(255,0,255);
	int color;
	int spec=100;
	for(int i=0;i<width;i++)
	{
		for(int j=0;j<height;j++)
		{
			if(getr(getpixel(arrow,i,j))>spec&&getg(getpixel(arrow,i,j))>spec&&getb(getpixel(arrow,i,j))>spec)
			{
				putpixel(arrow,i,j,pink);
			}
		}
	}
}
void Arrow::updateArrow(int x, int y,double a)
{
	xc=x;
	yc=y;
	angle=a;
}
double Arrow::getAngle(){return angle;}
void Arrow::stopArrow(){stop=true;}
void Arrow::setDir(int d){dir=d;}
