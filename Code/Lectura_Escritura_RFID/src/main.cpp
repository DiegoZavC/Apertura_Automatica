#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>
//#include <ESP32Servo.h>

#define RST_Pin 21
#define SS_Pin 5
//#define CK_Pin 18
//#define MISO_Pin 19
//#define MOSI_Pin 23
MFRC522 RFID(SS_Pin, RST_Pin);
#define New_UID {0xDE, 0xAD, 0xAD, 0xEF}
byte newUID[] = New_UID;
const int BUFFER_SIZE = 10;
char Buff[BUFFER_SIZE];


int data;


void setup() {

  Serial.begin(921600);
  SPI.begin();
  RFID.PCD_Init();
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.println("1: Leer y ver datos de tarjeta");
  Serial.println("2: Escribir datos en tarjetas");
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  /*
  if (Serial.available()){
    data = Serial.readBytes(Buff,BUFFER_SIZE);
  }
  switch (data)
  {
  case 1:
    Serial.println("Lectura de datos");
    if (RFID.PICC_IsNewCardPresent()){
      digitalWrite(LED_BUILTIN,1);
      if (RFID.PICC_ReadCardSerial()){
        Serial.print("Card UID: ");
        for (byte i = 0; i < RFID.uid.size; i++){
          Serial.print(RFID.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(RFID.uid.uidByte[i], HEX);
          delay(1000);
        }
        RFID.PICC_HaltA();
      }
    }
    break;

  case 2:
    Serial.println("Escritura de datos");
    if (RFID.MIFARE_SetUid(newUID, (byte)4, true)){
      Serial.println("Se escribió una nueva UID");
    }
    RFID.PICC_HaltA();
    break;
  
  default:
    Serial.println("Ingrese una opción");
    delay(1000);
    break;
  }
  */
   if (RFID.PICC_IsNewCardPresent()) { // new tag is available
    if (RFID.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = RFID.PICC_GetType(RFID.uid.sak);
      Serial.print("RFID/NFC Tag Type: ");
      Serial.println(RFID.PICC_GetTypeName(piccType));

      // print UID in Serial Monitor in the hex format
      Serial.print("UID:");
      for (int i = 0; i < RFID.uid.size; i++) {
        Serial.print(RFID.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(RFID.uid.uidByte[i], HEX);
      }
      Serial.println();

      RFID.PICC_HaltA(); // halt PICC
      RFID.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }
  

}

