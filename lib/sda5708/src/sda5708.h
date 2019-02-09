#ifndef __SDA_5708__
#define __SDA_5708__


// Library für __SDA_5708__

#include <Arduino.h>

class SDA5708 {
  private:
    int LOAD;
    int DATA;
    int SDCLK;
    int RESET;

  public:
    SDA5708 (int LOAD, int DATA, int SDCLK, int RESET);
    
    void init_SDA5708();

    void brightness_SDA5708(byte val);

    void digit_to_SDA5708(byte sign, byte digit);

    void send_byte_to_SDA5708(byte letter);

    void print2display(char *text);
};

#endif

