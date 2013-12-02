#include "libtcod.hpp"

#ifndef MENU_H
#define MENU_H

class Menu {
public :
	enum MenuItemCode {
		NONE,
		NEW_GAME,
		EASY,
		HARD,
		NORMAL,
		CONTINUE,
		EXIT
	};
	~Menu();
	void clear();
	void addItem(MenuItemCode code, const char *label);
	MenuItemCode pick();
protected :
	struct MenuItem {
		MenuItemCode code;
		const char *label;
	};
	TCODList<MenuItem *> items;
};
#endif

