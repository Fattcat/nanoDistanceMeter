#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define trigPin 9
#define echoPin 8


// Connection Schematics
// 
// OLED --> Arduino Nano
// 
// VCC - 5V
// GND - GND
// SCL - A5
// SDA - A4
// 
// Radar --> Arduino Nano
// 
// VCC - 5V
// GND - GND
// ECHO - D8
// TRIG - D9

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // adresa 0x3C (128x64)
  display.clearDisplay();
  display.setTextWrap(false); // Táto riadka sa pridala pre zakázanie pretekania textu na ďalšie riadky
}

void loop() {
  float duration;
  float distance_cm;
  float distance_in;

  digitalWrite(trigPin, LOW); //PULSE ___|---|___
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance_cm = (duration / 2) / 29.1;
  distance_in = (duration / 2) / 73.914;

  display.setCursor(20, 0); // oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Vzdialenost je :");

  display.setCursor(10, 15); // oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print(distance_cm, 1); // Zmena: Odstavenie desatinných miest
  display.setCursor(90, 15);
  display.setTextSize(2);
  display.println(" cm");

  display.setCursor(10, 45); // oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print(distance_in, 1); // Zmena: Odstavenie desatinných miest
  display.setCursor(90, 45);
  display.setTextSize(2);
  display.println(" in");

  display.display();

  delay(500);
  display.clearDisplay();

  Serial.println(distance_cm, 1); // Zmena: Odstavenie desatinných miest
  Serial.println(distance_in, 1); // Zmena: Odstavenie desatinných miest
}
