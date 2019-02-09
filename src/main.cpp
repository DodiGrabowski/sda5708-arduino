#include <Arduino.h>

/*

*/

#include <sda5708.h>


SDA5708 sda(19,18,5,17); // int LOAD, int DATA, int SDCLK int RESET

void setup() {
  // Port-Initialisierung, Display-Reset
	sda.init_SDA5708();
}

void loop() {

  int i;

  sda.print2display("SDA 5708"); 

  // put your main code here, to run repeatedly:
  while(1) {
    // anzeige faden lassen
      for (i=6; i>-1; i--) {
        sda.brightness_SDA5708(i);
        delay(250);
          }
        delay(150);
      for (i=0; i<7; i++) {
        sda.brightness_SDA5708(i);
        delay(250);
          }
        }
}