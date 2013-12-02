#include "main.hpp"

Character::Character(int x, int y, int ch,int live,int sX, int sY, const TCODColor &col) :
    x(x),y(y),ch(ch),live(live),sX(sX),sY(sY),col(col) {
}

void Character::render() const {
    TCODConsole::root->setChar(x,y,ch);
    TCODConsole::root->setCharForeground(x,y,col);
}

void Character::guardUpdate(int targetx, int targety)
{
	count++;
	//time out
	if(count%200==0){
		int dx = targetx - x;
		int dy = targety - y;
		int stepdx = (dx > 0 ? 1:-1);
		int stepdy = (dy > 0 ? 1:-1);
		float distance=sqrtf(dx*dx+dy*dy);
		if ( distance != 0 ) {
			dx = (int)(round(dx/distance));
			dy = (int)(round(dy/distance));
			if ( !engine.map->isWall(x+dx,y+dy) ) {
				x += dx;
				y += dy;
			} else if (! engine.map->isWall(x+stepdx,y) ) {
				x += stepdx;
			} else if (! engine.map->isWall(x,y+stepdy) ) {
				y += stepdy;
			}
		} 
	}
}

void Character::spamBack(){
	x = sX;
	y = sY;
}


