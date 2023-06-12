#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

const String FIRST_MSG_ROW_0 = "SILAKAN";
#define FIRST_MSG_ROW_1 "MERANGKAI!"

class Display{
    private:
        LiquidCrystal_I2C& lcd;
        void clear(void);
    
    public:
        Display(LiquidCrystal_I2C& lcd);
        void init(void);
        void first_message(void);
        void second_message(void);
        void disp_measurements(float* volt, float* current);
        void custome_message(String msg);
};

#endif
