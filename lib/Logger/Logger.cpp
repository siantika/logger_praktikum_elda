#include "Logger.h"

// private
String Logger::get_date()
{
    DS3231 rtc(A4, A5);
    rtc.begin();
    return rtc.getDateStr();
}

String Logger::get_time()
{
    DS3231 rtc(A4, A5);
    rtc.begin();
    return rtc.getTimeStr();
}

uint8_t Logger::init(uint8_t pin_cs)
{
    uint8_t opt = !SD.begin(pin_cs);
    return opt;
}

void Logger::log(float &voltage_in, float &current_in,
                 float &voltage_out, float &current_out, String file_name)
{
    File dataFile = SD.open(file_name, FILE_WRITE);
    if (dataFile)
    {
        dataFile.print("DATE,\t");
        dataFile.print("TIME,\t");
        dataFile.print("VOLTAGE IN(V),\t");
        dataFile.print("CURRENT IN(A),\t");
        dataFile.print("VOLTAGE OUT(V),\t");
        dataFile.println("CURRENT OUT(A),\t");
        dataFile.print(get_date());
        dataFile.print(",\t");
        dataFile.print(get_time());
        dataFile.print(",\t");
        dataFile.print(String(voltage_in));
        dataFile.print(",\t");
        dataFile.print(String(current_in));
        dataFile.print(",\t");
        dataFile.print(String(voltage_out));
        dataFile.print(",\t");
        dataFile.println(String(current_out));
        dataFile.close();
    }
    else
    {
        Serial.println("error opening datalog.txt");
    }
}
