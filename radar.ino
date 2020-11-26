#include <SR04.h>
#include "LedControl.h"
#define TRIG_PIN1 7
#define ECHO_PIN1 8
#define TRIG_PIN2 3
#define ECHO_PIN2 2
#define TRIG_PIN3 51
#define ECHO_PIN3 53
#define TRIG_PIN4 50
#define ECHO_PIN4 48
#define rxd 69
#define txd 35
#define BUFFER_SIZE 64

const int alertDistance = 25;

const int  power [4] = {
  6,
  4,
  49,
  52
};

SR04 sr04a = SR04(ECHO_PIN1, TRIG_PIN1);
SR04 sr04b = SR04(ECHO_PIN2, TRIG_PIN2);
SR04 sr04c = SR04(ECHO_PIN3, TRIG_PIN3);
SR04 sr04d = SR04(ECHO_PIN4, TRIG_PIN4);

LedControl lc = LedControl(13, 11, 12, 1);
// (datain, clk, cs(load))

byte rows[5] = {
  B00000000,
  B00011000,
  B00011011,
  B11011000,
  B11011011
};

void setup() {
  pinMode(power[0],OUTPUT);
  pinMode(power[1],OUTPUT);
  pinMode(power[2],OUTPUT);
  pinMode(power[3],OUTPUT);
  digitalWrite(power[0],HIGH);
  digitalWrite(power[1],HIGH);
  digitalWrite(power[2],HIGH);
  digitalWrite(power[3],HIGH);
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

  if (a < alertDistance) {
    if (c < alertDistance) {
      lc.setRow(0, 3, rows[4]);
      lc.setRow(0, 4, rows[4]);
    }
    else {
      lc.setRow(0, 3, rows[3]);
      lc.setRow(0, 4, rows[3]);
    }
  }
  else if (c < alertDistance) {
    lc.setRow(0, 3, rows[2]);
    lc.setRow(0, 4, rows[2]);
  }
  else {
    lc.setRow(0, 3, rows[1]);
    lc.setRow(0, 4, rows[1]);
  }

  if (b < alertDistance) {
    lc.setRow(0, 0, rows[1]);
    lc.setRow(0, 1, rows[1]);
  }
  else {
    lc.setRow(0, 0, rows[0]);
    lc.setRow(0, 1, rows[0]);
  }
  if (d < alertDistance) {
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
