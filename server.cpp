#include <LiquidCrystal_I2C.h>

//bekotes
const int ledPin = 1;
const int buzzerPin = 2;
const int lightSensorPin = 3;

//fenyerzekenyseg
const int lightThreshold = 500;

//valtozok
int PIN = 1111;
int code = 0;
bool houseAttacked = false;
bool alarmEnabled = true;

//lcd init
LiquidCrystal_I2C lcd(0x32, 16, 2);

void setup() {
  
  // lcd init
  lcd.begin(16, 2);
  lcd.print("init..");
  lcd.setCursor(0, 1);
  lcd.print("Alert sys");
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(lightSensorPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  int lightLevel = analogRead(lightSensorPin);

  if (lightLevel < lightThreshold) {
    if (alarmEnabled && !houseAttacked) {
      houseAttacked = true;
      lcd.clear();
      lcd.print("Intruder");
      lcd.setCursor(0, 1);
      lcd.print("alert!");

      Serial.println("attack");
      digitalWrite(ledPin, HIGH);
      tone(buzzerPin, 1000, 2000);
    }
  }
  else {
    if (houseAttacked) {
      houseAttacked = false;
      lcd.clear();
      lcd.print("Alert System");
      lcd.setCursor(0, 1);
      lcd.print("Init..");

      Serial.println("secured");
      digitalWrite(ledPin, LOW);
      noTone(buzzerPin);
    }
  }

  if (Serial.available() > 0) {
    code = Serial.parseInt();

    if (code == pinCode) {
      alarmEnabled = false;
      Serial.println("Kiriasztva..");
    }
    else {
      Serial.println("Helytelen PIN!");
    }
  }
}
