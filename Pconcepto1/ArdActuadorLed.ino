
 
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

//El led es conectado al pin4 del arduino
byte ledPin = 4;

// Radio con CE & CSN conectado al pin 9 y 10 
RF24 radio(9,10);
RF24Network network(radio);

// Constante que identificara este nodo
const uint16_t this_node = 2;

// Tiempo entre paquetes (en ms)
const unsigned long interval = 1000;  // cada segundo

// Estructura del mensaje
struct message_action {
  bool state;
};
message_action message;


void setup(void)
{
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  delay(5);
  network.begin(90, this_node);

  // Configuracion del pin LED
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Actualización de los datos
  network.update();

  while (network.available()) {
    RF24NetworkHeader header;
    message_action message;
    network.peek(header);
    if (header.type == '2') {
      network.read(header, &message, sizeof(message));
      Serial.print("Datos recibidos desde el nodo:  ");
      Serial.println(header.from_node);
      Serial.print("valor: ");
      Serial.println(message.state);
      if (message.state) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
    } else {
      network.read(header, &message, sizeof(message));
      Serial.print("Mensaje desconocido recibido desde el nodo:  ");
      Serial.println(header.from_node);
    }
  }
  delay(interval);
}
