//Made by Tirarex 2017
#include "Settings.h" //Settings file

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>//EEPROM Lib 

#include "EEPROM.h" //EEPROM simple lib
#include "System.h" //System func
#include "FsServ.h" //Spifs file server
#include "Upd.h" //Web updater 
#include "WS.h" //WebSockets worker

void setup(void) {
  DBG_OUTPUT_PORT.begin(115200);
  PrepareLed();//Make magic
  InitEEPROM(EEPROMSize);
  PrepareMem(); //ReadMem

  if (WifiSetup == 1) {




  } else {
    SetupWifi();//StartupWifi
    HandleUpdate();//Start updater service
    BindPages();//Start Spiffs service
    InitWs();//WebSockets init
  }
  server.begin(); ColorLeds (0, 0, 0);

}



void loop(void) {
  server.handleClient();
  webSocket.loop();
  CheckWifiConnection();



  if (millis() - lastTimeHost > 10) {
    lastTimeHost = millis();
  }

  switch (TiMode) {
    case 0:
      ApplyColor();
      break;
    case 1:
      if (millis() - lastTimeRefresh > WAIT_RAINBOW && millis() - lastTimeRefreshTimer > rainbowDelay ) {
        lastTimeRefreshTimer = millis();
        writeWheel(cnt++, RGB);
      }
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
  }
}



