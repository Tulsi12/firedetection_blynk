#define BLYNK_TEMPLATE_ID "TMPLw7FvsBsD"
#define BLYNK_DEVICE_NAME "falme"
#define BLYNK_AUTH_TOKEN "VPG4Wj76kSLJ0H7p7w0mh0sNClRtvSfM"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Tulsi";
char pass[] = "123456789";
BlynkTimer timer;
int pinValue = 0;
#define LED1 D1
#define LED2 D2
#define Buzzer D3
#define Sensor D0

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Sensor, INPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, notifiaction);
}
BLYNK_WRITE(V0) {
  pinValue = param.asInt();
}
void notifiaction() {
  int sensor = digitalRead(Sensor);
  digitalWrite(Buzzer, HIGH);
  if (pinValue == 1) {
    Serial.println("System is ON");
    if (sensor == 1) {
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, LOW);
      digitalWrite(Buzzer, LOW);
    } else if (sensor == 0) {
      Blynk.logEvent("flame","WARNING! A fire was detected"); //flame is a code of event in blynk
      digitalWrite(LED2, LOW);
      digitalWrite(LED1, HIGH);
      digitalWrite(Buzzer, HIGH);
    }
  } else if (pinValue == 0) {
    Serial.println("System is OFF");
  }
}

void loop() {
  Blynk.run();
  timer.run();
}
