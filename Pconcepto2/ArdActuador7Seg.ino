#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
byte ledPin = 4;

// Radio with CE & CSN connected to pins 9&10
RF24 radio(9,10);
RF24Network network(radio);
const uint16_t this_node = 2;
const unsigned long interval = 1000;  
struct message_action {
   float light;
};
message_action message;
void setup(void)
{
  Serial.begin(9600);
   pinMode(2, OUTPUT);  
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  SPI.begin();
  radio.begin();
  delay(5);
  network.begin(90, this_node);
  pinMode(ledPin, OUTPUT);
}
void display (int a, int b, int c, int d, int e, int f, int g)// Función del display
{
  digitalWrite (2,a);   
  digitalWrite (3,b);   
  digitalWrite (4,c);
  digitalWrite (5,d);
  digitalWrite (6,e);
  digitalWrite (7,f);
  digitalWrite (8,g);
}
void loop() {
  // Update network data
  network.update();

  while (network.available()) {
    RF24NetworkHeader header;
    message_action message;
    network.peek(header);
    if (header.type == '2') {
      network.read(header, &message, sizeof(message));
      Serial.print("Data received from node ");
      Serial.println(header.from_node);
      int resultado;
      Serial.print("Value: ");
      Serial.println(message.light);
      int valor= (int)message.light;
      int guardavalor;
      Serial.print("valor int: ");
      Serial.println(valor);
      
      int primernumero=valor/10;
      Serial.print("valor primernumero: ");
      Serial.println(primernumero);
      int segundonumero=int(valor-10*primernumero);
      Serial.print("valor segundonumero: ");
      Serial.println(segundonumero);
 
        delay(500);
          pintaDigito(primernumero);
          delay(500);
          pintaDigito(segundonumero);
            
          delay(500);
          display (1,1,1,1,1,1,1);
          delay(1000); //reiniciar el display 
  }
  }
  delay(interval);
}
void pintaDigito(int numero) {
if(numero==0){
  cero();
  }
  else if(numero==1){
  uno();
  }
  else if(numero==2){
  dos();
  }
  else if(numero==3){
  tres();
  }
  else if(numero==4){
  cuatro();
  }
  else if(numero==5){
  cinco();
  }
  else if(numero==6){
  seis();
  }
  else if(numero==7){
  siete();
  }
  else if(numero==8){
  ocho();
  }
  else if(numero==9){
  nueve();
  }

}
void cero() {
display (0,0,0,0,0,0,1); 

}
void uno() {

display (1,0,0,1,1,1,1);
}
void dos() {

display (0,0,1,0,0,1,0);
}
void tres() {
display (0,0,0,0,1,1,0);

}
void cuatro() {
display (1,0,0,1,1,0,0);

}
void cinco() {
display (0,1,0,0,1,0,0);

}
void seis() {
display (0,1,0,0,0,0,0);

}
void siete() {
display (0,0,0,1,1,1,1);

}
void ocho() {
display (0,0,0,0,0,0,0);

}
void nueve() {
display (0,0,0,1,1,0,0);

}

