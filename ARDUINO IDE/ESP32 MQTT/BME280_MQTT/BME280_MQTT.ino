#include <QubitroMqttClient.h>
#include <WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
// WiFi Client
WiFiClient wifiClient;

// Qubitro Client
QubitroMqttClient mqttClient(wifiClient);

// Device Parameters
char deviceID[] = "5060befb-5aec-4777-b247-4c11ce884a54";
char deviceToken[] = "IeqcXR0zhmhHpbmf-mt8t1w$9FAg3-gutaMd-0$J";

// WiFi Parameters
const char* ssid = "KARTHIK JIO";
const char* password = "0758Karthik!";
void setup() {
  // Initialize the serial port
  serial_init();
  
  // Initialize wireless connectivity
  wifi_init();

  // Initialize Qubitro
  qubitro_init();
   while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
    int temp=bmp.readTemperature();
    float pressure= bmp.readPressure();
    float altitude=bmp.readAltitude(1017);
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1017)); /* Adjusted to local forecast! */
    Serial.println(" m");                    //If you don't know it, modify it until you get your current altitude
    Serial.println();
  // Generate random values
  //int sensor_value_1 = analogRead(potpin);
  //int sensor_value_2 = random(0, 100);

  // Print the random values
  //Serial.print("Sensor value 1: ");
  //Serial.println(sensor_value_1);
  //Serial.print("Sensor value 2: ");
  //Serial.println(sensor_value_2);

  // Send telemetry
  String payload = "{\"Sensor 1\":" + String(temp)
    + ",\"Sensor 2\":" + String(pressure) + "}";
  mqttClient.poll();
  mqttClient.beginMessage(deviceID);
  mqttClient.print(payload);
  mqttClient.endMessage();

  // Delay
  delay(2000);
}

// Initialization code

void serial_init() {
  // Initiate serial port connection
  Serial.begin(115200);

  // Delay for stabilization
  delay(200);
}

void wifi_init() {
  // Set WiFi mode
  WiFi.mode(WIFI_STA);

  // Disconnect WiFi
  WiFi.disconnect();
  delay(100);

  // Initiate WiFi connection
  WiFi.begin(ssid, password);

  // Print connectivity status to the terminal
  Serial.print("Connecting to WiFi...");
  while(true)
  {
    delay(1000);
    Serial.print(".");
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("");
      Serial.println("WiFi Connected.");
      Serial.print("Local IP: ");
      Serial.println(WiFi.localIP());
      Serial.print("RSSI: ");
      Serial.println(WiFi.RSSI());
      break;
    }
  }
}

void qubitro_init() {
  char host[] = "broker.qubitro.com";
  int port = 1883;
  mqttClient.setId(deviceID);
  mqttClient.setDeviceIdToken(deviceID, deviceToken);
  Serial.println("Connecting to Qubitro...");
  if (!mqttClient.connect(host, port))
  {
    Serial.print("Connection failed. Error code: ");
    Serial.println(mqttClient.connectError());
    Serial.println("Visit docs.qubitro.com or create a new issue on github.com/qubitro");
  }
  Serial.println("Connected to Qubitro.");
  mqttClient.subscribe(deviceID);
}
