#ifndef __ARDUIOTA__
#define __ARDUIOTA__

#include "Arduino.h"

class ArduIOTA {
private:
  byte resetDelay;

public:
  ArduIOTA (int resetDelay);
    
  void software_Reset();
  void FormatArduIota();
};

#endif
