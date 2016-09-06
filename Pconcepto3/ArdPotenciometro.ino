const int pinSensor = A0;  
int valorAnalogico  = 0;   // variable para guardar el valor leido del sensor
void setup() {
     pinMode(pinSensor, INPUT); 
      Serial.begin(9600);         
   }
   void loop(){
     // Lee el valor del sensor
      valorAnalogico = analogRead(pinSensor);
      Serial.print("Valor del sensor analogico = "); 
      Serial.println(valorAnalogico);
      // Espera 1000 milisegundos para leer y enviar la siguiente lectura del sensor
      delay(1000);     
   }

