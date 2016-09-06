
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
RF24 radio(9, 10);
RF24Network network(radio);
const uint16_t this_node = 1;
const uint16_t parent_node = 0;
const unsigned long interval = 500;  // every sec
struct message_1 {
   float temperature;
  float humidity;
  float light;
};
message_1 message;
RF24NetworkHeader header(parent_node);
byte photocellPin = A0;            
unsigned int sensorValue = 0;  
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  delay(5);
  network.begin(90, this_node);
}

void loop()
{
  network.update();
  int p = analogRead(photocellPin);
  p = constrain(p, 50, 1000);
  p = map(p, 50, 1000, 0, 100);
 header.type = '1';

    message = (message_1){0,0, p };
        if (network.write(header, &message, sizeof(message))) {
      Serial.print("Message sent\n");
       Serial.print(message.light);     
  Serial.println("");     
    } else {
      Serial.print("Could not send message\n"); 
    }
  
  delay(interval);
}
