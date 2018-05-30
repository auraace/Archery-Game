#include <allegro.h>
#include <winalleg.h>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

using namespace std;

#ifndef Player_H
#define Player_H

class Player
{
	public:
		Player();
		Player(int x, int y, int w, int h, char *imgname,int d);
		Player(int x, int y, int w, int h, int d);
		~Player();
		void drawPlayer(BITMAP *Buffer);
		void loadPlayer(char imgname[]);
		void drawHitbox(BITMAP *Buffer);
		int getHealth();
		void removeBackground();
		int collision(int x,int y, int w, int h);
		int getArrowX();
		int getArrowY();
		int getHeight();
		int getWidth();
		int getX();
		int getY();
		void setActive(bool a);
		void updateAngle(double a);
		void setUpBitmaps();
		void setMoves(int m);
		void moveForeward();
		void moveBackward();
		int getMoves();
	private:
		int xc,yc,width,height,top,bottom,left,right,health,dir,angle,moves;
		bool active;
		BITMAP *player;
		BITMAP *healthBar[7];
		BITMAP *playerBow[19];
		//BITMAP *bow;
		char fileName[20];
};

#endif
