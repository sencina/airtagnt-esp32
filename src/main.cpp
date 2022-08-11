#include <Arduino.h>

#include "key_proc.h"

//#define TBLINK 1000
const int tblink = 1000;

void setup() 
{
    pinMode(BLINK_LED, OUTPUT);
    init_key(PUSH);
    Serial.begin(BAUD_RATE);
}

void loop() 
{
    digitalWrite(BLINK_LED,HIGH);
    Serial.println("on");
    test_key();
//    delay(tblink);

    digitalWrite(BLINK_LED,LOW);
    Serial.println("off");
    test_key();
//    delay(tblink);
}
