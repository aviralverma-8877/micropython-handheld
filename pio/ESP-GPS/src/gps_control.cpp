#include "gps_control.h"

void process_nmea(DynamicJsonDocument value)
{
    String nmea_sentences = "";
    for( String kv : value.as<JsonArray>() ) 
    {
        nmea_sentences += kv+'\n';
    }
    for(char r:nmea_sentences)
    {
        if(gps.encode(r))
            displayGPSInfo();
    }
}

void displayGPSInfo()
{
  if (gps.location.isValid())
  {
    print_lcd(String(gps.location.lat()), 1);
    print_lcd(String(gps.location.lng()), 2);
  }

  if (gps.date.isValid())
  {
    String date_val = String(gps.date.day())+"/"+String(gps.date.month())+"/"+String(gps.date.year());
    print_lcd(date_val, 3);
  }

  if (gps.time.isValid())
  {
    String time_val = String(gps.time.hour())+":"+String(gps.time.minute())+":"+String(gps.time.second());
    if (gps.time.hour() < 10) Serial.print(F("0"));
        if (gps.time.minute() < 10) Serial.print(F("0"));
            if (gps.time.second() < 10) Serial.print(F("0"));
            {
                String time_val = String(gps.time.hour())+":"+String(gps.time.minute())+":"+String(gps.time.second());
                print_lcd(time_val, 4);
            }
  }
}