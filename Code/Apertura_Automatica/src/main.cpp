#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>
#include <ESP32Servo.h>

#define RST_Pin 21
#define SS_Pin 5
#define CK_Pin 18
#define MISO_Pin 19
#define MOSI_Pin 23
MFRC522 RFID(SS_Pin, RST_Pin);
Servo servoDoor;
const int servoPin = 12;
const int buzzerPin = 14;
const int greenLed = 25;
const int redLed = 26;
byte in_UID1[4] = {0xE3, 0x9E, 0x8F, 0xDC};
byte in_UID2[4] = {0xE3, 0x31, 0x2D, 0xFB};
byte in_UID3[4] = {0x93, 0xEF, 0xA1, 0xF5};

//bool ArrayEquality(byte*, byte*, int);
void BuzzerPIP();



void setup() {
  // put your setup code here, to run once:
  Serial.begin(921600);
  SPI.begin();
  RFID.PCD_Init();
  servoDoor.attach(servoPin);
  Serial.println();
  Serial.println("Sistema de apertura de puerta");
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(buzzerPin,OUTPUT);
  //servoDoor.write(0);

}

void loop() {
  /*
  // put your main code here, to run repeatedly:
  if (RFID.PICC_IsNewCardPresent()){
    if (RFID.PICC_ReadCardSerial()){
      if (ArrayEquality(RFID.uid.uidByte,in_UID,4)){
        digitalWrite(LED_BUILTIN,1);
        servoDoor.write(180);
        delay(10000);
        servoDoor.write(0);
        
      } else {
        digitalWrite(LED_BUILTIN,1);
        delay(500);
        digitalWrite(LED_BUILTIN,0);
        delay(500);
        //Buzzer
      }
      RFID.PICC_HaltA();
    }
  }
  */
   if (RFID.PICC_IsNewCardPresent()) { // new tag is available
    if (RFID.PICC_ReadCardSerial()) { // NUID has been readed
      //MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      digitalWrite(buzzerPin,0);
      if ((RFID.uid.uidByte[0] == in_UID1[0] &&
          RFID.uid.uidByte[1] == in_UID1[1] &&
          RFID.uid.uidByte[2] == in_UID1[2] &&
          RFID.uid.uidByte[3] == in_UID1[3]) ||
          (RFID.uid.uidByte[0] == in_UID2[0] &&
          RFID.uid.uidByte[1] == in_UID2[1] &&
          RFID.uid.uidByte[2] == in_UID2[2] &&
          RFID.uid.uidByte[3] == in_UID2[3])||
          (RFID.uid.uidByte[0] == in_UID3[0] &&
          RFID.uid.uidByte[1] == in_UID3[1] &&
          RFID.uid.uidByte[2] == in_UID3[2] &&
          RFID.uid.uidByte[3] == in_UID3[3])) {
        digitalWrite(LED_BUILTIN,1);//Led indica que esta abierta
        servoDoor.write(135);//Gira antihorario, Se abre
        delay(500);
        servoDoor.write(90);//Detiene su giro (dura 10 segundos)
        delay(4500);
        digitalWrite(LED_BUILTIN,0);//Led indica que se cierra
        servoDoor.write(45);//Vuelve a su posición original, se cierra
        delay(500);
        //digitalWrite(LED_BUILTIN,1);//Se borrara al final
        //delay(1000);//Se borrará al final
        //digitalWrite(LED_BUILTIN,0);
        servoDoor.write(90);//Se detiene
      } else {
        BuzzerPIP();
      }
      RFID.PICC_HaltA(); // halt PICC
      RFID.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }

}

//Funciones

/*
bool ArrayEquality(byte* arrayA[], byte* arrayB[], int length)
{
  for (int i = 0; i < length; i++){
    if (arrayA[i] != arrayB[i]){
      return false;
    }
  }
  return true;
}
*/

void BuzzerPIP()
{
  digitalWrite(buzzerPin,1);
  delay(500);
  digitalWrite(buzzerPin,0);
  delay(500);
  digitalWrite(buzzerPin,1);
  delay(500);
  digitalWrite(buzzerPin,0);
  delay(500);
  digitalWrite(buzzerPin,1);
  delay(500);
  digitalWrite(buzzerPin,0);
}
