#include "Thermistor.h"
#include "math.h"

Thermistor::Thermistor(uint8_t _pin)
{
    pin = _pin;
    pinMode(pin, INPUT);
}

void Thermistor::readTemp(void)
{
    float _degrees;
    float rtherm;

    rtherm = Rb * ((ADCres / analogRead(pin))-1);

    _degrees = (beta / logf(rtherm * G)) - K;

    /* Error control */

    if(_degrees < 0) _degrees = 0.0;

    degrees = _degrees;
}
