#include <stdio.h>
#include <math.h>

#include "libtcod.hpp"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
	public:
		int x,y; //position
		int ch; // ascii code
		int count;
		int live;
		int sX,sY; 
   		TCODColor col; // color
	
		Character(int x, int y, int ch,int live,int sX, int sY, const TCODColor &col);
		void guardUpdate(int targetx, int targety);
		void render() const;	
		void spamBack();
		void load();
		void save();
		
};
#endif


