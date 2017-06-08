//Simple HTTP get/post worker
void handleHTTPsrv() {
  String  msg;
  if (server.hasArg("R") && server.hasArg("G") && server.hasArg("B")) {
    Ccolor(0, server.arg("R").toInt(), 0);
    Ccolor(1, server.arg("G").toInt(), 0);
    Ccolor(2, server.arg("B").toInt(), 0);
    Serial.println("Hopa - color");
  }
  if (server.hasArg("M")) {
    int sArg=server.arg("M").toInt();
    switch (sArg) {
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
    Serial.println("Hopa - Rejim");
  }
  if (server.hasArg("T")) {
    rainbowDelay = server.arg("T").toInt();
 
    Serial.println("Hopa - Timing");
  }


  String content = "<html><body><form action='/scolor' method='GET'>SUBMIT COLOR<br>";
  content += "R:<input type='text' name='R' placeholder='color 0-255'><br>";
  content += "G:<input type='text' name='G' placeholder='color 0-255'><br>";
  content += "B:<input type='text' name='B' placeholder='color 0-255'><br>";
  content += "<input type='submit' name='SUBMIT' value='Submit'>";
  content += "-</body></html>";
  server.send(200, "text/html", content);
}


void handleSTATEsrv() {

  String content = "---";
  content += "RN:"+ String( unmap(ColorsReal[0]));
  content += "GN:"+ String( unmap(ColorsReal[1]));
  content += "BN:"+ String( unmap(ColorsReal[2]));
  content += "RR:"+ String( unmap(ColorsNew[0]));
  content += "GR:"+ String( unmap(ColorsNew[1]));
  content += "BR:"+ String( unmap(ColorsNew[2]));
  content += "---";
  content += "MO:"+ String(TiMode);
  content += "Ti:"+ String(rainbowDelay);
  server.send(200, "text/html", content);
}

void InitHttpApi(){
      server.on("/scolor", handleHTTPsrv);
      server.on("/state", handleSTATEsrv);
}

// End of http api ------------------------------------------------------------------

