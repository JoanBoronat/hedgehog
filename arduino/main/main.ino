#include <DHT11.h>
#include <Photoresistor.h>
#include <Timer.h>
#include <Thermistor.h>
#include <Led.h>
#include <EEPROM.h> //Needed to access the eeprom read write functions

struct Sensor
{
  const int pin;
  int minValue;
  int maxValue;
};

// Initialization of the components
Led verd(11);
Led vermell(9);

Sensor humidity = {4, 10, 88};
Sensor temperature = {A1, 5, 45};
Sensor luminosity = {A2, 0, 1200};

Photoresistor photo(luminosity.pin);
Thermistor therm(temperature.pin);
DHT11 dht11(humidity.pin);
Timer t;

// Global variables to store the max and min temperature
unsigned int maxTemp, minTemp;

// Global variable with the status of the system (running or stopped)
boolean running = false;

void setup()
{
  Serial.begin(9600);

  // Initialization of the tasks
  int tickEvent = t.every(1000, sensors_handler, (void*) 1);
  int tickEvent2 = t.every(10, reader, (void*) 2);

  // Set up the button to turn on or off the system
  attachInterrupt(digitalPinToInterrupt(2), startStop, RISING);

  // Turn off the lights
  verd.off();
  vermell.off();

  // Retrieve the last values of the min and max temperature
  minTemp = EEPROMReadInt(0);
  maxTemp = EEPROMReadInt(2);
}

void loop()
{
  // Using the Timer library to schedule the tasks
  // If the status is running update the Timer and turn
  // the green led on otherwise don't update and turn off the led
  if (running) {
    verd.on();
    t.update();
  } else {
    verd.off();
  }
}

void startStop() {
  running = !running; // A single button to handle on/off
}

void sensors_handler(void* context) {
  float humi, temp;

  // Retrieve sensor values 
  therm.readTemp();
  photo.readLight();

  if (dht11.read(humi, temp) == 0)
  {
    // If the temperature is lower than the stored value update it
    if ((unsigned int) temp < minTemp) {
      EEPROMWriteInt(0, (unsigned int) temp);
    }

    // If the temperature is higher than the stored value update it
    if ((unsigned int) temp > maxTemp) {
      EEPROMWriteInt(2, (unsigned int) temp);
    }

    // Check if the temperature is in the correct range
    // send an error if it's outside of it
    // The same procedure is done for each sensor
    if (temp < temperature.minValue || temp > temperature.maxValue) {
      Serial.print("error temperature ");
      Serial.println(temp);
      vermell.on();
    } else {
      Serial.print("temperature ");
      Serial.println(temp);
      vermell.off();
    }

    if (humi < humidity.minValue || humi > humidity.maxValue) {
      Serial.print("error humidity ");
      Serial.println(humi);
      vermell.on();
    } else {
      Serial.print("humidity ");
      Serial.println(humi);
      vermell.off();
    }

    if (photo.lux < luminosity.minValue || photo.lux > luminosity.maxValue) {
      Serial.print("error luminosity ");
      Serial.println(photo.lux);
      vermell.on();
    } else {
      Serial.print("luminosity ");
      Serial.println(photo.lux);
      vermell.off();
    }

  }
  delay(DHT11_DELAY); //delay for reread
}

void reader(void* context) {

  String sensor;
  int minValue, maxValue;

  // Read if there is something in the buffer
  if (Serial.available() > 0)
  {
    // Break the message into pieces
    sensor = Serial.readStringUntil(',');
    minValue = Serial.parseInt();
    Serial.read();
    maxValue = Serial.parseInt();
    Serial.read();

    // Set the new values for the sensor
    if (sensor == "temperature") {
      temperature.minValue = minValue;
      temperature.maxValue = maxValue;
    }

    else if (sensor == "humidity") {
      humidity.minValue = minValue;
      humidity.maxValue = maxValue;
    }

    else if (sensor == "luminosity") {
      luminosity.minValue = minValue;
      luminosity.maxValue = maxValue;
    }
  }
}

// Write a two byte integer to the non-volatile memory
void EEPROMWriteInt(int adress, int value)
{
  byte primerByte = ((value >> 0) & 0xFF);
  byte segonByte = ((value >> 8) & 0xFF);

  EEPROM.write(adress, primerByte);
  EEPROM.write(adress + 1, segonByte);
}

// Read a two byte integer from the non-volatile memory
unsigned int EEPROMReadInt(int adress)
{
  byte primerByte = EEPROM.read(adress);
  byte segonByte = EEPROM.read(adress + 1);

  return ((primerByte << 0) & 0xFF) + ((segonByte << 8) & 0xFF00);
}
