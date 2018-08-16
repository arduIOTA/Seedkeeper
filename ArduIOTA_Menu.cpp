#include "Arduino.h"
#include "EEPROM.h"
#include "ArduIOTA_Menu.h"

ArduIOTA_Menu::ArduIOTA_Menu (bool s)  {
  this->showMenu = s;
}

void ArduIOTA_Menu::ShowMenu() // Show main menu
{
  Serial.print("\r\n-- Menu --\r\n1. Set seed\r\n2. Get Seed\r\n3. Factory default\r\n4. Close\r\n_____________\r\n>  ");
}

String ArduIOTA_Menu::MenuEingabe() // main menu choice
{ 
  Serial.setTimeout(1000);
  return Serial.readString();
}
