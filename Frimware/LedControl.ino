#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "OlolololO";
const char* password = "Crdyyudv";
const char* host = "esp8266fs";


#include "FsServ.h"
#include "Upd.h"
#include "WS.h"

void setup(void) {
  DBG_OUTPUT_PORT.begin(115200);
  PrepareMem();
  PrepareLed ();
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DBG_OUTPUT_PORT.print(".");
  }
  DBG_OUTPUT_PORT.println("");
  DBG_OUTPUT_PORT.print("Connected! IP address: ");
  DBG_OUTPUT_PORT.println(WiFi.localIP());

  MDNS.begin(host);
  MDNS.addService("ws", "tcp", 81);
  MDNS.addService("http", "tcp", 80);

  HandleUpdate() ; //Start updater service
  BindPages(); //Start Spiffs service
  InitWs();
  server.begin();
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


