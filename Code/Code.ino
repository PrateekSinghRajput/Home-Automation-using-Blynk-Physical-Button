//Prateek
//https://justdoelectronics.com
//https://www.youtube.com/c/JustDoElectronics/videos

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


BlynkTimer timer;

void checkPhysicalButton();

int relay1State = LOW;
int pushButton1State = HIGH;
int relay2State = LOW;
int pushButton2State = HIGH;
int relay3State = LOW;
int pushButton3State = HIGH;
int relay4State = LOW;
int pushButton4State = HIGH;

#define AUTH "rw43t6t744wsggt6eq4tghse"
#define WIFI_SSID "Justdoelectronics"
#define WIFI_PASS "justdoelectronics"

#define SERVER "blynk-cloud.com "
#define PORT 8442

#define RELAY_PIN_1 D7
#define RELAY_PIN_2 D6
#define RELAY_PIN_3 D5
#define RELAY_PIN_4 D4

#define PUSH_BUTTON_1 D1
#define PUSH_BUTTON_2 D2
#define PUSH_BUTTON_3 D3
#define PUSH_BUTTON_4 D0

#define VPIN_BUTTON_1 V12
#define VPIN_BUTTON_2 V13
#define VPIN_BUTTON_3 V14
#define VPIN_BUTTON_4 V15

#define OTA_HOSTNAME "Home_Automation"


BLYNK_CONNECTED() {

  Blynk.syncVirtual(VPIN_BUTTON_1);
  Blynk.syncVirtual(VPIN_BUTTON_2);
  Blynk.syncVirtual(VPIN_BUTTON_3);
  Blynk.syncVirtual(VPIN_BUTTON_4);
}
BLYNK_WRITE(VPIN_BUTTON_1) {
  relay1State = param.asInt();
  digitalWrite(RELAY_PIN_1, relay1State);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  relay2State = param.asInt();
  digitalWrite(RELAY_PIN_2, relay2State);
}
BLYNK_WRITE(VPIN_BUTTON_3) {
  relay3State = param.asInt();
  digitalWrite(RELAY_PIN_3, relay3State);
}
BLYNK_WRITE(VPIN_BUTTON_4) {
  relay4State = param.asInt();
  digitalWrite(RELAY_PIN_4, relay4State);
}

void checkPhysicalButton() {
  if (digitalRead(PUSH_BUTTON_1) == LOW) {

    if (pushButton1State != LOW) {
      relay1State = !relay1State;
      digitalWrite(RELAY_PIN_1, relay1State);
      Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
    }
    pushButton1State = LOW;
  } else {
    pushButton1State = HIGH;
  }

  if (digitalRead(PUSH_BUTTON_2) == LOW) {

    if (pushButton2State != LOW) {
      relay2State = !relay2State;
      digitalWrite(RELAY_PIN_2, relay2State);

      Blynk.virtualWrite(VPIN_BUTTON_2, relay2State);
    }
    pushButton2State = LOW;
  } else {
    pushButton2State = HIGH;
  }

  if (digitalRead(PUSH_BUTTON_3) == LOW) {

    if (pushButton3State != LOW) {
      relay3State = !relay3State;
      digitalWrite(RELAY_PIN_3, relay3State);
      Blynk.virtualWrite(VPIN_BUTTON_3, relay3State);
    }
    pushButton3State = LOW;
  } else {
    pushButton3State = HIGH;
  }

  if (digitalRead(PUSH_BUTTON_4) == LOW) {

    if (pushButton4State != LOW) {
      relay4State = !relay4State;
      digitalWrite(RELAY_PIN_4, relay4State);
      Blynk.virtualWrite(VPIN_BUTTON_4, relay4State);
    }
    pushButton4State = LOW;
  } else {
    pushButton4State = HIGH;
  }
}

void setup() {

  Serial.begin(115200);
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS, "blynk-cloud.com", 8442);
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.begin();

  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_1, relay1State);


  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(PUSH_BUTTON_2, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_2, relay2State);


  pinMode(RELAY_PIN_3, OUTPUT);
  pinMode(PUSH_BUTTON_3, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_3, relay3State);


  pinMode(RELAY_PIN_4, OUTPUT);
  pinMode(PUSH_BUTTON_4, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_4, relay4State);

  timer.setInterval(500L, checkPhysicalButton);
}

void loop() {
  Blynk.run();
  ArduinoOTA.handle();
  timer.run();
}
