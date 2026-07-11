#include <Preferences.h>
Preferences preferences;
#include <WiFi.h>
#include <ArduinoJson.h>  //v7
#include <MQTTClient.h>

WiFiClient network;
//HTTPClient http;

String ssid = "";
String pass = "";
String MQTT_broker_addr = "";
int MQTT_broker_port = 1883;
String id = "";
MQTTClient mqtt = MQTTClient(256);
String MQTT_user = "";
String MQTT_pass = "";



#define pi 3.1416
double loadpower = 2000;


double Temperature = 0;


// def des Pin digitaux
const int Pin_ZC = 6, Pin_Trig = 7;
// marge Triac
const int marge_min = 400, marge_max = 10000 - 400;  // marge pour le declenchement du triac en us
//------------Interuptions------------//
// Timer interupt trig
hw_timer_t* Timer_Trig_on = NULL;   //creation compteur pour l'allumage
hw_timer_t* Timer_Trig_off = NULL;  //creation compteur pour l'extinction

void IRAM_ATTR Timer_Trig_on_ISR() {
  digitalWrite(Pin_Trig, HIGH);                // allumer trig
  timerRestart(Timer_Trig_off);                // preparer compteur pour l'extinction
  timerAlarm(Timer_Trig_off, 1000, false, 3);  // eteindre apres 1 000 cycles : 1000 / 10 MHz = 100us added a 0
}
void IRAM_ATTR Timer_Trig_off_ISR() {
  digitalWrite(Pin_Trig, LOW);  // allumer trig
}
// interupt ZC
int wait_time = 10000;
unsigned long ZC = 0;
void IRAM_ATTR zeroCrossing() {
  if (micros() - ZC > 2000) {            //debounce du ZC
    if (wait_time < marge_min) {         //Si temps d'attente trop proche limte (tot)
      digitalWrite(Pin_Trig, HIGH);      // laisser Trig allumé
    } else if (wait_time > marge_max) {  //Si temps d'attente trop proche limte (tardive)
      digitalWrite(Pin_Trig, LOW);       // laisser Trig eteint
    } else {
      timerRestart(Timer_Trig_on);                          // preparer compteur pour le delay
      timerAlarm(Timer_Trig_on, wait_time * 10, false, 3);  // eteindre apres wait_time x10 cycles : wait_time * 10 / 10 MHz = wait_time (en us)
    }
    ZC = micros();  //debounce du ZC
  }
}
//------------Fin Interuptions------------//

//------------int------------//
void setup() {
  pinMode(48, OUTPUT);
  digitalWrite(48, LOW);
  Serial.begin(115200);  //debuter la com série
  delay(1000);
  Serial.println("Serialbegun");
  preferences.begin("network", false);  // false = read/write mode
  Serial_conf();


  pinMode(Pin_Trig, OUTPUT);
  pinMode(Pin_ZC, INPUT_PULLUP);

  Wifibegin();
  Timer_Trig_on = timerBegin(10000000);  // demarage compteurs
  Timer_Trig_off = timerBegin(10000000);
  timerAttachInterrupt(Timer_Trig_on, &Timer_Trig_on_ISR);  // attacher compteurs aux fonction d'interuption
  timerAttachInterrupt(Timer_Trig_off, &Timer_Trig_off_ISR);
  attachInterrupt(digitalPinToInterrupt(Pin_ZC), zeroCrossing, RISING);


  MQTT_connect();
}
//------------Fin int------------//

double powerPercentage = 0.0;  //pourcentage de dump au demarrage
unsigned long last = 0;


void loop() {
  delay(150);
  mqtt.loop();
  wait_time = powerPercentage_to_wait(powerPercentage);
  show_data();
}







//Math
float precision = 0.000005;

int powerPercentage_to_wait(float Pwr_Percentage) {
  Pwr_Percentage = Pwr_Percentage / 100;  // decale power percenta
  //cycle_count = 0;
  float bornes[2] = { 0, pi };
  unsigned long calcTimeout = millis();
  while (millis() - calcTimeout < 5000) {
    float p_test = (bornes[1] + bornes[0]) / 2;
    float Pwr_Percentage_test = integrale_sin2_from_p_to_pi(p_test);
    //cycle_count += 1;
    if (Pwr_Percentage_test <= Pwr_Percentage + precision && Pwr_Percentage_test >= Pwr_Percentage - precision) {
      return p_test / pi * 10000;
    }
    if (Pwr_Percentage_test < Pwr_Percentage) {
      bornes[1] = p_test;
    } else if (Pwr_Percentage_test > Pwr_Percentage) {
      bornes[0] = p_test;
    }
  }
  return 0;
}

float integrale_sin2_from_p_to_pi(float p) {
  float Normalized_Pwr = 1 - (2 * p - sin(2 * p)) / (2 * pi);
  return Normalized_Pwr;
}













/*
//math:
int powerPercentage_to_wait(double pers) {
  pers = max(min(pers, 100.0), 0.0);
  return arcos(pers / 50 - 1) / 3.1415 * 10000;
}
float arcos(float x) {
  float negate = float(x < 0);
  float ret = -0.0187293;
  x = abs(x);
  ret = x * -0.0187293;
  ret += 0.0742610;
  ret *= x;
  ret -= 0.2121144;
  ret *= x;
  ret += 1.5707288;
  ret *= sqrt(1.0 - x);
  ret = ret - 2.0 * negate * ret;
  return negate * 3.14159265358979 + ret;
}*/
