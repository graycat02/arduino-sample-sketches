/*
 * made by graycat02
 * 
 * This sketch purpose is to control some analog RGB leds. The color presets are defined
 * via programming (hardcoded ;) ) and you can change or skip colors with a simple button
 * pin defined.
 * It's designed to be run in the Attiny85 chip board, but can be adapted to other
 * projects and boards, like the Arduino nano (for example). When using the Attiny85
 * all-in-one board which includes the USB port and programmer, take care that there is
 * no interference with the pins used for the usb connection (P0 and P2) and the other
 * components.
 */
 
#define DEBOUNCE_PRESS 80
#define DEBOUNCE_RELEASE 80
#define COLOR_PRESET colors_minecraft
  // by changing this setting to some of the arrays' names below you can apply color schemes easily
#define STARTUP_BLINK true
#define DEBUG false

const int pinR = 38;
const int pinG = 39;
const int pinB = 40;
const int buttonPin = 0;

// {R, G, B} -> (0 to 255 values)
int colors_default[][3] = {
  {0, 0, 0}, // off
  {255, 0, 0},
  {0, 255, 0},
  {0, 0, 255},
  {255, 255, 0},
  {0, 255, 255},
  {255, 0, 255},
  {255, 255, 255}
};
int colors_minecraft[][3] = {
  /* the combinations below are manually calibrated for my personal build, including the
   * resistors combinations, leds, and other physical components.
   */
  {0, 0, 0}, // off
  {234, 126, 62}, // iron
  {190, 116, 0}, // gold
  {14, 250, 242}, // diamond
  {5, 248, 10}, // emerald
  {250, 2, 0}, // redstone
  {246, 72, 16}, // copper
  {0, 6, 247}, // lapislazuli
  {130, 46, 248}, // amethyst
  {245, 225, 208}, // quartz
  {236, 72, 8}, /// orange
  {248, 38, 174} /// pink
};

int currentColorIndex = 0;
int numColors = sizeof(COLOR_PRESET) / sizeof(COLOR_PRESET[0]); // number of RGB colors (not single cells), so we divide into individual cell size

void setup() {
  pinMode(pinR, OUTPUT); // Red
  pinMode(pinG, OUTPUT); // Green
  pinMode(pinB, OUTPUT); // Blue
  pinMode(buttonPin, INPUT_PULLUP); // now in v2 I use the internal pull-up resistor of the ESP32-S2 mini
  
  if(DEBUG){
    // color channels check
    setColor(colors_default[1]);
    delay(300);
    setColor(colors_default[2]);
    delay(300);
    setColor(colors_default[3]);
    delay(300);
  
    // fade to check PWM on all channels
    setColor(colors_default[0]); // off
    // red
    for (int i = 0; i <= 255; i++) {
      analogWrite(pinR, i);
      delay(10);
    }
    delay(500);
    analogWrite(pinR, 0);
    delay(500);
  
    // green
    for (int i = 0; i <= 255; i++) {
      analogWrite(pinG, i);
      delay(10);
    }
    delay(500);
    analogWrite(pinG, 0);
    delay(500);  
  
    // blue
    for (int i = 0; i <= 255; i++) {
      analogWrite(pinB, i);
      delay(10);
    }
    delay(500);
    analogWrite(pinB, 0);
    delay(500);
  }
  
  // startup blink
  if(STARTUP_BLINK){
    analogWrite(pinG, 255);
    delay(100);
    analogWrite(pinG, 0);
    delay(100);
    analogWrite(pinB, 255);
    delay(100);
    analogWrite(pinB, 0);
    delay(100);
  }
  
  setColor(COLOR_PRESET[currentColorIndex]);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    delay(DEBOUNCE_PRESS);

    while (digitalRead(buttonPin) == HIGH) {}
    delay(DEBOUNCE_RELEASE);

    currentColorIndex = (currentColorIndex + 1) % numColors; // return to 0 if end has been reached
    setColor(COLOR_PRESET[currentColorIndex]);
  }
}

void setColor(int color[3]) {
  analogWrite(pinR, color[0]);
  analogWrite(pinG, color[1]);
  analogWrite(pinB, color[2]);
}
