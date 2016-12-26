#include <Wtv020sd16p.h>

/*
 * Подключение пинов Arduino к RC522:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>
#include <Wtv020sd16p.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);        // Назначение пинов считывателя.

const int card_delay = 500;
const int wait_card = 250;
unsigned long uidDec, uidDecTemp;

const unsigned int PLAY_PAUSE = 0xFFFE;
const unsigned int STOP = 0xFFFF;
const unsigned int VOLUME_MIN = 0xFFF0;
const unsigned int VOLUME_MAX = 0xFFF7;

int resetPin = 3;
int clockPin = 4;
int dataPin = 5;
int busyPin = 6;
int x = 0;

Wtv020sd16p wtv020sd16p(resetPin, clockPin, dataPin, busyPin);


void setup() {
  
        wtv020sd16p.reset();
        
        Serial.begin(9600);        // Инициализация последнего обмена данными с ПК
        while (!Serial);           // Ожидание открытия порта
        SPI.begin();               // Инициализация  шины
        mfrc522.PCD_Init();        // Инициализация считывателя
        Serial.println(F("Wait card: "));      
}

void loop() {
        delay(wait_card);
       // wtv020sd16p.sendCommand(0xFFF6);
        // Просмотр карты, если приложена запомнить
        if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
            delay(50);
            return;
        }
        
        uidDec = 0;
                
        for (byte i = 0; i < mfrc522.uid.size; i++)
         {
         uidDecTemp = mfrc522.uid.uidByte[i];
         uidDec = uidDec * 256 + uidDecTemp;
         }
         Serial.println("Card UID: ");
         Serial.println(uidDec); // Выводим UID метки в консоль.
  
         if (uidDec == 429208694) // Сравниваем Uid метки, если он равен заданому - включаем музыку.
         {
         Serial.println("Super!");
         delay(wait_card);
         }
          else if (uidDec == 1100222070) // Сравниваем Uid метки, если он равен заданому - включаем музыку.
         {
         Serial.println("Neploho!");
         }
         else if (uidDec == 3239272822) // Сравниваем Uid метки, если он равен заданому - включаем музыку.
         {
         Serial.println("Otlichno!");
         }
       
 delay(card_delay);
 
}
