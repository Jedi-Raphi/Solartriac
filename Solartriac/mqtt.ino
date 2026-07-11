void MQTT_connect() {
  mqtt.begin(MQTT_broker_addr.c_str(), MQTT_broker_port, network);
  mqtt.onMessage(messageHandler);
  Serial.println("connecting to MQTT broker");
  while (!mqtt.connect(id.c_str(), MQTT_user.c_str(), MQTT_pass.c_str())) {
    Serial.print("*");
    delay(100);
  }
  Serial.println("connected to MQTT broker");
  String SUBSCRIBE_TOPIC = String("HEMS/") + id + String("/actions/#");
  mqtt.subscribe(SUBSCRIBE_TOPIC);



  if (!mqtt.connected()) {
    Serial.println("ESP32 - MQTT broker Timeout!");
    return;
  }

  // Subscribe to a topic, the incoming messages are processed by messageHandler() function
  if (mqtt.subscribe(SUBSCRIBE_TOPIC))
    Serial.print("ESP32 - Subscribed to the topic: ");
  else
    Serial.print("ESP32 - Failed to subscribe to the topic: ");

  Serial.println(SUBSCRIBE_TOPIC);
  Serial.println("ESP32 - MQTT broker Connected!");
}

void messageHandler(String& topic, String& payload) {
  Serial.println("ESP32 - received from MQTT:");
  Serial.println("- topic: " + topic);
  Serial.println("- payload:");
  Serial.println(payload);

  if (topic == String("HEMS/Water_tank1/actions/pwr_perc")) {
    powerPercentage = 100.0 * payload.toFloat();
  }
}