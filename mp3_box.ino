/*
 * Typical pin layout used:
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
 *
 * The reader can be found on eBay for around 5 dollars. Search for "mf-rc522" on ebay.com. 
 */

#include <SPI.h>
#include <MFRC522.h>

/* Set your new UID here! */
#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);        // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

void setup() {
        Serial.begin(9600);        // Initialize serial communications with the PC
        while (!Serial);           // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
        SPI.begin();               // Init SPI bus
        mfrc522.PCD_Init();        // Init MFRC522 card
        Serial.println(F("Wait card: "));
        
        // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;
        }
}

void loop() {
  
        // Look for new cards, and select one if present
        if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
            delay(50);
            return;
        }
        
        // Now a card is selected. The UID and SAK is in mfrc522.uid.
        
        // Dump UID
        Serial.print(F("Card UID:"));
        for (byte i = 0; i < mfrc522.uid.size; i++) {
                Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                Serial.print(mfrc522.uid.uidByte[i], HEX);
        } 
        Serial.println();
       
        delay(2000);
}
