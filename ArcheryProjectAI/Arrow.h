#include <allegro.h>
#include <winalleg.h>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

using namespace std;

#ifndef Arrow_H
#define Arrow_H

class Arrow
{
	public:
		Arrow();
		Arrow(int x,int y,int w,int h,int d);
		void drawArrow(BITMAP *Buffer);
		void updateArrow(int x,int y,double a);
		void removeBackground();
		double getAngle();
		void stopArrow();
		void setDir(int d);
		~Arrow();
	private:
		int xc,yc,dir,width,height,top,bottom,left,right;
		BITMAP *arrow;
		double angle;
		bool stop;	
		
};
#endif
