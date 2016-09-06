
#include <Servo.h>
Servo myservo;  
int pos = 0;    
void setup() {
  myservo.attach(7);  
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { 
    myservo.write(pos);              //Se le dice al servo que vaya a la posición pos
    delay(15);                       // Espera 15ms para que el servo vuelva a su posición 
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
}
