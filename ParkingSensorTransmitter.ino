#include <RCSwitch.h> // Knižnica pre ovládanie 433 MHz modulu

#define PIN_TRIG 2
#define PIN_ECHO 3
#define PIN_TRANSMITTER 4 // Pin na 433 MHz transmitter

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);

  // Nastavenie HC-SR04
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  // Nastavenie transmitteru
  mySwitch.enableTransmit(PIN_TRANSMITTER); // Nastav vysielací pin
}

float measureDistance() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  int duration = pulseIn(PIN_ECHO, HIGH);
  float distance = duration / 58.0; // Prepočet na cm
  return distance;
}

void loop() {
  float distance = measureDistance();

  // Konverzia vzdialenosti na celé číslo pre odoslanie
  int distanceInt = (int)distance;

  // Odoslanie vzdialenosti cez 433 MHz transmitter
  mySwitch.send(distanceInt, 24); // Posielaj 24-bitové celé číslo
  Serial.print("Sent distance: ");
  Serial.println(distanceInt);

  delay(500); // Krátke oneskorenie
}
