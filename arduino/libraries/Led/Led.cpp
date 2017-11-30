#include "Led.h"

Led::Led(uint8_t _pin)
{
    pin = _pin;
    pinMode(pin, OUTPUT);
}

void Led::increaseIntensity(void)
{
    ledIntensity = ledIntensity + variation > maxIntensity ? maxIntensity : ledIntensity + variation;
    analogWrite(pin, ledIntensity);
}

void Led::decreaseIntensity(void)
{
    ledIntensity = ledIntensity - variation < 0 ? 0 : ledIntensity - variation;
    analogWrite(pin, ledIntensity);
}

void Led::on(void)
{
    digitalWrite(pin, HIGH);
}

void Led::off(void)
{
    digitalWrite(pin, LOW);
}