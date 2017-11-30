#include <DHT11.h>
#include <Photoresistor.h>
#include <Timer.h>
#include <Thermistor.h>
#include <Led.h>

struct Sensor
{
  const int pin;
  int minValue;
  int maxValue;
};

Led verd(11);
Led groc(10);
Led vermell(9);

Sensor humidity = {4, 10, 100};
Sensor temperature = {A1, 10, 100};
Sensor luminosity = {A2, 10, 100};

Photoresistor photo(luminosity.pin);
Thermistor therm(temperature.pin);
DHT11 dht11(humidity.pin);
Timer t;

boolean running = false;

void setup()
{
  Serial.begin(9600);

  int tickEvent = t.every(1000, sensors_handler, (void*) 1);
  int tickEvent2 = t.every(10, reader, (void*) 2);

  attachInterrupt(0, startStop, RISING);

  verd.on();
  groc.on();
  vermell.on();
}

void loop()
{
  if (running) {
    t.update();
  }
}

void startStop() {
  running = true;
}

void sensors_handler(void* context) {
  float temp, humi;

  therm.readTemp();
  photo.readLight();

  if (dht11.read(humi, temp) == 0)
  {
    temp = (temp + therm.degrees) / 2.0;

    if (temp < temperature.minValue || temp > temperature.maxValue) {
      Serial.print("error Temperature ");
      Serial.println(temp);
    } else {
      Serial.print("temperature ");
      Serial.println(temp);
    }

    if (humi < humidity.minValue || humi > humidity.maxValue) {
      Serial.print("error Humidity ");
      Serial.println(humi);
    } else {
      Serial.print("humidity ");
      Serial.println(humi);
    }

    if (photo.lux < luminosity.minValue || photo.lux > luminosity.maxValue) {
      Serial.print("error Luminosity ");
      Serial.println(photo.lux);
    } else {
      Serial.print("luminosity ");
      Serial.println(photo.lux);
    }

  }
  /*else
    {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();
    }*/
  delay(DHT11_DELAY); //delay for reread
}

void reader(void* context) {

  String sensor;
  int minValue, maxValue;

  if (Serial.available() > 0)
  {
    sensor = Serial.readStringUntil(',');
    Serial.read();
    minValue = Serial.parseInt();
    Serial.read();
    maxValue = Serial.parseInt();
    Serial.read();

    if (sensor == "temperature") {
      Serial.print("temperature: ");
      Serial.print(minValue);
      Serial.print(" ");
      Serial.println(maxValue);
    }

    else if (sensor == "humidity") {
      Serial.print("humidity: ");
      Serial.print(minValue);
      Serial.print(" ");
      Serial.println(maxValue);
    }

    else if (sensor == "luminosity") {
      Serial.print("luminosity: ");
      Serial.print(minValue);
      Serial.print(" ");
      Serial.println(maxValue);
    }

  }
}
