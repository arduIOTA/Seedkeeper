# Seedkeeper
Save your Seed on the Arduino 

1. Download and install Arduino Software IDE -> https://www.arduino.cc/en/Main/Software
2. Download arduIOTA Seedkeeper -> https://github.com/arduIOTA/Seedkeeper
3. Unzip arduIOTA Seedkeeper to any folder.
4. Start *.ino* file and Arduino IDE will start.
5. Connect Arduino by USB and config your IDE to connect to Arduino.
6. Open ArduIOTA_Seed_keeper.ino and change parameter from the key (find: uint8_t key[] = {0,8,16,24,3...) !!! Only number between 0-255)
7. Upload files to your Arduino (on top right arrow).
8. Start console from arduino or maybe putty (Serial).
9. arduIOTA starts in factory default.
10. Set 4 digit PIN (like 0000).
11. Login per PIN.
12. Choose 1 to save your seed on the Arduino.
13. Write seed and make at the end an # (like 9999...9999#)
14. Choose 2 for check the seed.

