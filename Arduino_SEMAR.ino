#define BLYNK_TEMPLATE_ID "TMPL6YZS6x4FW"
#define BLYNK_TEMPLATE_NAME "SEMAR"
#define BLYNK_AUTH_TOKEN "Z2rxBeMHjztCVC3ijJyuSuF8meTTr69y"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>

const int pulsePin = A0; // Pin for pulse sensor, you can change
const float refVolt = 5.0;
int pulseValue;
int pulseBpm, bloodGlucose, cholesterol, asamUratPria, asamUratWanita;

// Blynk authentication
char auth[] = "fill with your blynk auth";
char ssid[] = "fill with your wifi";
char pass[] = "fill with your password wifi";
BlynkTimer timer;

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Blynk.begin(auth, ssid, pass);
  while (!Blynk.connected()) {
    Serial.println("Connecting to Blynk...");
    delay(1000);
  }
  Serial.println("Connected to Blynk");

  pinMode(pulsePin, INPUT);
}

void loop() {
  pulseValue = analogRead(pulsePin);
  pulseBpm = 12000 / pulseValue;

  Serial.println(pulseValue);
  bloodGlucose = (pulseBpm * 140) / 120;
  cholesterol = (pulseBpm * 230) / 120;
  asamUratPria = (pulseBpm * 10) / 120;
  asamUratWanita = (pulseBpm * 8) / 120;


    Serial.print("Heart rate: ");
    Serial.print(pulseBpm);
    Serial.println(" BPM");

    Serial.print("Blood Glucose: ");
    Serial.print(bloodGlucose);
    Serial.println(" mg/dl");

    Serial.print("Cholesterol: ");
    Serial.print(cholesterol);
    Serial.println(" mg/dl");

    Serial.print("Asam Urat Pria: ");
    Serial.print(asamUratPria);
    Serial.println(" mg/dl");

    Serial.print("Asam Urat Wanita: ");
    Serial.print(asamUratWanita);
    Serial.println(" mg/dl");

    Blynk.virtualWrite(V0, pulseBpm);
    Blynk.virtualWrite(V1, bloodGlucose);
    Blynk.virtualWrite(V2, cholesterol);
    Blynk.virtualWrite(V3, asamUratPria);
    Blynk.virtualWrite(V4, asamUratWanita);

    //for debugging in your IDE
    String messagePulse = "Heart rate from Pulse: " + String(pulseBpm) + " BPM";
    String glucose = "Blood glucose from Pulse: " + String((pulseBpm * 140) / 120) + " mg/dl";
    Serial.println(messagePulse);
    delay(1000);

  Blynk.run();
}

