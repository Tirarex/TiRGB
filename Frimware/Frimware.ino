//Made by Tirarex 2017
#include "Settings.h" //Settings file

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>//EEPROM Lib 

#include "EEPROM.h" //EEPROM simple lib
#include "Led.h" //Led algo 
#include "System.h" //System func
#include "FsServ.h" //Spifs file server
#include "Upd.h" //Web updater 
#include "WS.h" //WebSockets worker
#include "Services.h" //Services (mqtt and etc)
#include "Buttons.h" //Buttons func


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
  if ( millis() - lastTimeRefreshTimer > rainbowDelay ) {
    lastTimeRefreshTimer = millis();
    switch (TiMode) {
      case 0:
        break;
      case 1:
        LigthChSpeed = 0.00005;
        FlowStage++;
        if (FlowStage > 4) {
          FlowStage = 0;
        }
        switch (FlowStage) {
          case 0:
            Ccolor(0, 255, TiMode); Ccolor(1, 0, TiMode); Ccolor(2, 0, TiMode);
            break;
          case 1:
            Ccolor(0, 0, TiMode); Ccolor(1, 255, TiMode); Ccolor(2, 0, TiMode);
            break;
          case 2:
            Ccolor(0, 0, TiMode); Ccolor(1, 255, TiMode); Ccolor(2, 0, TiMode);
            break;
          case 3:
            Ccolor(0, 0, TiMode); Ccolor(1, 255, TiMode); Ccolor(2, 255, TiMode);
            break;
          case 4:
            Ccolor(0, 255, TiMode); Ccolor(1, 255, TiMode); Ccolor(2, 0, TiMode);
            break;
        }
        break;
      case 2:
        LigthChSpeed = 0.0001;
         FlowStage=1-FlowStage;

        if (FlowStage >0)
        {
           Ccolor(0, FadeCLR[1], TiMode); Ccolor(1, FadeCLR[2], TiMode); Ccolor(2, FadeCLR[3], TiMode);
        }
        else
        {
           Ccolor(0, 0, TiMode); Ccolor(1, 0, TiMode); Ccolor(2, 0, TiMode);
        }



        break;
      case 3:
        LigthChSpeed = 1;
         FlowStage=1-FlowStage;

        if (FlowStage >0)
        {
           Ccolor(0, FadeCLR[1], TiMode); Ccolor(1, FadeCLR[2], TiMode); Ccolor(2, FadeCLR[3], TiMode);
        }
        else
        {
           Ccolor(0, 0, TiMode); Ccolor(1, 0, TiMode); Ccolor(2, 0, TiMode);
        }

        break;
      case 4:
        break;
    }
  }
  ApplyColor();
}



