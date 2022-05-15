#define BLYNK_TEMPLATE_ID "TMPLA25TekhO"
#define BLYNK_DEVICE_NAME "ESP32 DHT11"
#define BLYNK_AUTH_TOKEN "4krhSgJaoLcJpJhq9lGNXJnd-y4U0ner"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
 
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "KARTHIK JIO";  // type your wifi name
char pass[] = "0758Karthik!";  // type your wifi password

int sensor_pin = 36;

BlynkTimer timer;

void sendSensor(){
  uint16_t moisture_val= analogRead(sensor_pin);
  uint8_t moisture_per = map(moisture_val,4095,880,0,100);
  Serial.print("Moisture_val : ");
  Serial.print(moisture_val);
  Serial.print("  Moisture_per : ");
  Serial.print(moisture_per);
  Serial.println("%");
  
  Blynk.virtualWrite(V5, moisture_per);
}


void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2500L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V7)
{
  int pinvalue = param.asInt();
  digitalWrite(2,pinvalue);
}
