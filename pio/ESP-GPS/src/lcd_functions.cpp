#include "lcd_functions.h"

void print_lcd(String msg, int line)
{
    DynamicJsonDocument doc(200);
    doc["m"] = msg;
    doc["l"] = line;
    serializeJson(doc, Serial);
    Serial.println();
}

void clear_lcd()
{
    DynamicJsonDocument doc(200);
    doc["c"] = 0;
    serializeJson(doc, Serial);
    Serial.println();
}

void toggle_bkled()
{
    DynamicJsonDocument doc(200);
    doc["c"] = 1;
    serializeJson(doc, Serial);
    Serial.println();
}

void set_lcd_contrast(int value)
{
    DynamicJsonDocument doc(200);
    doc["c"] = 2;
    doc["v"] = value;
    serializeJson(doc, Serial);
    Serial.println();
}

void alert_lcd()
{
    DynamicJsonDocument doc(200);
    doc["c"] = 3;
    serializeJson(doc, Serial);
    Serial.println();
}

void get_gps_data()
{
    DynamicJsonDocument doc(200);
    doc["c"] = 4;
    serializeJson(doc, Serial);
    Serial.println();
}

void print_intro()
{
    set_lcd_contrast(5);
    clear_lcd();
    print_lcd("Hello World", 0);
    print_lcd("Welcome To", 1);
    print_lcd("Neo 6M", 2);
    print_lcd("WiFi Status", 3);
    if(WiFi.status() == WL_CONNECTED)
    {
        print_lcd("Connected", 4);
        print_lcd(WiFi.localIP().toString(),5);
    }
    else{
        print_lcd("Disonnected", 4);
    }
    alert_lcd();
    Serial.flush();
}