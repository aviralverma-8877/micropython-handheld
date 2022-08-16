#include <ArduinoJson.h>
#include <bb_hx1230.h>
#include <SoftwareSerial.h>

const byte rxPin = 4;
const byte txPin = 11;

String serialData;
String gpsData;

byte lastPin = 0;

DynamicJsonDocument jsonBuffer(500);
SoftwareSerial GPS_serial(rxPin, txPin); // RX, TX

#define bkled 5
#define BTN1 6
#define BTN2 7
#define BTN3 8
#define BTN4 9
#define BTN5 10

byte w = 84;
byte h = 48;

void setup() {
  hx1230Init(2, 5, 3, 12, 13, 0, 0); // on the ATtiny85, I wired CE to ground, and BL to Vcc, so 3 pins are needed.
  hx1230Fill(0);      // erase display memory
  hx1230SetContrast(5);
  
  Serial.begin(9600);
  Serial.setTimeout(5);
  GPS_serial.begin(9600);
  GPS_serial.setTimeout(5);
  
  pinMode(bkled, OUTPUT);
  digitalWrite(bkled,HIGH);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);
  pinMode(BTN4, INPUT);
  pinMode(BTN5, INPUT);
}

void gps_data()
{
  if(GPS_serial.available())
  {
    while(GPS_serial.available()){GPS_serial.read();}
  }
  while(!GPS_serial.available()){;}
  delay(10);
  gpsData = "";
  jsonBuffer.clear();
  jsonBuffer["action"] = "gps_data";
  while(GPS_serial.available())
  {
    gpsData = GPS_serial.readString();
    gpsData.trim();
  }
  jsonBuffer["value"] = gpsData;
  serializeJson(jsonBuffer, Serial);
  Serial.println();
  while(GPS_serial.available()){GPS_serial.read();}
}

void serial_check()
{
  if(Serial.available())
  {
    serialData = "";
    while(Serial.available())
    {
      serialData += Serial.readString();
    }
    serialData.trim();
    String command = "";
    for(int i=0; i<serialData.length(); i++)
    {
      if(serialData[i] == '\n')
      {
        controller(command);
        command = "";
      }
      else
      {
        command += serialData[i];
      }
    }
    controller(command);
  }
}

void controller(String command)
{
  jsonBuffer.clear();
  DeserializationError error = deserializeJson(jsonBuffer, command);
  if (error) {
    return;
  }  
  if(jsonBuffer.containsKey("c"))
  {
    int cmd;
    cmd = int(jsonBuffer["c"]);
    switch(cmd){
      case 0:
        clearLCD();
        break;
      case 1:
        digitalWrite(bkled,!digitalRead(bkled));
        break;
      case 2:
        if(jsonBuffer.containsKey("v"))
        {
          int v = int(jsonBuffer["v"]);
          hx1230SetContrast(v);
        }
        break;
      case 3:
        for(int i=0; i<5; i++)
        {
          digitalWrite(bkled,!digitalRead(bkled));
          delay(100);
          digitalWrite(bkled,!digitalRead(bkled));
          delay(100);
        }
        break;
      case 4:
        gps_data();
        break;
      default:
        clearLCD();
        lcdDisplay("Unknown CMD", 0);
        break;
    }
  }
  if(jsonBuffer.containsKey("m"))
  {
    if(jsonBuffer.containsKey("l"))
    {
      const char* msg;
      int line;
      msg = jsonBuffer["m"];
      line = int(jsonBuffer["l"]);
      lcdDisplay(msg, line);
    }
  }
}

void button_check()
{
  if(digitalRead(BTN1) == HIGH)
  {
    delay(10);
    if(lastPin != 1)
    {
      lastPin = 1;
      jsonBuffer.clear();
      jsonBuffer["action"] = "botton_press";
      jsonBuffer["value"] = "top_left";
      serializeJson(jsonBuffer, Serial);
      Serial.println();
    }
  }
  else if(digitalRead(BTN2) == HIGH)
  {
    delay(10);
    if(lastPin != 2)
    {
      lastPin = 2;
      jsonBuffer.clear();
      jsonBuffer["action"] = "botton_press";
      jsonBuffer["value"] = "top_right";
      serializeJson(jsonBuffer, Serial);
      Serial.println();
    }
  }
  else if(digitalRead(BTN3) == HIGH)
  {
    delay(10);
    if(lastPin != 3)
    {
      lastPin = 3;
      jsonBuffer.clear();
      jsonBuffer["action"] = "botton_press";
      jsonBuffer["value"] = "bottom_left";
      serializeJson(jsonBuffer, Serial);
      Serial.println();
    }
  }  
  else if(digitalRead(BTN4) == HIGH)
  {
    delay(10);
    if(lastPin != 4)
    {
      lastPin = 4;
      jsonBuffer.clear();
      jsonBuffer["action"] = "botton_press";
      jsonBuffer["value"] = "bottom_right";
      serializeJson(jsonBuffer, Serial);
      Serial.println();
    }
  }
  else if(digitalRead(BTN5) == HIGH)
  {
    delay(10);
    if(lastPin != 5)
    {
      lastPin = 5;
      jsonBuffer.clear();
      jsonBuffer["action"] = "botton_press";
      jsonBuffer["value"] = "select";
      serializeJson(jsonBuffer, Serial);
      Serial.println();
    }
  }
  else
  {
    lastPin = 0;
    serial_check();
  }
}

void loop() {
  button_check();
}

void clearLCD()
{
  hx1230Fill(0);
  delay(1);
}

void lcdDisplay(const char* message, int line)
{ 
  hx1230WriteString(1, line, message, FONT_SMALL, 0);
}
