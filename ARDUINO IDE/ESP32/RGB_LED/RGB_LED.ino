#define LED1RED 5
#define LED1BLUE 18
#define LED1GREEN 19

#define LED2RED 25
#define LED2BLUE 26
#define LED2GREEN 27

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1RED, OUTPUT);
  pinMode(LED1BLUE, OUTPUT); 
  pinMode(LED1GREEN, OUTPUT);
  
  pinMode(LED2RED, OUTPUT);
  pinMode(LED2BLUE, OUTPUT); 
  pinMode(LED2GREEN, OUTPUT);
  
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED1RED, HIGH);   
  digitalWrite(LED2RED, HIGH);   
  Serial.println("LED1RED & LED2RED ON");
  delay(1000);                       
  digitalWrite(LED1RED, LOW);   
  digitalWrite(LED2RED, LOW);   
  Serial.println("LED1RED & LED2RED OFF");
  delay(1000);    

  digitalWrite(LED1BLUE, HIGH);   
  digitalWrite(LED2BLUE, HIGH);   
  Serial.println("LED1BLUE & LED2BLUE ON");
  delay(1000);                       
  digitalWrite(LED1BLUE, LOW);   
  digitalWrite(LED2BLUE, LOW);   
  Serial.println("LED1BLUE & LED2BLUE OFF");
  delay(1000);  

  digitalWrite(LED1GREEN, HIGH);   
  digitalWrite(LED2GREEN, HIGH);   
  Serial.println("LED1GREEN & LED2GREEN ON");
  delay(1000);                       
  digitalWrite(LED1GREEN, LOW);   
  digitalWrite(LED2GREEN, LOW);   
  Serial.println("LED1GREEN & LED2GREEN OFF");
  delay(1000);  
  
}
