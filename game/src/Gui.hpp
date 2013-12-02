#include "libtcod.hpp"
#include "Menu.hpp"


#ifndef GUI_H
#define GUI_H
class Gui {
public :
	Menu menu;
	Gui();
	~Gui();
	void render();
	void message(const TCODColor &col, const char *text, ...);
	void gameRender();
	void clear();

protected :
	TCODConsole *con;

	struct Message {
		char *text;
		TCODColor col;
		Message(const char *text, const TCODColor &col);
		~Message();
	};
	TCODList<Message *> log;

	void renderBar(int x, int y, int width, const char *name,float value, float maxValue, const TCODColor &barColor,const TCODColor&backColor);
	

};
#endif


