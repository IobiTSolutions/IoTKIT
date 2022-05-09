/*
  WriteMultipleFields
  
  Description: Writes values to fields 1,2,3,4 and status in a single ThingSpeak update every 20 seconds.
  
  Hardware: ESP32 based boards
  
  !!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!
  
  For licensing information, see the accompanying license file.
  
  Copyright 2020, The MathWorks, Inc.

  MODIFIED BY IOBIT SOLUTIONS PVT LTD // www.iobit.in
*/

#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include "DHT.h"

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;


unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
#define DHTPIN 4 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11
// Initializing the DHT11 sensor.
DHT dht(DHTPIN, DHTTYPE);

String myStatus = "";

void setup() {
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  dht.begin();
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
     delay(2500);
    // Reading temperature or humidity takes about 250 milliseconds!
     float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
     float t = dht.readTemperature();
     float f = dht.readTemperature(true);
     if (isnan(h) || isnan(t) || isnan(f)) {
     Serial.println(F("Failed to read from DHT sensor!"));
     return;
    }
     Serial.print("Temperature (ºC): ");
     Serial.print(t);
     Serial.println("ºC");
     Serial.print("Humidity");
     Serial.println(h);
     ThingSpeak.setField(1, h);
     ThingSpeak.setField(2, t);
   
    // set the status
    ThingSpeak.setStatus(myStatus);
  
    // write to the ThingSpeak channel
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(x == 200){
    Serial.println("Channel update successful.");
    }
    else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
   delay(20000); // Wait 20 seconds to update the channel again
}
