void setup() {
  pinMode(13, OUTPUT);
}
void loop() {
  digitalWrite(13, HIGH);   // Enciende el LED 
  delay(1000);              // Espera un segundo
  digitalWrite(13, LOW);    // Apaga el led volviendo el voltaje a cero
  delay(1000);              // Espera un segundo
}
