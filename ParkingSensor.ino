#define PIN_TRIG1 2
#define PIN_ECHO1 3
#define PIN_BUZZER 4


// Please DUPLICATE SOME CODE PATH TO ESTABLISH 4 SENSORS INSTEAD OF 1 !
// Cuz its MORE PRECISELY !
// DRIVE CAREFULLY !


void setup() {
  Serial.begin(115200);

  pinMode(PIN_TRIG1, OUTPUT);
  pinMode(PIN_ECHO1, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  digitalWrite(PIN_BUZZER, LOW);
}

float measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int duration = pulseIn(echoPin, HIGH);
  float distance = duration / 58.0;      
  return distance;
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
  float distance1 = measureDistance(PIN_TRIG1, PIN_ECHO1);

  Serial.print("Distance Sensor: ");
  Serial.println(distance1);

  bool buzzerActive = false;

  if (distance1 >= 20 && distance1 <= 40) {
    beepBuzzer(3, 50);
  }

  if (distance1 >= 10 && distance1 <= 19) {
    buzzerActive = true;
  }

  if (distance1 >= 41 && distance1 <= 70) {
    beepBuzzer(3, 100);
  }

  if (distance1 >= 71 && distance1 <= 90) {
    beepBuzzer(3, 300);
  }

  if (buzzerActive) {
    digitalWrite(PIN_BUZZER, HIGH);
  } else {
    digitalWrite(PIN_BUZZER, LOW);
  }

  delay(100);
}
