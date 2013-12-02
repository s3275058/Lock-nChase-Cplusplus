#include "Character.hpp"
#include "Map.hpp"
#include "Gui.hpp"
#include "Tile.hpp"
#include "Menu.hpp"
#include "libtcod.hpp"

#ifndef ENGINE_H
#define ENGINE_H
class Engine {
public :

    TCODList<Character *> guards;
    Character *player;
	Gui *gui;
	Map *map;
	enum GameStatus {
		RUNNING,
		END,
		QUIT
	} gameStatus;
	
	int screenWidth;
    int screenHeight;
    int mapWidth;
    int mapHeight;

	int noGuard;
	int noKey, collKey;
	int point;
	
    Engine(int screenWidth, int screenHeight);
    ~Engine();
    void update();
    void render();
    void endGame();
    void init(int mode);
    void load();
    void save();
    void clear();
    void subMenu();
    
protected:
	void collide();
};

#endif
extern Engine engine;


