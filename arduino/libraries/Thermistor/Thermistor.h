
#include "Arduino.h"

#define PHOTO_LIB_VERSION 0.1

/* Class declaration */

class Thermistor
{
    public:
        Thermistor(uint8_t _pin);
        float degrees;
        void readTemp(void);
    protected:
        uint8_t pin;
        const static float ADCres = 1023.0;
        const static float Rb = 10000.0;
        const static float beta = 3950.0;
        const static float K = 273.15;
        const static float G = 120.668;
    private:
};
