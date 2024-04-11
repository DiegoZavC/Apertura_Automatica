#include <Arduino.h>
#include <ESP32Servo.h>

Servo Myservo;
const int pinServo = 12;



void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(921600);
  Myservo.attach(pinServo);
  Serial.println();
  Serial.println("Prueba del servo motor");

}

void loop() {
  // put your main code here, to run repeatedly:}
        digitalWrite(LED_BUILTIN,1);//Led indica que esta abierta
        Myservo.write(135);//Gira antihorario, Se abre
        delay(750);
        Myservo.write(90);//Detiene su giro (dura 10 segundos)
        delay(4500);
        digitalWrite(LED_BUILTIN,0);//Led indica que se cierra
        Myservo.write(45);//Vuelve a su posición original, se cierra
        delay(500);
        //digitalWrite(LED_BUILTIN,1);//Se borrara al final
        //delay(1000);//Se borrará al final
        //digitalWrite(LED_BUILTIN,0);
        Myservo.write(90);//Se detiene
        delay(2000);
}
