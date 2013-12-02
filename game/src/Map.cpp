#include "main.hpp"
	 
Map::Map(int width, int height, int mode) : width(width),height(height),mode(mode){
	randomInit();
}
void Map::init()
{
	tiles=new Tile[width*height];
}

void Map::randomInit()
{
	tiles=new Tile[width*height];
	//generate the wall		
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			bool at_edge = x == 0 || x == width - 1 || y == 0 || y == height - 1;
			TCODRandom *rng=TCODRandom::getInstance();
			int r = rng->getInt(0,100);	//random
			if (at_edge) {
				setWall(x,y); //wall around the map
			}else if(r<mode){
				setWall(x,y);	//wall randomly in the map
			}else if(r==88){
				setItem(x,y,1); //generate keys
			}else if(r==77){
				setItem(x,y,0); //generate money
			}
		}
	}
	//generate the lock
	setItem(width/2, height/2, 2);	
}

Map::~Map() {
			delete [] tiles;
		}

		bool Map::isWall(int x, int y) const {
			if(!tiles[x+y*width].canWalk && tiles[x+y*width].itemType==-1){
				return true;
			}
				return false;
		}
		
		bool Map::isPickable(int x, int y) const {
			 if(tiles[x+y*width].itemType==2 && engine.collKey!=engine.noKey){
				return false;
			}else {
				return true;
			}
		}

		int Map::getType(int x, int y) const{
			return tiles[x+y*width].itemType;
		}
		

void Map::render() const {
			for (int x=0; x < width; x++) {
				for (int y=0; y < height; y++) {

					TCODConsole::root->setChar(x,y,isWall(x,y) ?'#': ' ');
					switch(tiles[x+y*width].itemType)
					{
						case 2: TCODConsole::root->setChar(x,y,'/');
								TCODConsole::root->setCharForeground(x,y,TCODColor::green);
								break;
						case 0: TCODConsole::root->setChar(x,y,'$');
								TCODConsole::root->setCharForeground(x,y,TCODColor::yellow);
								break;
						case 1: TCODConsole::root->setChar(x,y,'+');
								TCODConsole::root->setCharForeground(x,y,TCODColor::red);
								break;
					}
				}
			}
		}

void Map::setItem(int x, int y, int type){
    		tiles[x+y*width].canWalk=true;
    		tiles[x+y*width].itemType = type;
			if(type==1) engine.noKey++;
}

void Map::deleteItem(int x, int y){
			TCODConsole::root->setChar(x,y,' ');
			switch(getType(x,y)){
				case 0:	engine.point+=100;
					tiles[x+y*width].itemType = -1; 
					engine.gui->message(TCODColor::white,"User get 100 points"); 
					break;
				case 1: engine.collKey++;
					tiles[x+y*width].itemType = -1;
					engine.gui->message(TCODColor::white,"User get a key"); 
					break;
				case 2: tiles[x+y*width].itemType = -1;  
					engine.endGame();
					break;
			}
		}
	 
	    void Map::setWall(int x, int y) {
    		tiles[x+y*width].canWalk=false;
}



