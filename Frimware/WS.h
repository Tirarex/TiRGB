
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



        if (text.startsWith("ch")) {
          String channel = (text.substring(text.indexOf("ch") + 2, 3));
          int IntChannel = channel.toInt();
          String ChannelVal = (text.substring(text.indexOf("ch" + channel) + 3, text.length()));
          int IntChannelVal = ChannelVal.toInt();
          //webSocket.sendTXT(num, "channel:" + channel + "   Value:" + ChannelVal);
          Ccolor(IntChannel, IntChannelVal, 0);
        }



        if (text.startsWith("off")) {
          int i;
          for (i = 0; i < UsedCH; i = i + 1) {
            Ccolor(i, 0, 0);
          }
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


