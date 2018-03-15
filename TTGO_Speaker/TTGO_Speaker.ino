#include "Speaker.h"
#include "startup_music.h"

void setup() {
  // put your setup code here, to run once:
  SPEAKER().begin();
  SPEAKER().setVolume(8);
  SPEAKER().beep();
  delay(1000);
  SPEAKER().playMusic(startup_music, 25000);
}

void loop() {
  SPEAKER().tone(5, 200);
  delay(1000);
  SPEAKER().tone(10, 200);
  delay(1000);
  SPEAKER().tone(20, 200);
  delay(1000);
  SPEAKER().tone(30, 200);
  delay(1000);
  SPEAKER().tone(40, 200);
  delay(1000);
  SPEAKER().update();
}
