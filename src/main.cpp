#include <Arduino.h>

void setup() {
   pinMode(13, OUTPUT);   
}

void loop() {
   digitalWrite(13, HIGH);   // set the LED on
   delay(2000);              // wait for a second
   digitalWrite(13, LOW);    // set the LED off
   delay(1000);              // wait for a second
}