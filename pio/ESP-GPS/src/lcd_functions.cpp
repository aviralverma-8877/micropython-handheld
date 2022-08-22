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
    print_lcd("    Neo 6M", 3);
    print_lcd("   Tracker", 4);
    alert_lcd();
    Serial.flush();
}