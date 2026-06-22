
void handleRoot() {
  if (server.arg("API_KEY") == api_key) { 
    if (server.hasArg("target")) {
      String targetStr = server.arg("target");
      target = targetStr.toFloat(); 
    }
    
    if (server.hasArg("powerPercentage")) {
      String pwrPercStr = server.arg("powerPercentage");
      powerPercentage = pwrPercStr.toFloat();
      if (powerPercentage > 100) {
        powerPercentage = 100;
      }
      if (powerPercentage < 0) {
        powerPercentage = 0;
      }
      wait_time = powerPercentage_to_wait(powerPercentage);
    }
    String returnjson = "{\"cod\": 200, \"powerPercentage\": ";
    returnjson += powerPercentage;
    returnjson += ", \"target\": ";
    returnjson += target;
    returnjson += ", \"Tank_Temperature\": ";
    returnjson += Temperature;
    returnjson += "}";
    server.send(200, "application/json", returnjson);
  } else {
    String returnjson = "{\"cod\": 401, \"message\": \"invalid api key\"}";
    server.send(401, "application/json", returnjson);
  }
}


void Wifibegin() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(Secret_ssid, Secret_password);
  Serial.println("\nConnecting to WiFi Network ..");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("RRSI: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");


  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}
