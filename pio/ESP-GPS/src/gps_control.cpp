#include "gps_control.h"

void process_nmea(DynamicJsonDocument value)
{
    clear_lcd();
    print_lcd("GPS Data",0);
    String msg ;
    serializeJson(value,msg);
    if (value.containsKey("la"))
    {
        if (value.containsKey("ln"))
        {
            print_lcd("Location:", 1);
            print_lcd("Lat : "+String(value["la"]), 2);
            print_lcd("Lng : "+String(value["ln"]), 3);
        }
    }

    if (value.containsKey("d"))
    {
        if (value.containsKey("m"))
        {
            if (value.containsKey("y"))
            {
                String date_val = String(value["d"])+"/"+String(value["m"])+"/"+String(value["y"]);
                print_lcd("Date:", 4);
                print_lcd(date_val, 5);
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