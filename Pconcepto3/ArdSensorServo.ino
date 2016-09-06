
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <Servo.h> 
RF24 radio(9, 10);
RF24Network network(radio);
const uint16_t this_node = 1;
const uint16_t parent_node = 0;
const unsigned long interval = 1000;  
struct message_1 {
  float potenciometro;
 };
message_1 message;
Servo myservo;  
int potpin = 0; 
int val;        
RF24NetworkHeader header(parent_node);
void setup(void)
{
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  delay(5);
  network.begin(90, this_node);
}
void loop() {
  network.update();
  val = analogRead(potpin); 
  val = map(val, 0, 1023, 0, 179);  
 header.type = '1';

   
    message = (message_1){val };
Serial.print(val);                                 
    if (network.write(header, &message, sizeof(message))) {
      Serial.print("Message sent\n"); 
    } else {
      Serial.print("Could not send message\n"); 
    }
    delay(interval);
}
