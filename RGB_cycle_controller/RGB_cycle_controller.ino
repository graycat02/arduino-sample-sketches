
const int pinR = 1;
const int pinG = 3;
const int pinB = 4;
const int buttonPin = 0;

int colors[][3] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {255, 255, 0},
    {0, 255, 255},
    {255, 0, 255},
    {255, 255, 255}
};

int currentColorIndex = 0;
int numColors = sizeof(colors) / sizeof(colors[0]);

void setup() {
    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(buttonPin, INPUT);

    setColor(colors[currentColorIndex]);
}

void loop() {
    if (digitalRead(buttonPin) == HIGH) {
        delay(50); // Debounce

        while (digitalRead(buttonPin) == HIGH) {}

        currentColorIndex = (currentColorIndex + 1) % numColors;
        setColor(colors[currentColorIndex]);
    }
}

void setColor(int color[3]) {
    analogWrite(pinR, color[0]);
    analogWrite(pinG, color[1]);
    analogWrite(pinB, color[2]);
}
