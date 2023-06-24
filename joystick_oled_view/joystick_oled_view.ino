#include <GyverOLED.h>

#define VX_PIN 12
#define VY_PIN 11

GyverOLED<SSH1106_128x64> oled;

int input_x, input_y;

void setup() {
  Serial.begin(9600);
  oled.init();
  oled.clear();
  oled.update();
  oled.home();

  pinMode(VX_PIN, INPUT);
  pinMode(VY_PIN, INPUT);
}

void loop() {
  oled.fastLineH(32, 32, 96); // H position, V start and end
  oled.fastLineV(64, 0, 63); // V position, H start and end

  input_x = analogRead(VX_PIN); //get raw data from pins
  input_y = analogRead(VY_PIN);
  Serial.printf("\nRAW: %i, %i\n", input_x, input_y);
  //scale input from 0-4095 to 0-63 scale (screen heigth)
  input_x = input_x*64/4096;
  input_y = input_y*64/4096;
  Serial.printf("Scale: %i, %i\n", input_x, input_y);
  
  oled.circle(input_x+32, input_y, 1);  // center X and Y, radius

  oled.update();
  oled.clear();
  oled.home();
}
