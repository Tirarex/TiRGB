
/*
   WebSocke LIB by Links2004
   https://github.com/Links2004/arduinoWebSockets
*/
#include <WebSocketsServer.h>
WebSocketsServer webSocket = WebSocketsServer(81);//WS Server INIT


//Ws timers
unsigned long lastTimeHost = 0;
unsigned long lastTimeRefresh = 0;
unsigned long lastTimeRefreshTimer = 0;

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
        }

        if (text.startsWith("red")) {
          String xVal = (text.substring(text.indexOf("red") + 3, text.length()));
          int xInt = xVal.toInt();
          Colors[0] = remap(xInt);
          TiMode = 0;
        }

        if (text.startsWith("green")) {
          String yVal = (text.substring(text.indexOf("green") + 5, text.length()));
          int yInt = yVal.toInt();
          Colors[1] = remap(yInt);
          TiMode = 0;
        }

        if (text.startsWith("blue")) {
          String zVal = (text.substring(text.indexOf("blue") + 4, text.length()));
          int zInt = zVal.toInt();
          Colors[2] = remap(zInt);
          TiMode = 0;
        }

        if (text == "RESET") {
          RebootESP();
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


