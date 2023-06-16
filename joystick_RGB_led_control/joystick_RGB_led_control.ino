/*
 * made by graycat02
 * 
 * This sketch controls a single NeoPixel RGB LED (from Lolin S3 ESP32 board)
 * from a joystick input.
 * Y axis selects R/G/B color and X axis adjusts brightness of selected color.
 */

#define LED_PIN 38
#define X_PIN 12
#define Y_PIN 11

int r, g, b; // color data for the pixel
int y_input;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
}

void loop() {
  y_input = analogRead(Y_PIN);
  if(y_input < 340){ // select Red
    r = analogRead(X_PIN) * (256/1024); // converts input from 0-1023 to 0-255 scale
  } else if(y_input > 680){ // select Blue
    b = analogRead(X_PIN) * (256/1024);
  } else{ // select Green
    g = analogRead(X_PIN) * (256/1024);
  }

  
}
