
void Wifibegin() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("\nConnecting to WiFi Network ..");
  Serial.printf("Connexion à [%s] / pass [%s]\n", ssid.c_str(), pass.c_str());

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



}
