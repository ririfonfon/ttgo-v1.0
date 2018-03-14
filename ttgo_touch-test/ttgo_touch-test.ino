int threshold = 40;
bool touch1detected = false;
bool touch2detected = false;

void gotTouch() {
  touch1detected = true;
}

void gotTouch1() {
  touch2detected = true;
}

void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  printf("\n ESP32 Touch Interrupt Test\n");
  touchAttachInterrupt(49, gotTouch, threshold);
  touchAttachInterrupt(50, gotTouch1, threshold);
}

void loop() {
  if (touch1detected) {
    touch1detected = false;
    Serial.println("Touch 1 detected");
  }
  if (touch2detected) {
    touch2detected = false;
    Serial.println("Touch 2 detected");
  }
  Serial.println(touchRead(35));
  Serial.println(touchRead(34));
  Serial.println(touchRead(39));

  Serial.println("");
  delay(1000);
}
