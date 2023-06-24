#include <GyverOLED.h>

const int Trigger = 14;   // digital pin for the sensor trigger
const int Echo = 13;   // digital pin for the sensor echo

GyverOLED<SSH1106_128x64> oled;

void setup() {
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trigger, LOW);
  oled.init();
}

void loop()
{

  long t; // time it takes for the echo to arrive
  long d; // distance in centimeters

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          // send 10us pulse
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); // we get the pulse width
  d = t/59;             // we scale time to a distance in cm
  
  Serial.print("Distance: ");Serial.print(d);Serial.println("cm");

  oled.clear();
  oled.home();
  oled.print("Distance: ");oled.print(d);oled.println("cm");
  oled.update();

  delay(100);
}