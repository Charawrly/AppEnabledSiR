 
// Servo parameters.  Pin MUST be 1 or 4 on a Trinket.  Servo position
// is specified in raw timer/counter ticks (1 tick = 0.128 milliseconds).
// Servo pulse timing is typically 1-2 ms, but can vary slightly among
// servos, so you may need to tweak these limits to match your reality.
#define SERVO_PIN  4 // Pins 1 or 4 are supported on Trinket
#define SERVO_MIN  4 // ~1 ms pulse
#define SERVO_MAX 26 // ~2 ms pulse
 

Adafruit_TiCoServo servo;
 
void setup(void) {
#if (F_CPU == 16000000L)
  // 16 MHz Trinket requires setting prescale for correct timing.
  // This MUST be done BEFORE servo.attach()!
  clock_prescale_set(clock_div_1);
#endif
  servo.attach(SERVO_PIN);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}
 
uint32_t lastLookTime = 0; // Time of last head-turn
 
void loop(void) {
 
  unsigned long t = millis(); // Current time
 
  // If more than 1/2 second has passed since last head turn...
  if((t - lastLookTime) > 500) {
    if(random(10) == 0) { // There's a 1-in-10 chance...
      // ...of randomly moving the head in a new direction:
      servo.write(random(SERVO_MIN, SERVO_MAX));
      lastLookTime = t;   // Save the head-turn time for future reference
    }
  }
 
  // Unrelated to head-turn check,
  if(random(10) == 0) { // there's a 1-in-10 chance...
    // ...of an "eye blink":
    digitalWrite(LED_PIN, LOW);  // The LED turns OFF
    delay(random(50, 250));      // for just a short random moment
    digitalWrite(LED_PIN, HIGH); // then back ON
  }
 
  delay(100); // Repeat loop() about 10 times/second
}
