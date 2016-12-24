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

#define SS_PIN 10
#define RST_PIN 9
#define LED 13

MFRC522 mfrc522(SS_PIN, RST_PIN);        // Назначение пинов считывателя.

const int CARD_DELAY = 500;
unsigned long uidDec, uidDecTemp;

void setup() {
        Serial.begin(9600);        // Инициализация последнего обмена данными с ПК
        while (!Serial);           // Ожидание открытия порта
        SPI.begin();               // Инициализация  шины
        mfrc522.PCD_Init();        // Инициализация считывателя
        Serial.println(F("Wait card: "));
        
        pinMode(LED, OUTPUT);

}

void loop() {
        // Просмотр карты, если приложена запомнить
        if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
            delay(50);
            return;
        }
        uidDec = 0;
        
        // Выбор карты: UID
        
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
  }
  else if (uidDec == 1100222070) // Сравниваем Uid метки, если он равен заданому - включаем музыку.
  {
    Serial.println("Neploho!");
  }
  else if (uidDec == 3239272822) // Сравниваем Uid метки, если он равен заданому - включаем музыку.
  {
    Serial.println("Otlichno!");
  }
       
    delay(CARD_DELAY);
}
