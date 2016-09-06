#include DHT.h
 El sensor está conectado al pin 2
#define DHTPIN 2
#define DHTTYPE DHT11    DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600); 
  Serial.println(DHT11 test!);
  Se inicia librería dht
  dht.begin();
}
void loop() {
   Se esperan 2 segundos entre mediciones
  delay(2000);
   Lectura de humedad (Porcentaje)
  float h = dht.readHumidity();
   Lectura de temperatura en Celsius
  float t = dht.readTemperature();
  Se revisa si alguna medición falla y se sale o intenta de nuevo
  if (isnan(h)  isnan(t) ) {
    Serial.println(Fallo! La lectura del sensor DGT -();
    return;
  }
  float hi = dht.computeHeatIndex(t, h);
  Serial.print(Humedad ); 
  Serial.print(h);
  Serial.print( %t);
  Serial.print(Temperatura ); 
  Serial.print(t);
  Serial.print( C )
}
