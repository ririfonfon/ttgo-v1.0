// Arduino RBD Button Library Example v2.1.1 - Debounce a button with events. INPUT_PULLUP enabled.
// https://github.com/alextaujenis/RBD_Button
// Copyright 2016 Alex Taujenis
// MIT License

#include <RBD_Timer.h>  // https://github.com/alextaujenis/RBD_Timer
#include <RBD_Button.h> // https://github.com/alextaujenis/RBD_Button

// input pullup enabled by default
RBD::Button button1(35);
RBD::Button button2(34);
RBD::Button button3(39);

void setup() {
  Serial.begin(115200);
}

void loop() {
  if(button1.onPressed()) {
    Serial.println("Button1 Pressed");
  }

  if(button1.onReleased()) {
    Serial.println("Button1 Released");
  }
   if(button2.onPressed()) {
    Serial.println("Button2 Pressed");
  }

  if(button2.onReleased()) {
    Serial.println("Button2 Released");
  }
   if(button3.onPressed()) {
    Serial.println("Button3 Pressed");
  }

  if(button3.onReleased()) {
    Serial.println("Button3 Released");
  }
}
