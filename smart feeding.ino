#define BLYNK_TEMPLATE_ID "TMPLt6f2j0ON"
#define BLYNK_DEVICE_NAME "pet feeder"
#define BLYNK_AUTH_TOKEN "1N38iZx2HS53nsm1bab1ydlj-oe7uaso"

#include <Servo.h>


#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

Servo servo;

char auth[] = "1N38iZx2HS53nsm1bab1ydlj-oe7uaso";//Enter your Blynk auth token

char ssid[] = "UIU-STUDENT";//Enter your WIFI name

char pass[] = "12345678";//Enter your WIFI password

BLYNK_WRITE(V2){

  servo.write(param.asInt());

  }

  void setup() {

    Serial.begin(9600);

      servo.attach(2);

        Blynk.begin(auth, ssid, pass);

        }

void loop() {

  Blynk.run();

  }