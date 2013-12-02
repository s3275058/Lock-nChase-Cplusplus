#include "main.hpp"

Engine engine(75,55);
 
int main() {
    while ( !TCODConsole::isWindowClosed()) {
    	engine.update();
    	engine.render();
		TCODConsole::flush();    
    }
    return 0;
}


