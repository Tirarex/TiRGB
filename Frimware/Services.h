//Simple HTTP get/post worker
void handleHTTPsrv() {
  String  msg;
  if (server.hasArg("col")) {
    Ccolor(0, server.arg("ch0").toInt(), 0);
    Ccolor(1, server.arg("ch1").toInt(), 0);
    Ccolor(2, server.arg("ch2").toInt(), 0);
  }
  

  String content = "<html><body><form action='/scolor' method='GET'>SUBMIT COLOR<br>";
  content += "R:<input type='text' name='R' placeholder='color 0-255'><br>";
  content += "WORK ON IT";
  content += "<input type='submit' name='SUBMIT' value='Submit'>";
  content += "-</body></html>";
  server.send(200, "text/html", content);
}


void handleSTATEsrv() {
  String content = "";
  int i;
  for (i = 0; i < UsedCH; i = i + 1) {
    content += "CH:" + i + String( ColorsReal[i]);
  }


  server.send(200, "text/html", content);
}

void InitHttpApi() {
  server.on("/scolor", handleHTTPsrv);
  server.on("/state", handleSTATEsrv);
}

// End of http api ------------------------------------------------------------------

