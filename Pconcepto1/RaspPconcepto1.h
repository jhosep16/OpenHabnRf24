
#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>
#include <mosquittopp.h>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constantes que identifican a los nodos
const uint16_t pi_node = 0;
const uint16_t sensor_node1 = 1;
const uint16_t action_node1 = 2;
¿

const char* action_channel1 = "home/bedroom/light";
const char* action_channel2 = "home/kitchen/light";

// CE Pin, CSN Pin, SPI Speed

RF24radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_18, BCM2835_SPI_SPEED_1MHZ);
RF24Network network(radio);

const unsigned long interval = 1000;

struct message_action {
	bool state;
};

struct message_sensor {
	float temperature;
	float humidity;
	unsigned char light;
	bool motion;
	bool dooropen;
};

// Clase mosquitto
 class MyMosquitto : public mosquittopp::mosquittopp {
	public:
		MyMosquitto() : mosquittopp::mosquittopp ("PiBrain") { MyMosquitto::lib_init(); }
		
		virtual void on_connect (int rc) { printf("Connected to Mosquitto\n"); }
		
		virtual void on_disconnect () { printf("Disconnected\n"); }
		
		virtual void on_message(const struct mosquitto_message* mosqmessage) {
			// Mensaje recibido desde el canal subscrito
			printf("Message found on channel %s: %s\n", mosqmessage->topic, mosqmessage->payload);
			
			// Se crea el mensaje que se enviara por RF24
			message_action actionmessage;
			if (strcmp((char*)mosqmessage->payload, "0") == 0) {
				actionmessage = (message_action){ false };
			} else if (strcmp((char*)mosqmessage->payload, "1") == 0) {
				actionmessage = (message_action){ true };
			} else {
				printf("Unknown message: %s\n", mosqmessage->payload); 
				return;
			}
			// Determina el nodo base en el canal 
			uint16_t target_node;
			if (strcmp(mosqmessage->topic, action_channel1) == 0) {
				target_node = action_node1;
			} else if (strcmp(mosqmessage->topic, action_channel2) == 0) {
				target_node = action_node2;
			}
			
			printf("Enviando la instrucción al nodo %i\n", target_node);
			
			// Enviando el mensaje a RF24 
			RF24NetworkHeader header(target_node);
			header.type = '2';
			if (network.write(header, &actionmessage, sizeof(actionmessage))) {
				printf("Mensaje enviado\n"); 
			} else {
				printf("No se pudo enviar el mensaje\n"); 
			}
		}
 };
 
 MyMosquitto mosq;

int main(int argc, char** argv)
{
	// Se inicializan todos los radios relacionados al nodo
	radio.begin();
	delay(5);
	network.begin(90, pi_node);
	
	radio.printDetails();
	
	network.update();
	
	mosq.connect("127.0.0.1");
	mosq.subscribe(0, action_channel1);
	mosq.subscribe(0, action_channel2);
	
	while (true) {
		network.update();
		printf(".\n");
		// Entra a este loop si es que hay datos disponibles para leer,
		// Y continua asi todo el tiempo que haya mas datos para leer
		while ( network.available() ) {
			RF24NetworkHeader header;
			message_sensor sensormessage;
			// Toma un vistazo a los datos para ver la cabecera
			network.peek(header);
			// Solo se puede tomar un solo sensor
			if (header.type == '1') {
				// leer el mensaje
				network.read(header, &sensormessage, sizeof(sensormessage));
				
				printf("Data received from node %i\n", header.from_node);
				char buffer [50];
				switch (header.from_node) {
case sensor_node1:
						sprintf (buffer, "mosquitto_pub -t home/bedroom/temperature -m \"%f\"", sensormessage.temperature);
						system(buffer);
						sprintf (buffer, "mosquitto_pub -t home/bedroom/humidity -m \"%f\"", sensormessage.humidity);
						system(buffer);
						sprintf (buffer, "mosquitto_pub -t home/bedroom/light -m \"%i\"", sensormessage.light);
						system(buffer);
						sprintf (buffer, "mosquitto_pub -t home/bedroom/motion -m \"%i\"", sensormessage.motion ? 1 : 0);
						system(buffer);
						sprintf (buffer, "mosquitto_pub -t home/bedroom/door -m \"%i\"", sensormessage.dooropen ? 1 : 0);
						system(buffer);
						break;
					case sensor_node2:
						sprintf (buffer, "mosquitto_pub -t home/kitchen/temperature -m \"%f\"", sensormessage.temperature);
						system(buffer);
						
						break;
					default:
						printf("Unknown node %i\n", header.from_node);
						break;
				}
			} else {
				network.read(header, &sensormessage, sizeof(sensormessage));
				printf("Unknown message received from node %i\n", header.from_node);
			}
		}
		mosq.loop();
		delay(interval);
	}
	
	mosq.unsubscribe(0, action_channel1);
	mosq.unsubscribe(0, action_channel2);

	return 0;
}

