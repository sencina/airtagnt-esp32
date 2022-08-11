/*
 * 	key_proc.cpp
 * 		key process
 */

#include <Arduino.h>

#include "key_proc.h"

static const int long_delay = 1000;
static const int short_delay = 100;
static int key;

void
init_key( int push_key )
{
    key = push_key;
    pinMode(key, INPUT_PULLUP);
}


void
test_key(void)
{
    if (digitalRead(key))
        delay(long_delay);
    else
        delay(short_delay);
}
