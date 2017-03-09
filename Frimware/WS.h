#include <WebSocketsServer.h>
WebSocketsServer webSocket = WebSocketsServer(81);

#define REFRESH_RAINBOW 500
#define WAIT_RAINBOW 10000

#define BLUEPIN 13
#define REDPIN 12
#define GREENPIN 14



int Leds[2] = {4, 5};
int LedSt[2] = {1, 1};

unsigned long lastTimeHost = 0;
unsigned long lastTimeRefresh = 0;
unsigned long lastTimeRefreshTimer = 0;

int rainbowDelay = WAIT_RAINBOW;
int RGB[3];
int cnt = 0;

//0-JustLit
//1-Rainbow
//2-blink
//3-fade
//4-Music
//5-reserved
int TiMode = 0;


void PrepareLed () {
  pinMode(BLUEPIN, OUTPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);

  int i;
  for (i = 0; i < 1; i = i + 1) {
    pinMode(Leds[i], OUTPUT);
  }
}
int remap (int val) {
  return map(val, 0, 255, 1023, 0);
}
// WebSOcket Events
void WSEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
      }
      break;
    case WStype_TEXT:
      {
        lastTimeRefresh = millis();
        String text = String((char *) &payload[0]);

        DBG_OUTPUT_PORT.printf("WS EVENT:");
        DBG_OUTPUT_PORT.println(text);

        if (text.startsWith("t")) {
          String Timerval = (text.substring(text.indexOf("t") + 1, text.length()));
          rainbowDelay = Timerval.toInt();
          lastTimeRefreshTimer = 0;
          lastTimeRefresh = 0;
        }

        if (text.startsWith("mode")) {
          String tVal = (text.substring(text.indexOf("mode") + 4, text.length()));
          TiMode = tVal.toInt();
          lastTimeRefreshTimer = 0;
          lastTimeRefresh = 0;
          switch (TiMode) {
            case 0:
              break;
            case 1:
              break;
            case 2:
              break;
            case 3:
              break;
            case 4:
              break;
          }
        }

        if (text.startsWith("red")) {
          String xVal = (text.substring(text.indexOf("red") + 3, text.length()));
          int xInt = xVal.toInt();
          analogWrite(REDPIN, remap(xInt));
          TiMode = 0;
        }

        if (text.startsWith("green")) {
          String yVal = (text.substring(text.indexOf("green") + 5, text.length()));
          int yInt = yVal.toInt();
          analogWrite(GREENPIN, remap(yInt));
          TiMode = 0;
        }

        if (text.startsWith("blue")) {
          String zVal = (text.substring(text.indexOf("blue") + 4, text.length()));
          int zInt = zVal.toInt();
          analogWrite(BLUEPIN, remap(zInt));
          TiMode = 0;
        }

        if (text == "RESET") {
          TiMode = 0;
          analogWrite(BLUEPIN, LOW);
          analogWrite(REDPIN, LOW);
          analogWrite(GREENPIN, LOW);
        }


        if (text.startsWith("led")) {
          String lON = (text.substring(text.indexOf("led") + 3, text.length()));
          int LedToOn = lON.toInt();
          LedSt[LedToOn] = 1 - LedSt[LedToOn];
          digitalWrite(Leds[LedToOn], LedSt[LedToOn]);
          DBG_OUTPUT_PORT.println(Leds[LedToOn]);
          DBG_OUTPUT_PORT.println(LedSt[LedToOn]);
        }
        
        if (text.startsWith("on")) {
          String lON = (text.substring(text.indexOf("on") + 2, text.length()));
          int LedToOn = lON.toInt();
           digitalWrite(Leds[LedToOn], 0);
        }

        if (text.startsWith("off")) {
          String lON = (text.substring(text.indexOf("off") + 3, text.length()));
          int LedToOn = lON.toInt();
         digitalWrite(Leds[LedToOn], 1);
        }

      }
      break;
    case WStype_BIN:
      hexdump(payload, length);
      // echo data back to browser
      webSocket.sendBIN(num, payload, length);
      break;
  }
}

void InitWs() {
  webSocket.begin();
  webSocket.onEvent(WSEvent);
}

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



// Write wheel to leds
void writeWheel(int WheelPos, int* RGB) {
  Wheel(WheelPos, RGB);
  analogWrite(REDPIN, remap(RGB[0]));
  analogWrite(GREENPIN, remap(RGB[1]));
  analogWrite(BLUEPIN, remap(RGB[2]));
}

