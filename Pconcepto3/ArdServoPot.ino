#include <Servo.h> // Carga la librería Servo.h que contiene métodos para trabajar con servos
Servo myservo;   
int potpin = 0; 
int val;        
void setup()
{
myservo.attach(7); // asocia el servo al pin 7
}

void loop()
{
val = analogRead(potpin);  // lee el valor del potenciómetro (valor
                           //entre 0 y 1023)
val = map(val, 0, 1023, 0, 179);  // escala el valor para usarlo con el
                           //servo (valor entre 0 y 180)
myservo.write(val);        // fija la posición del servo de acuerdo
                           //al valor escalado
delay(15);                
}
