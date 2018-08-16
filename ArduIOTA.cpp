#include "Arduino.h"
#include "EEPROM.h"
#include "ArduIOTA.h"

ArduIOTA::ArduIOTA (int r)  {
  this->resetDelay   = r;
}

void ArduIOTA::software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
  delay(this->resetDelay);
  asm volatile ("  jmp 0");  
}

void ArduIOTA::FormatArduIota()
{
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
    if((i % 100) == 0)
    {
      Serial.print(".");
    }
  }
}
