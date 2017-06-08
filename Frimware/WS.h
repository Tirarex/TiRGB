
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

        if (text.startsWith("m")) {
          String tVal = (text.substring(text.indexOf("m") + 1, text.length()));
          TiMode = tVal.toInt();

          switch (TiMode) {
            case 0:
              break;
            case 1:
              break;
            case 2:
              FadeCLR[0] = unmap(ColorsNew[0]);
              FadeCLR[1] = unmap(ColorsNew[1]);
              FadeCLR[2] = unmap(ColorsNew[2]);
              break;
            case 3:
              FadeCLR[0] = unmap(ColorsNew[0]);
              FadeCLR[1] = unmap(ColorsNew[1]);
              FadeCLR[2] = unmap(ColorsNew[2]);
              break;
            case 4:
              break;
          }



        }

        if (text.startsWith("r")) {
          String xVal = (text.substring(text.indexOf("r") + 1, text.length()));
          int xInt = xVal.toInt();
          Ccolor(0, xInt, 0);
        }

        if (text.startsWith("g")) {
          String yVal = (text.substring(text.indexOf("g") + 1, text.length()));
          int yInt = yVal.toInt();
          Ccolor(1, yInt, 0);
        }

        if (text.startsWith("b")) {
          String zVal = (text.substring(text.indexOf("b") + 1, text.length()));
          int zInt = zVal.toInt();
          Ccolor(2, zInt, 0);
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


