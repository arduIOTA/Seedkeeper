#ifndef __ArduIOTA_Menu__
#define __ArduIOTA_Menu__

#include "Arduino.h"

class ArduIOTA_Menu {
private:


public:
 bool showMenu;
 bool loopStart;
 ArduIOTA_Menu (bool showMenu);
    
 void ShowMenu();
 String MenuEingabe();
};

#endif
