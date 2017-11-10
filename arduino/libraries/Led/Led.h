
#include "Arduino.h"

#define PHOTO_LIB_VERSION 0.1

/* Class declaration */

class Led
{
    public:
        Led(uint8_t _pin);
        volatile float ledIntensity = 0;
        void increaseIntensity(void);
        void decreaseIntensity(void);
    protected:
        const static float maxIntensity = 255.0;
        const static float variation = 10.0;
        uint8_t pin;
    private:
};
