
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

byte ledPin = 8;

RF24 radio(9, 10);
RF24Network network(radio);

const uint16_t this_node = 2;

const unsigned long interval = 1000;  // every sec

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

  pinMode(ledPin, OUTPUT);
}

void loop() {

  network.update();

  while (network.available()) {
    RF24NetworkHeader header;
    message_action message;
    network.peek(header);
    if (header.type == '2') {
      network.read(header, &message, sizeof(message));
      Serial.print("Data received from node ");
      Serial.println(header.from_node);
      Serial.print("Value: ");
      Serial.println(message.state);
      if (message.state) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
    } else {
      network.read(header, &message, sizeof(message));
      Serial.print("Unknown message received from node ");
      Serial.println(header.from_node);
    }
  }

  // Wait a bit before we start over again
  delay(interval);
}

