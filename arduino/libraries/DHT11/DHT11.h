#define DHT11_LIB_VERSION 0.1
#include <Arduino.h>
#define DHT11_DELAY 1000  // 1000ms lectures

class DHT11 
{
	int pin;
	unsigned long last_read_time;
protected:
	byte readByte();
	unsigned long waitFor(uint8_t target, unsigned long time_out_us);
	void waitFor(uint8_t target);
public:
	DHT11(int pin_number);
	int read( float& humidity, float& temperature);
};