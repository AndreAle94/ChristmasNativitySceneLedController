/**
 *  Arduino led controller per presepe
 */

#define PIN_SUN 9
#define PIN_STARS 10
#define PIN_HOUSES 11

#define TOTAL_TIME 60000
#define END_TIME_P1 15000
#define END_TIME_P2 30000
#define END_TIME_P3 45000
#define END_TIME_P4 60000

#define TIME_FADE_IN_SUN_VALUE 2000
#define TIME_FADE_OUT_SUN_VALUE 2000
#define TIME_FADE_IN_STARS_VALUE 2000
#define TIME_FADE_OUT_STARS_VALUE 2000
#define TIME_FADE_IN_HOUSES_VALUE 2000
#define TIME_FADE_OUT_HOUSES_VALUE 2000

#define TIME_FADE_IN_SUN_OFFSET 0
#define TIME_FADE_OUT_SUN_OFFSET 0
#define TIME_FADE_IN_STARS_OFFSET 0
#define TIME_FADE_OUT_STARS_OFFSET 0
#define TIME_FADE_IN_HOUSES_OFFSET 0
#define TIME_FADE_OUT_HOUSES_OFFSET 0

#define TOTAL_PULSE 4000
#define TIME_PULSE_OFFSET 2500
#define TIME_PULSE_DOWN 3250
#define PULSE_MIN_VALUE 64

// declare global variables
unsigned long startTime = 0;
unsigned long pulseTime = 0;
float percentage = 0;

void setup() {
  // preconfigure pin mode
  pinMode(PIN_SUN, OUTPUT);
  pinMode(PIN_STARS, OUTPUT);
  pinMode(PIN_HOUSES, OUTPUT);
  // set initial state for each pin
  analogWrite(PIN_SUN, 0);
  analogWrite(PIN_STARS, 255);
  analogWrite(PIN_HOUSES, 0);
  // initialize the start time
  startTime = millis();
}

void loop() {
  // here we can start the logic
  unsigned long currentTime = millis();
  unsigned long time = (currentTime - startTime) % TOTAL_TIME;
  float percentage = 0;
  if (time >= 0 && time < END_TIME_P1) {
    // calculate sun fade in percentage
    if (time < TIME_FADE_IN_SUN_OFFSET) {
      analogWrite(PIN_SUN, 0);
    } else if (time < TIME_FADE_IN_SUN_OFFSET + TIME_FADE_IN_SUN_VALUE) {
      percentage = ((float) time - TIME_FADE_IN_SUN_OFFSET) / TIME_FADE_IN_SUN_VALUE;
      analogWrite(PIN_SUN, percentage * 255);
    } else {
      analogWrite(PIN_SUN, 255);
    }
    // calculate stars fade out percentage
    if (time < TIME_FADE_OUT_STARS_OFFSET) {
      analogWrite(PIN_STARS, 255);
    } else if (time < TIME_FADE_OUT_STARS_OFFSET + TIME_FADE_OUT_STARS_VALUE) {
      percentage = ((float) time - TIME_FADE_OUT_STARS_OFFSET) / TIME_FADE_OUT_STARS_VALUE;
      analogWrite(PIN_STARS, 255 - (percentage * 255));
    } else {
      analogWrite(PIN_STARS, 0);
    }
    // always set houses off
    analogWrite(PIN_HOUSES, 0);
  } else if (time >= END_TIME_P1 && time < END_TIME_P2) {
    // calculate houses fade in percentage
    if (time < END_TIME_P1 + TIME_FADE_IN_HOUSES_OFFSET) {
      analogWrite(PIN_HOUSES, 0);
    } else if (time < END_TIME_P1 + TIME_FADE_IN_HOUSES_OFFSET + TIME_FADE_IN_HOUSES_VALUE) {
      percentage = ((float) time - (END_TIME_P1 + TIME_FADE_IN_HOUSES_OFFSET)) / TIME_FADE_IN_HOUSES_VALUE;
      analogWrite(PIN_HOUSES, percentage * 255);
    } else {
      analogWrite(PIN_HOUSES, 255);
    }
    // calculate sun fade out percentage
    if (time < END_TIME_P1 + TIME_FADE_OUT_SUN_OFFSET) {
      analogWrite(PIN_SUN, 255);
    } else if (time < END_TIME_P1 + TIME_FADE_OUT_SUN_OFFSET + TIME_FADE_OUT_SUN_VALUE) {
      percentage = ((float) time - (END_TIME_P1 + TIME_FADE_OUT_SUN_OFFSET)) / TIME_FADE_OUT_SUN_VALUE;
      analogWrite(PIN_SUN, 255 - (percentage * 255));
    } else {
      analogWrite(PIN_SUN, 0);
    }
    // always set stars off
    analogWrite(PIN_STARS, 0);
  } else if (time >= END_TIME_P2 && time < END_TIME_P3) {
    // calculate stars fade in percentage
    if (time < END_TIME_P2 + TIME_FADE_IN_STARS_OFFSET) {
      analogWrite(PIN_STARS, 255);
    } else if (time < END_TIME_P2 + TIME_FADE_IN_STARS_OFFSET + TIME_FADE_IN_STARS_VALUE) {
      percentage = ((float) time - (END_TIME_P2 + TIME_FADE_IN_STARS_OFFSET)) / TIME_FADE_IN_STARS_VALUE;
      analogWrite(PIN_STARS, percentage * 255);
    } else {
      pulseTime = (time - (END_TIME_P2 + TIME_FADE_IN_STARS_OFFSET + TIME_FADE_IN_STARS_VALUE)) % TOTAL_PULSE;
      if (pulseTime >= 0 && pulseTime < TIME_PULSE_OFFSET) {
        analogWrite(PIN_STARS, 255);
      } else if (pulseTime >= TIME_PULSE_OFFSET && pulseTime < TIME_PULSE_DOWN) {
        percentage = ((float) (pulseTime - TIME_PULSE_OFFSET)) / (TIME_PULSE_DOWN - TIME_PULSE_OFFSET);
        analogWrite(PIN_STARS, 255 - (percentage * (255 - PULSE_MIN_VALUE)));
      } else {
        percentage = ((float) (pulseTime - TIME_PULSE_DOWN)) / (TOTAL_PULSE - TIME_PULSE_DOWN);
        analogWrite(PIN_STARS, PULSE_MIN_VALUE + (percentage * (255 - PULSE_MIN_VALUE)));
      }
    }
    // always set houses on and sun off
    analogWrite(PIN_SUN, 0);
    analogWrite(PIN_HOUSES, 255);
  } else if (time >= END_TIME_P3 && time < END_TIME_P4) {
    // calculate houses fade out percentage
    if (time < END_TIME_P3 + TIME_FADE_OUT_HOUSES_OFFSET) {
      analogWrite(PIN_HOUSES, 255);
    } else if (time < END_TIME_P3 + TIME_FADE_OUT_HOUSES_OFFSET + TIME_FADE_OUT_HOUSES_VALUE) {
      percentage = ((float) time - (END_TIME_P3 + TIME_FADE_OUT_HOUSES_OFFSET)) / TIME_FADE_OUT_HOUSES_VALUE;
      analogWrite(PIN_HOUSES, 255 - (percentage * 255));
    } else {
      analogWrite(PIN_HOUSES, 0);
    }
    // calculate stars percentage bearing in mind that there may be a pulse already in progress from the previous phase
    // NB: do not pulse if we are very close to the end of the phase
    pulseTime = (time - (END_TIME_P2 + TIME_FADE_IN_STARS_OFFSET + TIME_FADE_IN_STARS_VALUE)) % TOTAL_PULSE;
    if ((pulseTime >= 0 && pulseTime < TIME_PULSE_OFFSET) || (END_TIME_P4 - time < TOTAL_PULSE)) {
      analogWrite(PIN_STARS, 255);
    } else if (pulseTime >= TIME_PULSE_OFFSET && pulseTime < TIME_PULSE_DOWN) {
      percentage = ((float) (pulseTime - TIME_PULSE_OFFSET)) / (TIME_PULSE_DOWN - TIME_PULSE_OFFSET);
      analogWrite(PIN_STARS, 255 - (percentage * (255 - PULSE_MIN_VALUE)));
    } else {
      percentage = ((float) (pulseTime - TIME_PULSE_DOWN)) / (TOTAL_PULSE - TIME_PULSE_DOWN);
      analogWrite(PIN_STARS, PULSE_MIN_VALUE + (percentage * (255 - PULSE_MIN_VALUE)));
    }
    // always set sun off
    analogWrite(PIN_SUN, 0);
  }
}
