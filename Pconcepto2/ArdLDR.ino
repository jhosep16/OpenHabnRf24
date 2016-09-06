
int sensorPin = A0;         //pin analógico elegido
unsigned int sensorValue = 0;  // variable para guardar el valor del ldr
void setup()
{
  pinMode(7, OUTPUT);
  Serial.begin(9600);        
}
void loop()
{
  sensorValue = analogRead(sensorPin);     
  if(sensorValue<200) digitalWrite(7, HIGH);   
  else digitalWrite(7, LOW);   
    Serial.print(sensorValue, DEC);     // Imprime le valor(0 a 1024)
  Serial.println("");                   
  delay(500);  
}
