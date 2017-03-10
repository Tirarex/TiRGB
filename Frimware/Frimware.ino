//Made by Tirarex 2017

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "OlolololO"; //SSID HEre
const char* password = "Crdyyudv"; //Wifi passw here
const char* host = "esp8266fs";

int brightness = 0;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by

#include "FsServ.h" //Spifs file server
#include "Upd.h" //Web updater espIP/upd
#include "WS.h" //WebSockets worker

void setup(void) {
  DBG_OUTPUT_PORT.begin(115200);
  PrepareLed ();

  ColorLeds (255, 255, 0);
  PrepareMem();

  ColorLeds (255, 0, 0);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DBG_OUTPUT_PORT.print(".");
  }
  DBG_OUTPUT_PORT.println("");
  DBG_OUTPUT_PORT.print("Connected! IP address: ");
  DBG_OUTPUT_PORT.println(WiFi.localIP());

  ColorLeds (0, 0, 255);

  MDNS.begin(host);
  MDNS.addService("ws", "tcp", 81);
  MDNS.addService("http", "tcp", 80);

  HandleUpdate() ; //Start updater service
  BindPages(); //Start Spiffs service
  InitWs();
  server.begin();
  ColorLeds (0, 0, 0);
}



void loop(void) {
  server.handleClient();
  webSocket.loop();
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



