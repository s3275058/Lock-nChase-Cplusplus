#include "main.hpp"

static const int EASY_MODE = 3, NORMAL_MODE = 8, HARD_MODE =15;

Engine::Engine(int screenWidth, int screenHeight):player(NULL),map(NULL), gameStatus(RUNNING), 
												screenWidth(screenWidth),screenHeight(screenHeight)
													
{
	
	TCODConsole::initRoot(screenWidth,screenHeight,"Lock 'n chase",false);

	gui = new Gui();    	
	load();
}

Engine::~Engine()
{
    clear();
    delete map;
	delete player;
	delete gui;

}

void Engine::clear() {
    guards.clearAndDelete();
    if ( map ) delete map;
    gui->clear();
}

void Engine::subMenu()
{
	gui->menu.clear();
	gui->menu.addItem(Menu::EASY,"Easy");
	gui->menu.addItem(Menu::NORMAL,"Normal");
	gui->menu.addItem(Menu::HARD,"Hard");
	
	Menu::MenuItemCode menuItem=gui->menu.pick();
	
	if ( menuItem == Menu::EASY ) 
	{
		clear();
		init(EASY_MODE);
	}else if ( menuItem == Menu::NORMAL) {
		// New game
		clear();
		init(NORMAL_MODE);
	}else if ( menuItem == Menu::HARD ) {
		// New game
		clear();
		init(HARD_MODE);
	}
	
}

void Engine::load() 
{
	gui->menu.clear();
	gui->menu.addItem(Menu::NEW_GAME,"New game");
	if ( TCODSystem::fileExists("save.xml")) {
		gui->menu.addItem(Menu::CONTINUE,"Continue");
	}
	gui->menu.addItem(Menu::EXIT,"Exit");

	Menu::MenuItemCode menuItem=gui->menu.pick();
	if ( menuItem == Menu::EXIT || menuItem == Menu::NONE ) {
		// Exit or window closed
		exit(0);
	} else if ( menuItem == Menu::NEW_GAME ) {
		// sub menu for New game
		subMenu();
	} 
}

void Engine::init(int mode) 
{
	noGuard = 4;
	noKey = collKey = point = 0;
	mapWidth = 70;
	mapHeight = 30;
	
    TCODRandom *rng=TCODRandom::getInstance();
    player = new Character(2,2,'O',3,2,2,TCODColor::white);
  
    map = new Map(mapWidth,mapHeight,mode);
    
	
	
	//generate guard
	while(noGuard!=0){
		int x=  rng->getInt(1,mapWidth-1);
		int y = rng->getInt(1,29);
		if(!map->isWall(x,y)){
			guards.push(new Character(x,y,'X',0,x,y,TCODColor::blue));
			noGuard--;
		}
	}
	gameStatus = RUNNING;
	gui->message(TCODColor::white,"Welcome to the game");
}


void Engine::update() {
	
	switch(gameStatus)
	{
					
		//case END: endGame(); break;
		case QUIT: load();
			 break;
	
		case RUNNING:
			// player update
			TCOD_key_t key;
			TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
			switch(key.vk) {
				case TCODK_UP :
					
				    if ( ! map->isWall(player->x,player->y-1) || !map->isPickable(player->x,player->y-1)) {
				        player->y--;  
						if(map->isPickable(player->x,player->y)){
							map->deleteItem(player->x,player->y);
				
						}
				    }
				break;
				case TCODK_DOWN :
				    if ( ! map->isWall(player->x,player->y+1)) {
				        player->y++;
						if(map->isPickable(player->x,player->y)){
							map->deleteItem(player->x,player->y);
						}
				    }

				break;
				case TCODK_LEFT :
				    if ( ! map->isWall(player->x-1,player->y)) {
				        player->x--;
						if(map->isPickable(player->x,player->y)){
							map->deleteItem(player->x,player->y);
						}
				    }

				break;
				case TCODK_RIGHT :
				    if ( ! map->isWall(player->x+1,player->y)) {
				        player->x++;
						if(map->isPickable(player->x,player->y)){
							map->deleteItem(player->x,player->y);
						}
				    }
				break;
				
				case TCODK_F3 :exit(0); break;
				default: break;
			}
			
			//check colide between player and guards
			for (Character **iterator=guards.begin(); iterator != guards.end(); iterator++) 
			{
				if(((*iterator)->x == player->x) && ((*iterator)->y == player->y))
				{
					collide();
					break;	
				}
			}
		
			//guard update
			for (Character **iterator=guards.begin(); iterator != guards.end(); iterator++) 
			{
				(*iterator)->guardUpdate(player->x,player->y);
			}
	
			break;	
			default: break;
	}
}

void Engine::collide()
{
	if(player->live>0){
		player->spamBack();
		gui->message(TCODColor::white,"You have been caught by the guards");
		for (Character **iterator=guards.begin(); iterator != guards.end(); iterator++) 
		{
			(*iterator)->spamBack();
		}
		player->live--;
	}
	else
	{
		//gameStatus=END;
		endGame();
	}
}

void Engine::render() 
{
	TCODConsole::root->clear();	
	// draw the map
	map->render();
	// draw the actors
	player->render();
	gui->render();

	// draw the guard
	for (Character **iterator=guards.begin(); iterator != guards.end(); iterator++) 
	{
	    (*iterator)->render();
	}
}

void Engine::endGame()
{
	
	if(collKey == noKey)
	{
		
		gui->message(TCODColor::white,"The lock is open! You have escaped! Game over.");
	}
	else
	{
		
		gui->message(TCODColor::white,"No more live. Game over.");
	}
	
	gameStatus = QUIT;
}




