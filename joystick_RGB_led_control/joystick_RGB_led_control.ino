/*
 * made by graycat02
 * 
 * This sketch controls a single NeoPixel RGB LED (from Lolin S3 ESP32 board)
 * from a joystick input.
 * Y axis selects R/G/B color and X axis adjusts brightness of selected color.
 */

#include <Adafruit_NeoPixel.h>

#define LED_PIN 38
#define X_PIN 12
#define Y_PIN 11
#define ANALOGREAD_MAX 4096

Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);

int r, g, b; // color data for the pixel
int x_input, y_input;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
  pixels.begin();
  Serial.begin(9600);
}

void loop() {

  // get input from joystick
  x_input = analogRead(X_PIN);
  y_input = analogRead(Y_PIN);

  //converts input from 0-ANALOGREAD_MAX to 0-255 scale
  if(y_input < ANALOGREAD_MAX/3){ // select Red
    r = x_input * (256/ANALOGREAD_MAX);
  } else if(y_input > ANALOGREAD_MAX*2/3){ // select Blue
    b = (float)x_input * (256/ANALOGREAD_MAX);
  } else{ // select Green
    g = x_input * (256/ANALOGREAD_MAX);
  }

  Serial.printf("R:%i G:%i B:%i y:%i x:%i\n", r, g, b, y_input, analogRead(X_PIN));

  // apply color to LED
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(r, g, b)); // receives R, G and B channels and applies to LED
  pixels.show();
  
  delay(500);
}
