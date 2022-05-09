/********************************************************************
 *Project   : Tutorial Blynk ESP32 with BMP280 Pressure sensor module
*********************************************************************/

#define BLYNK_TEMPLATE_ID "TMPLA25TekhO"
#define BLYNK_DEVICE_NAME "ESP32 DHT11"
#define BLYNK_AUTH_TOKEN "4krhSgJaoLcJpJhq9lGNXJnd-y4U0ner"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>


Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

// You should get Auth Token in the Blynk App.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "KARTHIK JIO";
char pass[] = "0758Karthik!";

BlynkTimer timer;


void setup() 
{      
  Serial.begin(9600);
  Serial.println(F("BMP280 Sensor event test"));
  if (!bmp.begin(0X76)) 
  {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1) delay(10);
  }
  
  Blynk.begin(auth,ssid, pass);
  timer.setInterval(2500L, sendSensor);
}

void loop()
{
    Blynk.run();
    timer.run();
}

void sendSensor()
{
  //read sensor data
  sensors_event_t temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);

  //send data to blynk virtual pin
  Blynk.virtualWrite(V5,temp_event.temperature);
  Blynk.virtualWrite(V6,pressure_event.pressure);

  //Serial print data;
  Serial.print("TEMPERATURE : ");
  Serial.print(temp_event.temperature);
  Serial.print("     PRESSURE : ");
  Serial.println(pressure_event.pressure);

}
