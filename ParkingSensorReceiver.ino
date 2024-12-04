#include <RCSwitch.h>       // Knižnica pre ovládanie 433 MHz modulu
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> // Knižnica pre OLED displej

#define PIN_RECEIVER 4      // Pin na 433 MHz receiver
#define PIN_BUZZER 3        // Pin na bzučiak
#define SCREEN_WIDTH 128    // Šírka OLED displeja
#define SCREEN_HEIGHT 64    // Výška OLED displeja
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);

  // Nastavenie receiveru
  mySwitch.enableReceive(PIN_RECEIVER); // Nastav prijímací pin

  // Nastavenie bzučiaka
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);

  // Inicializácia OLED displeja
  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
    Serial.println(F("OLED init failed"));
    for (;;); // Zastav program, ak displej nefunguje
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void beepBuzzer(int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(delayTime);
    digitalWrite(PIN_BUZZER, LOW);
    delay(delayTime);
  }
}

void loop() {
  if (mySwitch.available()) {
    // Prijatie dát
    int distance = mySwitch.getReceivedValue();
    mySwitch.resetAvailable();

    if (distance == 0) {
      Serial.println("Error: No signal");
      return;
    }

    Serial.print("Received distance: ");
    Serial.println(distance);

    // Zobrazenie na OLED displeji
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Distance: ");
    display.print(distance);
    display.println(" cm");
    display.display();

    // Signalizácia bzučiakom
    if (distance >= 30 && distance <= 50) {
      digitalWrite(PIN_BUZZER, HIGH); // Neustále bzučanie
    } else if (distance >= 60 && distance <= 100) {
      digitalWrite(PIN_BUZZER, LOW); // Vypni bzučiak pred trojnásobným bzučaním
      beepBuzzer(3, 100); // Trojnásobné zabzučanie
    } else {
      digitalWrite(PIN_BUZZER, LOW); // Vypni bzučiak
    }
  }

  delay(100);
}
