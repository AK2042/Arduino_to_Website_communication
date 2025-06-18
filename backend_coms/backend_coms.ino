#define buzzerPin 9
#define trigPin 6
#define echoPin 7
#define ldrPin 5
const int ledPins[] = {A2,A3,A4,A5};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) pinMode(ledPins[i], OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd.startsWith("led")) {
      int ledIndex = cmd.charAt(3) - '1';
      if (ledIndex >= 0 && ledIndex < 4) {
        digitalWrite(ledPins[ledIndex], cmd.endsWith("on") ? HIGH : LOW);
        Serial.println("OK");
      }
    } else if (cmd == "buzzer_on") {
      digitalWrite(buzzerPin, HIGH);
      Serial.println("OK");
    } else if (cmd == "buzzer_off") {
      digitalWrite(buzzerPin, LOW);
      Serial.println("OK");
    } else if (cmd == "ultrasonic?") {
      long duration;
      float distance;
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2;
      Serial.println(distance);
    } else if (cmd == "ldr?") {
      int ldrValue = analogRead(ldrPin);
      Serial.println(ldrValue);
    } else if (cmd == "get_data") {
      // Read both sensors and return a JSON string
      long duration;
      float distance;
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2;

      int ldrValue = analogRead(ldrPin);

      // Manually create a JSON string
      Serial.print("{\"distance\":");
      Serial.print(distance, 1);
      Serial.print(",\"ldr\":");
      Serial.print(ldrValue);
      Serial.println("}");
    }
  }
}
