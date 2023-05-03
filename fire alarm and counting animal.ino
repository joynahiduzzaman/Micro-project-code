#include "DHT.h"
#include <LiquidCrystal.h>
#define DHTPIN 2       // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // DHT 11
#define IR 3           //ir pin
#define led 13         //led pin
#define trig A3        // trigger pin
#define echo A2        // echo pin
#define buzzer 22
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  // rs , en, d4, d5, d6, d7


long dis_a = 0;
int flag1 = 0, flag2 = 0;
int person = -1;  //counting person initialization
int pos = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(IR, INPUT);
  pinMode(led, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  dht.begin();
  lcd.begin(16, 2);     // set up the LCD's number of columns and rows:
  analogWrite(10, 70);  //v0
  lcd.setCursor(0, 0);
  lcd.print("     Welcome    ");
  delay(1000);
  lcd.clear();
}



void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  Serial.print(F("F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("C "));
  Serial.print(hif);
  Serial.println(F("F"));

  long time;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(2);
  time = pulseIn(echo, HIGH);
  dis_a = time / 29 / 2;
  delay(30);
  int statIRSensor = digitalRead(IR);
  Serial.print("da: ");
  Serial.println(dis_a);
  Serial.print("ir: ");
  Serial.println(statIRSensor);
  if (dis_a < 90 && flag1 == 0) {
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    flag1 = 1;
    if (flag2 == 0) {
      person = person + 1;
      Serial.print("Total person : ");
      Serial.println(person);
    }
  }

  if (statIRSensor == 0 && flag2 == 0) {
    flag2 = 1;
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    if (flag1 == 0) {
      if (person >= 1)
        person = person - 1;
      Serial.print("Total person : ");
      Serial.println(person);

    }
  }
  if (dis_a > 90 && statIRSensor == 0 && flag1 == 1 && flag2 == 1) {
    flag1 = 0, flag2 = 0;
    delay(1000);
  }
  lcd.setCursor(2, 0);
  lcd.print("Have  Person");
  lcd.setCursor(7, 1);
  lcd.print(person);

  if (t > 31 && hic > 40) {
    digitalWrite(buzzer, HIGH);
    delay(20);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    lcd.write("     DANGER     ");
  }
      Serial.print("Total person : ");
      Serial.println(person);


}
