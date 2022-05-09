// MQ2 GAS SENSOR is connected to GPIO 34 (Analog ADC1_CH6) 

int redLed = 5;
int greenLed = 18;
int buzzer = 19;
int MQ2SENSOR = 34;
// Your threshold value
int sensorThres = 400;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(MQ2SENSOR, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(MQ2SENSOR);

  Serial.print("MQ2SENSOR VALUE : ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(buzzer, HIGH);
    Serial.println("Threshold Value Reached, BUZZER ON");
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    digitalWrite(buzzer, LOW);
    Serial.println("Threshold Value Not Reached, BUZZER OFF");
  }
  delay(500);
}
