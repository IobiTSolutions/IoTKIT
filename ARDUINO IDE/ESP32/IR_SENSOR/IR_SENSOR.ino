int IRSensor = 4; // connect ir sensor to arduino pin 2
int LED = 2; // conect Led to arduino pin 13



void setup() 
{

  pinMode (IRSensor, INPUT); // sensor pin INPUT
  pinMode (LED, OUTPUT); // Led pin OUTPUT
   Serial.begin(9600);
}

void loop()
{
  int statusSensor = digitalRead (IRSensor);
  
  if (statusSensor == 1){
    digitalWrite(LED, LOW); // LED LOW
    Serial.println("Obstable Not Detected, LED OFF");
  }
   else
  {
    digitalWrite(LED, HIGH); // LED High
    Serial.println("Obstable Detected, LED ON");
  }
  
}
