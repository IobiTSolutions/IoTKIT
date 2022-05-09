#define RELAY1 25
#define RELAY2 27

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RELAY1, HIGH);     // turn the RELAY1 on (HIGH is the voltage level)
  digitalWrite(RELAY2, HIGH);     // turn the RELAY2 on (HIGH is the voltage level)
  Serial.println("RELAY1 & RELAY2 ON");
  delay(2000);                       // wait for a second
  digitalWrite(RELAY1, LOW);      // turn the RELAY1 off by making the voltage LOW
  digitalWrite(RELAY2, LOW);      // turn the RELAY2 off by making the voltage LOW
  Serial.println("RELAY1 & RELAY2 OFF");
  delay(2000);                       // wait for a second
}
