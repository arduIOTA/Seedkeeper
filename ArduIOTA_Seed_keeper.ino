#include <EEPROM.h>
#include "ArduIOTA.h"
#include "ArduIOTA_Menu.h"
#include "ArduIOTA_Pin.h"
#include "ArduIOTA_Seed.h"
#include "ArduIOTA_FactoryDefault.h"

/*
 * ArduIOTA Seedkeeper
 * 
 * Adresse0 > if facotrydefault true = 1, otherwise 0
 * Adresse1 to Adresse6 > pin to access
 * Adresse5 to Adresse149 > Seed encrypted
 * 
 * Use on your own risk!!!
 * 
 */

// ________________________________________________________________________________________________________________________________// 
const byte factoryLength          = 1;
const byte pinLength              = 4;
const byte seedLength             = 144;
uint8_t key[]                     = {0,8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,128,136,144,152,160,168,176,184,192,200,208,216,224,232,240,255}; 

const byte adresseFactoryDefault  = 0;
const byte adressePinStart        = adresseFactoryDefault + factoryLength;
const byte adressePinStop         = pinLength;
const byte adresseSeedStart       = adressePinStart + pinLength;
const byte adresseSeedStop        = adresseSeedStart + seedLength;

bool isFactoryDefault = false;

ArduIOTA                            arduIota(500);
ArduIOTA_FactoryDefault             factoryDefault(adresseFactoryDefault);
ArduIOTA_Menu                       menu(true);
ArduIOTA_Pin                        pin(adressePinStart, adressePinStop, pinLength, adresseFactoryDefault);
ArduIOTA_Seed                       seed(adresseSeedStart, adresseSeedStop, seedLength, key);

void setup() {
 
  Serial.flush();
  Serial.begin(9600);
  Serial.println("ArduIOTA Seed Keeper");
  
  while (!Serial) {
    return; 
  }
  
  if(factoryDefault.IfFactoryDefault())
  {
    Serial.println("Setup PIN");
    while(pin.SetPin() == -1)
    {
       pin.SetPin(); 
    }
    
    factoryDefault.WriteFactoryDefault(1);
    pin.isAuth = false;
    isFactoryDefault = true;
    arduIota.software_Reset(); 
  }  
  
  if(!pin.VerifyPin() && !pin.isAuth)
  {
    pin.setupStart = true;
    pin.isAuth = false;
    arduIota.software_Reset(); 
  }
}

void loop() {
  
  while(menu.showMenu)
  {    
    if(!menu.loopStart)
    {
      menu.ShowMenu();
      menu.loopStart = true;  
    }

    int menuEingabe = menu.MenuEingabe().toInt();

    if(menuEingabe == 0)
    {
      return;
    }
    else if(menuEingabe == 1)
    {
      Serial.println("1");

      while(seed.SetSeed() == -1){
        seed.SetSeed();
      }
      
      menu.showMenu = true;
      menu.ShowMenu();
      menu.loopStart = true;
    }
    else if(menuEingabe == 2)
    {
      Serial.println("2");

      seed.GetSeed();

      menu.showMenu = true;
      menu.ShowMenu();
      menu.loopStart = true;  
    }  
    else if(menuEingabe == 3)
    {
      Serial.println("3");
      
      factoryDefault.showFactoryDefault = true;
      
      if(factoryDefault.FactoryDefaultMenu() == 1)
      {
        Serial.println(); 
        Serial.println("Format arduIOTA"); 
              
        arduIota.FormatArduIota();      
        factoryDefault.WriteFactoryDefault(0);
        
        Serial.println("\r\nsuccessful!\r\nreboot...\r\n");
        Serial.flush();
        
        pin.isAuth = false;
        arduIota.software_Reset();
      }
      else if(factoryDefault.FactoryDefaultMenu() == 2)
      {        
        menu.showMenu = true;
        menu.ShowMenu();
        return;
      }
    }  
    else if(menuEingabe == 4)
    {
      Serial.println("4");
      Serial.flush();
      Serial.println();
      pin.isAuth = false;
      arduIota.software_Reset();
    }   
  }
}
