/*
 * this sketch can control a simple drip irrigation system
 * the pump (a simple peristaltic pump can be used) is controlled by a mosfet
 * my pump works at 12V DC, and my mosfet (IRF530N) doesn't saturate at 3.3v,
 * so I built a pre-amplifier circuit with a simple NPN transistor for the
 * arduino nano output before the mosfet input.
 */

#define PUMP 2 // pump control pin (not to be connected directly to the pump)
#define IRRIGATION_TIME 3500 // 3.5 seconds (in milliseconds)
#define WAIT_TIME 1800000 // 30 minutes (in milliseconds)

void setup() {
  pinMode(PUMP, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // this sketch waits for a certain time and activates/deactivates the outputs
  // as it is a simple and single process, the delay() function won't harm other
  // running processes
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(PUMP, HIGH);
  delay(IRRIGATION_TIME);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(PUMP, LOW);
  delay(WAIT_TIME);
}
