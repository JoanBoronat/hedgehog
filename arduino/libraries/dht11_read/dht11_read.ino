#include <DHT11.h>
#include <Photoresistor.h>

int pin=4;
int pinPhotoresistor = A1;

Photoresistor photo(pinPhotoresistor);
DHT11 dht11(pin);

void setup()
{
   Serial.begin(9600);
  while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
}

void loop()
{
  int err;
  float temp, humi;

  photo.readLight();
  if((err=dht11.read(humi, temp))==0)
  {
    Serial.print("temperature ");
    Serial.println(temp);
    Serial.print("humidity ");
    Serial.println(humi);
    Serial.print("luminosity ");
    Serial.println(photo.lux);
  }
  else
  {
   /* Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();  */  
  }
  delay(DHT11_DELAY); //delay for reread
}



