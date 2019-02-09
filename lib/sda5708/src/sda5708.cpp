#include "sda5708.h"
#include "font5x7.h"

// sketch: http://blog.smue.org/archives/433-DBOX1-SDA5708-display-+-arduino.html
// data: http://www.sbprojects.com/knowledge/footprints/sda5708/index.php
// data2: http://www.bralug.de/wiki/Display_SDA5708
// adapted sketch by niq_ro: http://arduinotehniq.blogspot.com/

SDA5708::SDA5708 (int LOAD, int DATA, int SDCLK, int RESET) {
        this->LOAD= LOAD;
        this->DATA= DATA;
        this->SDCLK= SDCLK;
        this->RESET= RESET;

        pinMode(DATA, OUTPUT);      
        pinMode(LOAD, OUTPUT);      
        pinMode(SDCLK, OUTPUT);      
        pinMode(RESET, OUTPUT);      

    }



void SDA5708::init_SDA5708(void)
{
      // RESET toggeln
      digitalWrite(LOAD, HIGH);
      digitalWrite(RESET, LOW);
      digitalWrite(RESET, HIGH);
      Serial.println("SDA init");
}


void SDA5708::send_byte_to_SDA5708(byte letter)
{
	uint8_t x;	
    
	// LOAD auf Low
        digitalWrite(LOAD, LOW);
	// jede Byte-Stelle ans Display senden
	for (x=0; x<=7;x++)	{
		// DATA entsprechend setzen
		if ((letter>>x)&1) {
                  digitalWrite(DATA, HIGH);
                } else {
                  digitalWrite(DATA, LOW);
                }
		// SDCLK toggeln
                digitalWrite(SDCLK, HIGH);
                digitalWrite(SDCLK, LOW);
	}
	// LOAD auf High
      digitalWrite(LOAD, HIGH);
        Serial.print(letter);
        
        Serial.println("***");
}



void SDA5708::brightness_SDA5708(byte val)
{
	// Helligkeit von 0...8, wobei 0 ganz hell ist!
	// mit dem 4.Bit koennte man noch die Multiplex-Impulslaenge des 
	// Display-Controllere manipulieren und damit das Ding noch dunkler
	// machen... (siehe auch Hardware-/Protokoll-Beschreibung oben!)
	send_byte_to_SDA5708(0b11100000|(val&0b00000111));
}


void SDA5708::digit_to_SDA5708(uint8_t sign, uint8_t digit)
{
	uint8_t i;
	// anzeigbares Zeichen? Wenn nein, dann Leerzeichen!
	if ((sign < 0x20) || (sign > 0x7b)) sign = 0x20;
	// Digit im Bereich?
	if (digit > 7) digit = 0;
	// Digit-Adresse zum Display senden
	send_byte_to_SDA5708(0b10100000|digit);
	// jede Zeile des Fonts adressieren, lesen, ausgeben
	for(i=0; i<7; i++) {
		// Font ist linksbuendig, deshalb 3 Bit nach rechts schieben...
        	// Port-Initialisierung, Display-Reset
            Serial.println(sign);
		send_byte_to_SDA5708(pgm_read_byte(&font[(sign-0x20)*7+i])/8);
	}
}


void SDA5708::print2display(char *text)
{
	uint8_t cursor=0;
	char *p=text;
	while (*p) {
		digit_to_SDA5708(*p, cursor);
		cursor++;
		p++;
	}
}
