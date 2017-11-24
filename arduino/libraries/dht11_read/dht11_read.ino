#include <DHT11.h>
#include <Photoresistor.h>
#include <Timer.h>

int pin = 4;
int pinPhotoresistor = A1;
char incomingByte;

char inData[20]; // Allocate some space for the string
char inChar= ""; // Where to store the character read
byte index = 0; // Index into array; where to store the character

Timer t;
Photoresistor photo(pinPhotoresistor);
DHT11 dht11(pin);

void setup()
{
  Serial.begin(9600);
  //int tickEvent = t.every(1000, dht11_handler, (void*) 1);
  int tickEvent2 = t.every(10, reader, (void*) 2);
}

void loop()
{
  t.update();
}


void dht11_handler(void* context) {
  float temp, humi;

  photo.readLight();
  if (dht11.read(humi, temp) == 0)
  {
    Serial.print("temperature ");
    Serial.println(temp);
    Serial.print("humidity ");
    Serial.println(humi);
    Serial.print("luminosity ");
    Serial.println(photo.lux);
  }
<<<<<<< HEAD
=======
  else
  {
   /* Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();  */  
  }
  delay(DHT11_DELAY); //delay for reread
>>>>>>> 1d8153a84b8c6dd0f72e5bb7099827b09efcc1db
}

void reader(void* context) {
  if (Serial.available() > 0) {

    inChar = Serial.read(); // Read a character
    Serial.print(inChar);
    if(inChar != "\n") // One less than the size of the array
    {
        
        inData[index] = inChar; // Store it
        index++; // Increment where to write next
    } 
    else 
    {
        for(int i=0; i<index; i++) {
          Serial.print(inData[index]);
        }
        index = 0;
    }
  }
}