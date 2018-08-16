#include "Arduino.h"
#include "EEPROM.h"
#include "ArduIOTA.h"
#include "ArduIOTA_FactoryDefault.h"
#include "ArduIOTA_Menu.h"

ArduIOTA_FactoryDefault::ArduIOTA_FactoryDefault (byte a)  {
  this->adresseFactoryDefault = a;
}

bool ArduIOTA_FactoryDefault::IfFactoryDefault() // is factory default state
{
  return (String(EEPROM.read(this->adresseFactoryDefault)) == "0");
}

void ArduIOTA_FactoryDefault::WriteFactoryDefault(byte b)
{
  EEPROM.write(this->adresseFactoryDefault, b);
}

int ArduIOTA_FactoryDefault::FactoryDefaultMenu()
{
  byte buf[1];
    
  if(this->showFactoryDefault)
  {
    Serial.println();
    Serial.print("-- Factory default -- \r\n1. Ok (THIS WILL DELETE ALL!!!)\r\n2. Cancel\r\n_____________\r\n>  ");
    this->showFactoryDefault = false;
  }
  
  Serial.setTimeout(60000L);
  Serial.readBytesUntil('#', (char *) buf, 1);
  String input = String((char*) buf);
  
  if(input.substring(0,1) == "1")
  {
    Serial.println("1");
    return 1;
  }
  else
  {
    Serial.println("2");
    return 2;
  }
}
