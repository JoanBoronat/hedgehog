#include "Photoresistor.h"

Photoresistor::Photoresistor(uint8_t _pin)
{
    pin = _pin;
}

void Photoresistor::readLight(void)
{
    float _lux;
    float Vo;

    Vo = ((Vref/ADCres)*(analogRead(pin)));

    _lux = (((Vref*LuxRel)*Vo)-LuxRel)/Rl;

    /* Error control */

    if(_lux < 0) _lux = 0.0;

    lux = _lux;
}
