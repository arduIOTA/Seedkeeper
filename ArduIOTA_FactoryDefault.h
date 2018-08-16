#ifndef __ArduIOTA_FactoryDefault__
#define __ArduIOTA_FactoryDefault__

#include "Arduino.h"

class ArduIOTA_FactoryDefault {
private:
  byte adresseFactoryDefault;


public:
  ArduIOTA_FactoryDefault (byte adresseFactoryDefault);

  bool showFactoryDefault;
    
  bool IfFactoryDefault();
  void WriteFactoryDefault(byte b);
  int FactoryDefaultMenu();
};

#endif
