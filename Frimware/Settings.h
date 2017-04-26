
//Wifi Settings
const char* ssid = "Xiaomi"; //SSID HEre
const char* password = "Crdyyudv"; //Wifi passw here


//RGB Strip pins 
#define BLUEPIN 14
#define REDPIN 12
#define GREENPIN 13

//Pount light pins
const int ledscount=2;
int Leds[ledscount] = {4, 5};
int LedSt[ledscount] = {1, 1};



#define DBG_OUTPUT_PORT Serial
const char* host = "esp8266fs";
