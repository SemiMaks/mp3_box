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

/* Установка UIDa */
#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}
#define SS_PIN 10
#define RST_PIN 9

const int LED = 13;
const int CARD_DELAY = 500;

MFRC522 mfrc522(SS_PIN, RST_PIN);        // Назначение пинов считывателя.
MFRC522::MIFARE_Key key;

void setup() {
        Serial.begin(9600);        // Инициализация последнего обмена данными с ПК
        while (!Serial);           // Ожидание открытия порта
        SPI.begin();               // Инициализация  шины
        mfrc522.PCD_Init();        // Инициализация считывателя
        Serial.println(F("Wait card: "));
        
        // Установка ключа в FFFFFFFFFFFFh заводского номера.
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;
        }
}

void loop() {
  
        // Просмотр карты, если приложена запомнить
        if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
            delay(50);
            return;
        }
        
        // Выбор карты: UID
        
        // Dump UID
        Serial.print(F("Card UID:"));
        for (byte i = 0; i < mfrc522.uid.size; i++) {
                Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                Serial.print(mfrc522.uid.uidByte[i], HEX);
        } 
        Serial.println();
       
        delay(CARD_DELAY);
}
