#include "Menu.hpp"


Menu::~Menu() {
	clear();
}

void Menu::clear() {
	items.clearAndDelete();
}

void Menu::addItem(MenuItemCode code, const char *label) {
	MenuItem *item=new MenuItem();
	item->code=code;
	item->label=label;
	items.push(item);
}

Menu::MenuItemCode Menu::pick() {
	
	int selectedItem=0;
	while( !TCODConsole::isWindowClosed() ) {
		
		int currentItem=0;
		for (MenuItem **it=items.begin(); it!=items.end(); it++) {
			if ( currentItem == selectedItem ) {
				TCODConsole::root->setDefaultForeground(TCODColor::lighterOrange);
			} else {
				TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);
			}
			TCODConsole::root->print(10,10+currentItem*3,(*it)->label);
			currentItem++;
		}
		TCODConsole::flush();

		// check key presses
		TCOD_key_t key;
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
		switch (key.vk) {
			case TCODK_UP : 
				selectedItem--; 
				if (selectedItem < 0) {
					selectedItem=items.size()-1;
				}
			break;
			case TCODK_DOWN : 
				selectedItem = (selectedItem + 1) % items.size(); 
			break;
			case TCODK_ENTER : 
				return items.get(selectedItem)->code; 
			default : break;
		}
	}
	return NONE;
}

