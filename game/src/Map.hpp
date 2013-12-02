//#include "System.hpp"
//#include "Tile.hpp"
#include "libtcod.hpp"


#ifndef TILE_H
#define TILE_H
struct Tile {
    bool canWalk; // can we walk through this tile?
	int itemType;
    Tile() : canWalk(true), itemType(-1) {}
	
};
#endif


#ifndef MAP_H
#define MAP_H 
class Map
{
	protected :
	    Tile *tiles;
	    void setWall(int x, int y) ;
	    void setItem(int x, int y, int type);

	public :
	    int width,height,mode;
		Map(int width, int height, int mode);
		~Map();
		bool isWall(int x, int y) const;
		bool isPickable(int x, int y) const ;
		int getType(int x, int y) const;
		void render() const ;
		void deleteItem(int x, int y);
		void load(TCODZip &zip);
		void save(TCODZip &zip);
		void init();
		void randomInit();
};
#endif


