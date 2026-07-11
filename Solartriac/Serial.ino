
void Serial_conf() {
  unsigned long start_conf_rimeout = millis();
  Serial.println("press any key to lawnch conf util");
  while (millis() - start_conf_rimeout < 10000) {
    if (Serial.available()) {
      while (Serial.available()) {
        Serial.read();
      }
      Serial.println("Welcome to SolarTriac config util");
      Serial.println("");
      Serial.println("Enter ssid");
      while (!Serial.available()) {}
      // Read string until newline character
      String str = Serial.readStringUntil('\n');
      str.trim();
      ssid = str;
      preferences.putString("ssid", ssid);  // String

      Serial.println("Enter pass");
      while (!Serial.available()) {}
      // Read string until newline character
      str = Serial.readStringUntil('\n');
      str.trim();
      pass = str;
      preferences.putString("pass", pass);  // String

      Serial.println("Enter mqtt broker ip");
      while (!Serial.available()) {}
      // Read string until newline character
      str = Serial.readStringUntil('\n');
      str.trim();
      MQTT_broker_addr = str;
      preferences.putString("MQTT_addr", MQTT_broker_addr);  // String

      Serial.println("Enter mqtt user");
      while (!Serial.available()) {}
      // Read string until newline character
      str = Serial.readStringUntil('\n');
      str.trim();
      MQTT_user = str;
      preferences.putString("MQTT_user", MQTT_user);  // String


      Serial.println("enter mqtt pass");
      while (!Serial.available()) {}
      // Read string until newline character
      str = Serial.readStringUntil('\n');
      str.trim();
      MQTT_pass = str;
      preferences.putString("MQTT_pass", MQTT_pass);  // String


      Serial.println("enter mqtt id");
      while (!Serial.available()) {}
      // Read string until newline character
      str = Serial.readStringUntil('\n');
      str.trim();
      id = str;
      preferences.putString("id", id);  // String
    }
  }
  ssid = preferences.getString("ssid", "");
  pass = preferences.getString("pass", "");
  MQTT_user = preferences.getString("MQTT_user", "");
  MQTT_pass = preferences.getString("MQTT_pass", "");
  MQTT_broker_addr = preferences.getString("MQTT_addr", "");
  id = preferences.getString("id", "");

  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(MQTT_user);
  Serial.println(MQTT_pass);
  Serial.println(MQTT_broker_addr);
  Serial.println(id);
}

unsigned long tim = 0;
unsigned long cycle = 0;
void show_data() {


  cycle = millis() - tim;
  tim = millis();
  Serial.print("powerPercentage:");
  Serial.print(powerPercentage);
  Serial.print("\t");
  Serial.print("wait_time:");
  Serial.print(wait_time);
  Serial.print("\t");
  Serial.print("cycle:");
  Serial.print(cycle);
  Serial.print("\t");
  Serial.print("0:");
  Serial.print(0);
  Serial.print("\t");
  Serial.print("100:");
  Serial.println(100);
}