#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <Servo.h> 


byte switchPin = 12;
RF24 radio(9, 10); 
RF24Network network(radio);


const uint16_t this_node = 1;
const uint16_t parent_node = 0;


const unsigned long interval = 1000;  // every sec


struct message_1 {

  bool pulsador;
};
message_1 message;

RF24NetworkHeader header(parent_node);

void setup(void)
{
  // Set up the Serial Monitor
  Serial.begin(9600);

  // Initialize all radio related modules
  SPI.begin();
  radio.begin();
  delay(5);
  network.begin(90, this_node);
  
  // Activate the internal Pull-Up resistor for the door sensor
  pinMode(switchPin, INPUT_PULLUP);

  delay(50);
}

void loop() {

  network.update();

 
  bool d = (digitalRead(switchPin) == HIGH);
  
  header.type = '1';

  if ( d != message.pulsador) {
        message = (message_1){ d };

    if (network.write(header, &message, sizeof(message))) {
      Serial.print("Message sent\n"); 
    } else {
      Serial.print("Could not send message\n"); 
    }
  }

  delay(interval);
}
