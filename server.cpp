#include "Arduino_SensorKit.h"
#include "Wire.h"

//bekotes
const int lightSensorPin = 3;
const int buttonPin = 4;
const int ledPin = 6;
const int buzzerPin = 5;

//fenyerzekenyseg
const int lightThreshold = 500;

//valtozok
int PIN = 1111;
int code = 0;
bool houseAttacked = false;
bool alarmEnabled = true;

void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(lightSensorPin, INPUT);

  Oled.begin();
  Oled.setFlipMode(true);

  Oled.clear();
  Oled.setFont(u8x8_font_chroma48medium8_r);
  Oled.setCursor(0,0);
  Oled.print("Welcome home!");

  Serial.begin(9600);
}

void loop() {
  int lightLevel = analogRead(lightSensorPin);

  if (lightLevel < lightThreshold) {
    if (alarmEnabled && !houseAttacked) {
      houseAttacked = true;
      Oled.clear();
      Oled.setCursor(0, 1);
      Oled.print("Alert System");
      Oled.setCursor(0, 2);
      Oled.print("Intruder!");

      Serial.println("attack");
      digitalWrite(ledPin, HIGH);
      tone(buzzerPin, 1000, 2000);
    }
  }
  else {
    if (houseAttacked) {
      houseAttacked = false;
      Oled.clear();
      Oled.print("Alert System");
      Oled.setCursor(0, 1);
      Oled.print("Safe!");

      Serial.println("secured");
      digitalWrite(ledPin, LOW);
      noTone(buzzerPin);
    }
  }

  if (Serial.available() > 0) {
    code = Serial.parseInt();

    if (code == pinCode) {
      alarmEnabled = false;
      Serial.println("Successfully Unarmed..");
    }
    else {
      Serial.println("Incorrect PIN!");
    }
  }
}
