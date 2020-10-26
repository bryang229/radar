#include "LedControl.h"
#include "SR04.h"
#define TRIG_PIN1 9
#define ECHO_PIN1 8
#define TRIG_PIN2 7
#define ECHO_PIN2 6
#define TRIG_PIN3 5
#define ECHO_PIN3 4
#define TRIG_PIN4 3
#define ECHO_PIN4 2

SR04 sr04a = SR04(ECHO_PIN1, TRIG_PIN1);
SR04 sr04b = SR04(ECHO_PIN2, TRIG_PIN2);
SR04 sr04c = SR04(ECHO_PIN3, TRIG_PIN3);
SR04 sr04d = SR04(ECHO_PIN4, TRIG_PIN4);

LedControl lc = LedControl(12, 10, 11, 1);

byte rows[5] = {
  B00000000,
  B00011000,
  B00011011,
  B11011000,
  B11011011
};

void setup() {
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(9, HIGH);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  Serial.begin(9600);
  lc.setRow(0, 3, rows[1]);
  lc.setRow(0, 4, rows[1]);

}

void logic() {
  int a = sr04a.Distance();
  int b = sr04b.Distance();
  int c = sr04c.Distance();
  int d = sr04d.Distance();
  //a is left
  //b is top
  //c is right
  //d is bottom

  if (a < 100) {
    if (c < 100) {
      lc.setRow(0, 3, rows[4]);
      lc.setRow(0, 4, rows[4]);
    }
    else {
      lc.setRow(0, 3, rows[3]);
      lc.setRow(0, 4, rows[3]);
    }
  }
  else if (c < 100) {
    lc.setRow(0, 3, rows[2]);
    lc.setRow(0, 4, rows[2]);
  }
  else {
    lc.setRow(0, 3, rows[1]);
    lc.setRow(0, 4, rows[1]);
  }

  if (b < 100) {
    lc.setRow(0, 0, rows[1]);
    lc.setRow(0, 1, rows[1]);
  }
  else {
    lc.setRow(0, 0, rows[0]);
    lc.setRow(0, 1, rows[0]);
  }
  if (d < 100) {
    lc.setRow(0, 6, rows[1]);
    lc.setRow(0, 7, rows[1]);
  }
  else {
    lc.setRow(0, 6, rows[0]);
    lc.setRow(0, 7, rows[0]);
  }

}

void loop() {
  logic();
}
