#include <LiquidCrystal.h>
#include "DHT.h"
#include <SoftwareSerial.h>
#include <Servo.h>
#define DHTPIN 2
#define DHTTYPE DHT11
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);
Servo servo_il1, servo_il2, servo_il3, servo_il4;
int bluetoothTx = 10;
int bluetoothRx = 11;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
  servo_il1.attach(5);
  servo_il2.attach(6);
  servo_il3.attach(9);
  servo_il4.attach(3);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  bluetooth.begin(9600);
  lcd.clear();

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    lcd.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  lcd.setCursor(0, 0);
  lcd.print(F("sicaklik:"));
  lcd.print(t);
  lcd.println(F("'C "));
  lcd.setCursor(0, 1);
  lcd.print(F("baglanmaya calisiyor"));
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true); delay(1000);
  if (bluetooth.available() >= 2 ) {
    int servopos = bluetooth.read();
    int servopos1 = bluetooth.read();
    int servo_durum = (servopos1 * 256) + servopos;
    if (servo_durum >= 1000 && servo_durum <= 1135) // Keep leave
    { lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(F("baglandi"));
      lcd.setCursor(0, 0);
      lcd.print(F("tut birak calisiyor"));
      int servo1 = servo_durum; delay(20);
      servo1 = map(servo1, 1000, 1135, 0, 135); delay(20);
      servo_il1.write(servo1); delay(20);
      digitalWrite(13, HIGH); delay(20);
      digitalWrite(13, LOW); delay(20);
      digitalWrite(12, HIGH); delay(20);
      digitalWrite(12, LOW); delay(20);
    }
    if (servo_durum >= 2000 && servo_durum <= 2090) { // right left
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(F("baglandi"));
      lcd.setCursor(0, 0);
      lcd.print(F("sag sol calisiyor"));
      int servo2 = servo_durum;
      servo2 = map(servo2, 2000, 2090, 0, 90); delay(20);
      servo_il2.write(servo2); delay(20);
      digitalWrite(13, HIGH); delay(20);
      digitalWrite(13, LOW); delay(20);
    }
    if (servo_durum >= 3000 && servo_durum <= 3180) { // up down
      lcd.clear();  lcd.setCursor(0, 1);
      lcd.print(F("baglandi"));
      lcd.setCursor(0, 0);
      lcd.print(F("yukari asagi calisiyor"));
      int servo3 = servo_durum;
      servo3 = map(servo3, 3000, 3180, 0, 180); delay(20);
      servo_il3.write(servo3); delay(20);
      digitalWrite(13, HIGH); delay(20);
      digitalWrite(13, LOW); delay(20);
    }
    if (servo_durum >= 4000 && servo_durum <= 4120) { // Further back
      lcd.clear();  lcd.setCursor(0, 1);
      lcd.print(F("baglandi"));
      lcd.setCursor(0, 0);
      lcd.print(F("ileri geri calisiyor"));
      int servo4 = servo_durum;
      servo4 = map(servo4, 4000, 4120, 0, 120); delay(20);
      servo_il4.write(servo4); delay(20);
      digitalWrite(13, HIGH); delay(20);
      digitalWrite(13, LOW); delay(20);
    }
  }
}
