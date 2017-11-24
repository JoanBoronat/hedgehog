#include "DHT11.h"
#include <Arduino.h>


DHT11::DHT11(int pin_number) {
	pin=pin_number;
	last_read_time=0;
	pinMode(pin,INPUT);
	digitalWrite(pin, HIGH);

}
//wait for target status
//parameters
//  target : target status waiting for
//  time_out_us : time out in microsecond.
unsigned long DHT11::waitFor(uint8_t status, unsigned long time_out_micros) {
	unsigned long start=micros();
	unsigned long time_out=start+time_out_micros;
	while(digitalRead(pin)!=status)
	{
		if(time_out<micros()) return -1;
	}
	return micros()-start;
}

//wait for target status.
void DHT11::waitFor(uint8_t status) {
	while(digitalRead(pin)!=status);
}

//read one byte
byte DHT11::readByte() {
	int i=0;
	byte result=0;
	for(i=7;i>=0;i--)
	{
		waitFor(HIGH); //wait for 50us in LOW status
		delayMicroseconds(30); //wait for 30us
		if(digitalRead(pin)==HIGH) //if HIGH status lasts for 30us, the bit is 1;
		{
			result|=1<<(i);
			waitFor(LOW); //wait for rest time in HIGH status.
		}
	}
	return result;
}

//parameters
//	temperature : temperature to read.
//	humidity : humidity to read.
//return -1 : read too shortly. retry latter .
//		  0 : read successfully
//        1 : DHT11 not ready.
//		  2 : Checksum Error
int DHT11::read(float &humidity, float &temperature) {
	if((millis()-last_read_time<DHT11_DELAY)&&last_read_time!=0)	return -1;

	pinMode(pin,OUTPUT);
	digitalWrite(pin, LOW);
	delay(18); //at least 18ms to ensure DHT's detection on MCU's signal
	digitalWrite(pin, HIGH);
	pinMode(pin,INPUT);

	if(waitFor(LOW, 40)<0)	return 1; //waiting for DH11 ready
	if(waitFor(HIGH, 90)<0)	return 1; //waiting for first LOW signal(80us)
	if(waitFor(LOW, 90)<0)	return 1; //waiting for first HIGH signal(80us)

	byte hI=readByte();
	byte hF=readByte();
	byte tI=readByte();
	byte tF=readByte();
	byte cksum=readByte();
	if(hI+hF+tI+tF!=cksum)
		return 2;

	humidity=(float)hI+(((float)hF)/100.0F); //adding the decimal part to the integer one 
	temperature=(float)tI+(((float)tF)/100.0F);
	last_read_time=millis();
	return 0;
}