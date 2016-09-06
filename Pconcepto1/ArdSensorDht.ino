#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <DHT.h>

// El sensor DHT es conectado al pin 2 del Arduino
#define DHTPIN 2

// Se utiliza el modelo de sensor DHT11
#define DHTTYPE DHT11   // DHT 11 

DHT dht(DHTPIN, DHTTYPE);


// Radio con CE & CSN conectado al pin 9 & 10
RF24 radio(9, 10);
RF24Network network(radio);

// Constantes que identifican el sensor y el controlador
const uint16_t this_node = 1;
const uint16_t parent_node = 0;

// Tiempo entre paquetes  (en ms)
const unsigned long interval = 1000;  // cada 1sec

// estructura del mensaje
struct message_1 {
  float temperature;
  float humidity;
  unsigned char light;
  bool motion;
  bool dooropen;

};
message_1 message;

// se inicializa la cabecera para este nodo
RF24NetworkHeader header(parent_node);

void setup(void)
{
  Serial.begin(9600);

  SPI.begin();
  radio.begin();
  delay(5);
  network.begin(90, this_node);

  // Se inicializa la librería DHT
  dht.begin();
  // La cabecera siempre será 1 
  header.type = '1';
  
}

void loop() {

  // actualiza datos
  network.update();
  float t = dht.readTemperature();
  // Lectura de humedad  (porcentaje)
  float h = dht.readHumidity();
  // Lectura de temperatura en Grados Celsius
    
  
  

  // Solo se envían los valores si alguno de ellos tiene alguna variación:
  //  0.5 grados de temperatura, 1% humedad 
  if (abs(t - message.temperature) > 0.5 || 
      abs(h - message.humidity) > 1.0 ) {

    // Construcción del mensaje que se enviara.
    message = (message_1){ t, h,0,0,0};

    if (network.write(header, &message, sizeof(message))) {
      Serial.print("Mensaje enviado\n"); 
    } else {
      Serial.print("No se puedo enviar el mensaje\n"); 
    }
  }

  // Se espera un poco antes de comenzar otra vez
  delay(interval);
}
