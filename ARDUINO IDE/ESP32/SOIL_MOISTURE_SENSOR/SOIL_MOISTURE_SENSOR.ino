int sensor_pin = 36;
int moisture_val ;
int moisture_per ;

void setup()
{
  Serial.begin(9600);
  delay(2000);
}

void loop()
{

  moisture_val= analogRead(sensor_pin);
  moisture_per = map(moisture_val,4095,0,0,100);
  Serial.print("Moisture_val : ");
  Serial.print(moisture_val);
  Serial.print("  Moisture_per : ");
  Serial.print(moisture_per);
  Serial.println("%");
  delay(1000);
}
