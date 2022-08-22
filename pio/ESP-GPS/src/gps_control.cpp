#include "gps_control.h"

void process_nmea(DynamicJsonDocument value)
{
    if(gps_recording)
    {
        File gps_record = SPIFFS.open("/track.txt", "a");
        if(gps_record){
            String data;
            serializeJson(value, data);
            gps_record.println(data+"\n");
        }
        gps_record.close();
    }
    clear_lcd();
    String msg ;
    serializeJson(value,msg);
    if (value.containsKey("la"))
    {
        if (value.containsKey("ln"))
        {
            print_lcd("Location:", 0);
            print_lcd(String(value["la"])+", "+String(value["ln"]), 1);
        }
    }

    if (value.containsKey("d"))
    {
        if (value.containsKey("m"))
        {
            if (value.containsKey("y"))
            {
                String date_val = String(value["d"])+"/"+String(value["m"])+"/"+String(value["y"]);
                print_lcd("Date:", 3);
                print_lcd(date_val, 4);
            }
        }
    }


    if (value.containsKey("h"))
    {
        if (value.containsKey("mi"))
        {
            if (value.containsKey("s"))
            {
                print_lcd("Time:", 6);
                String time_val = String(value["h"])+":"+String(value["mi"])+":"+String(value["s"]);
                print_lcd(time_val, 7);
            }
        }
    }
}