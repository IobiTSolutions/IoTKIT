//Tech Trends Shameer
//Control LED Using Blynk 2.0/Blynk IOT

#define BLYNK_TEMPLATE_ID "TMPLHTicOEs8"
#define BLYNK_DEVICE_NAME "ESP32 RELAY"
#define BLYNK_AUTH_TOKEN "1UWN624hG5yUtgItNcfuvfLhgwRT_8lx"


#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
 

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "KARTHIK JIO";  // Enter your Wifi Username
char pass[] = "0758Karthik!";  // Enter your Wifi password

int ledpin = 2;
void setup()
{     
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);    
  pinMode(ledpin,OUTPUT);
}

void loop()
{
  Blynk.run(); 
}
