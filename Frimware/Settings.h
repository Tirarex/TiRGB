


//Wifi Settings
const char* ssid = "Xiaomi"; //SSID Here
const char* password = "Crdyyudv"; //Wifi passw here

//Esp8266 setup ap settings
const char* ApName = "TiRGB"; //Settings Ap name
const char* ApPassw = "Jfdf5dgrg7"; //Settings Ap passw

//System
#define EEPROMSize 512 //memory size
#define LedPWMFreq 10000 //PWM Freq

/*
   EEPROM STACK
   |----------------------------------512----------------------------------------|
   |-0-32-SSID-Name-|-32-96-Passw-|-96-97-Ap-mode-|-97-110-RGB-Coeff-|-reserved--|
*/


//Smoth color
float SmoCol = 0.1;

//RGB Strip pins
int RedMult = 1;
int GreenMult = 1;
int BlueMult = 1;

//RGB Strip pins
#define REDPIN 12
#define GREENPIN 13
#define BLUEPIN 14

//Pount light pins
const int ledscount = 2;
int Leds[ledscount] = {4, 5};
int LedSt[ledscount] = {1, 1};


#define DBG_OUTPUT_PORT Serial
const char* host = "TiRGB";



