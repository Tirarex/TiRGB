


int ledBL; //led blinking (when connecting to wifi)

int WifiSetup; //



//Wifi scanner
String ScanAP(void) {
  Serial.println("Looking for any WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100); //Delay for run wifi
  int n = WiFi.scanNetworks();
  Serial.println("Catched :" + n);
  String ApList = "<select name='answer'>";
  for (int i = 0; i < n; ++i)
  {
    ApList += "<option>";
    ApList += WiFi.SSID(i);
    // ApList += WiFi.RSSI(i);
    ApList += "</option>";
  }
  ApList += "</select>";
  Serial.println("Closed Wifi scanner :");
  return ApList;
}

void PrepareSetup(void) {
  ///  server.on("/s", handleSettings);
}

void RebootESP() {
  //Save led state

  //Reset
  ESP.reset();
}

//
int ConnectCounter;

void SetupWifi () {
  ColorLeds (255, 0, 0);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    ledBL = 1 - ledBL;
    ColorLeds (255 * ledBL, 0, 0);
    delay(500);
    DBG_OUTPUT_PORT.print(".");
    ConnectCounter++;
    if (ConnectCounter >= 15) {
      RebootESP();
    }

  }
  DBG_OUTPUT_PORT.println("");
  DBG_OUTPUT_PORT.print("Connected! IP address: ");
  DBG_OUTPUT_PORT.println(WiFi.localIP());

  ColorLeds (0, 0, 255);

  MDNS.begin(host);
  MDNS.addService("ws", "tcp", 81);
  MDNS.addService("http", "tcp", 80);
}



//Anti lag
int ErrCount;
void CheckWifiConnection() {
  //Attempt to fix lags with disconnect
  if (WiFi.status() != WL_CONNECTED) {
    ErrCount++;
    if (ErrCount >= 5) { //if too many errors for 25sec - reboot
      RebootESP();
    }
    delay(5000);
  } else {
    ErrCount = 0;
  }
}

