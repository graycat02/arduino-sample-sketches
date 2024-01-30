#include <Servo.h>

// pin definition
const int trigPin = 4;
const int echoPin = 3;
const int servoPin = 2;

Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin); // link servo with corresponding pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;

  // generate ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // pulse width
  digitalWrite(trigPin, LOW);

  // measure ultrasonic pulse time of flight
  duration = pulseIn(echoPin, HIGH);

  // convert time of flight to distance
  distance = (duration / 2) / 29.1;
  // 29.1 for cm, 74 for inch

  int servoAngle = map(distance, 0, 100, 0, 180);

  // print distance on serial port
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // move servo
  myServo.write(servoAngle);

  delay(200); // delay until next cycle/measure
}
