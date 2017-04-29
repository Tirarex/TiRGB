


int ErrCount, ledBL; //Varibles for errors and led blinking (when connecting to wifi)

int WifiSetup; //

//Store color
int Colors[3];
float ColorsReal[3];


//Remap rgb 0-255 to Aw 0-1023
int remap (int val) {
  return map(val, 0, 255, 0, 1023);
  //return map(val, 0, 255, 1023, 0); //reversed for - + + + rgb strip
}

void ApplyColor() {


  if  (ColorsReal[0] < Colors[0]) {
    ColorsReal[0] = ColorsReal[0] + SmoCol;
  }
  if  (ColorsReal[0] > Colors[0]) {
    ColorsReal[0] = ColorsReal[0] - SmoCol;
  }

  if  (ColorsReal[1] < Colors[1]) {
    ColorsReal[1] = ColorsReal[1] + SmoCol;
  }
  if  (ColorsReal[1] > Colors[1]) {
    ColorsReal[1] = ColorsReal[1] - SmoCol;
  }


  if  (ColorsReal[2] < Colors[2]) {
    ColorsReal[2] = ColorsReal[2] + SmoCol;
  }
  if  (ColorsReal[2] > Colors[2]) {
    ColorsReal[2] = ColorsReal[2] - SmoCol;
  }
  analogWrite(REDPIN, ColorsReal[0]*RedMult);
  analogWrite(GREENPIN, ColorsReal[1]*GreenMult);
  analogWrite(BLUEPIN, ColorsReal[2]*BlueMult);
}




//Rainbow var
#define WAIT_RAINBOW 10000
int rainbowDelay = 10000;
int RGB[3];
int cnt = 0;

//0-JustLit
//1-Rainbow
//2-blink
//3-fade
//4-Music
//5-reserved
int TiMode = 0;



void Wheel(int WheelPos, int* RGB) {
  WheelPos = WheelPos % 256;
  if (WheelPos < 85) {
    RGB[0] = WheelPos * 3;
    RGB[1] = 255 - WheelPos * 3;
    RGB[2] = 0;
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    RGB[2] = WheelPos * 3;
    RGB[0] = 255 - WheelPos * 3;
    RGB[1] = 0;
  }
  else if (WheelPos < 255) {
    WheelPos -= 170;
    RGB[1] = WheelPos * 3;
    RGB[2] = 255 - WheelPos * 3;
    RGB[0] = 0;

  }
  else
  {
    WheelPos -= 255;
    RGB[0] = WheelPos * 3;
    RGB[1] = 255 - WheelPos * 3;
    RGB[2] = 0;
  }
}


void ColorLeds (int r, int g, int b) {
  analogWrite(REDPIN, remap(r)*RedMult);
  analogWrite(GREENPIN, remap(g)*GreenMult);
  analogWrite(BLUEPIN, remap(b)*BlueMult);
}

// Write wheel to leds
void writeWheel(int WheelPos, int* RGB) {
  Wheel(WheelPos, RGB);
  analogWrite(REDPIN, remap(RGB[0])*RedMult);
  analogWrite(GREENPIN, remap(RGB[1])*GreenMult);
  analogWrite(BLUEPIN, remap(RGB[2])*BlueMult);
}
void PrepareLed () {
  analogWriteFreq(LedPWMFreq);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  int i;
  for (i = 0; i < ledscount; i = i + 1) {
    pinMode(Leds[i], OUTPUT);
  }
}

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


void SetupWifi () {
  ColorLeds (255, 0, 0);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    ledBL = 1 - ledBL;
    ColorLeds (255 * ledBL, 0, 0);
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
}


void CheckWifiConnection() {
  //Attempt to fix lags with disconnect
  if (WiFi.status() != WL_CONNECTED) {
    ErrCount++;
    if (ErrCount >= 5) { //if too many errors for 25sec - reboot
      ESP.reset();
    }
    delay(5000);
  } else {
    ErrCount = 0;
  }
}

