void target_serial() {
  if (Serial.available() > 0) {
    String targetStr = "";
    while (Serial.available()) {
      char character = Serial.read();
      targetStr += String(character);
    }
    Serial.println(targetStr);
     target = targetStr.toFloat();
    //powerPercentage = targetStr.toFloat();
   // wait_time = powerPercentage_to_wait(powerPercentage);
  }
}


void pwr_percentage_serial() {
  if (Serial.available() > 0) {
    String percStr = "";
    while (Serial.available()) {
      char character = Serial.read();
      percStr += String(character);
    }
    Serial.println(percStr);
     powerPercentage = percStr.toFloat();
    //powerPercentage = targetStr.toFloat();
   // wait_time = powerPercentage_to_wait(powerPercentage);
  }
}


void menu() {  // utile pour simuler valeurs pour les tests
  if (Serial.available() > 0) {
    int readchar = Serial.read();
    switch (readchar) { 
      case '1':
        Temperature += 5;
        break;
      case '2':
        Temperature += 1;
        break;
      case '3':
        Temperature += 0.5;
        break;
      case '4':
        Temperature += 0.1;
        break;
      case '5':
        Temperature += 0.01;
        break;
      case '6':
        Temperature -= 0.01;
        break;
      case '7':
        Temperature -= 0.1;
        break;
      case '8':
        Temperature -= 0.5;
        break;
      case '9':
        Temperature -= 1;
        break;
      case '0':
        Temperature -= 5;
        break;
      default: break;
    }
    Serial.print("Temperature :");
    Serial.println(Temperature);
    Serial.print("powerPercentage :");
    Serial.println(powerPercentage);
    Serial.print("wait_time :");
    Serial.println(wait_time);
    Serial.println("1 +5");
    Serial.println("2 +1");
    Serial.println("3 +0.5");
    Serial.println("4 +0.1");
    Serial.println("5 +0.01");
    Serial.println("6 -0.01");
    Serial.println("7 -0.1");
    Serial.println("8 -0.5");
    Serial.println("9 -1");
    Serial.println("0 -5");
    Serial.println();
    if (Temperature > 100) {
      Temperature = 100;
    }
    if (Temperature < 0) {
      Temperature = 0;
    }
  }
}

unsigned long tim = 0;
unsigned long cycle = 0;
void show_data() {


  cycle = millis() - tim;
  tim = millis();
  Serial.print("power:");
  Serial.print(power);
  Serial.print("\t");
  Serial.print("Tpower:");
  Serial.print(target);
  Serial.print("\t");
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
  Serial.print("45:");
  Serial.print(45);
  Serial.print("\t");
  Serial.print("100:");
  Serial.println(100);
}