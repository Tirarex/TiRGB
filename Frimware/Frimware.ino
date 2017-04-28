//Made by Tirarex 2017
#include "Settings.h" //Settings file

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "System.h" //System func
#include "FsServ.h" //Spifs file server
#include "Upd.h" //Web updater 
#include "WS.h" //WebSockets worker

void setup(void) {
  DBG_OUTPUT_PORT.begin(115200);
  PrepareLed();//Make magic
  PrepareMem(); //ReadMem

  if (WifiSetup==1){




  }else{ 
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
  
  if (millis() - lastTimeRefresh > WAIT_RAINBOW && millis() - lastTimeRefreshTimer > rainbowDelay ) {
    lastTimeRefreshTimer = millis();
    switch (TiMode) {
      case 0:
        break;
      case 1:
        writeWheel(cnt++, RGB);
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
    }
  }
}



