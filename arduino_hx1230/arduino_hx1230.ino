#include <ArduinoJson.h>
#include <bb_hx1230.h>
#include <SoftwareSerial.h>

#define SERIAL_BUFFER_SIZE 256
const byte rxPin = 4;
const byte txPin = 11;

String serialData;
String gpsData;

byte lastPin = 0;

StaticJsonDocument<1000> jsonBuffer;
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
  
  Serial.begin(115200);
  
  GPS_serial.begin(9600);

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
    while(GPS_serial.available())
    {
      GPS_serial.read();
    }
  }
  while(!GPS_serial.available()){;}
  gpsData = "";
  while(GPS_serial.available())
  {
      gpsData = GPS_serial.readStringUntil('\n');
      gpsData.trim();
      Serial.print("gps_data('");
      Serial.print(gpsData);
      Serial.println("')");
  }
}

void serial_check()
{
  if(Serial.available())
  {
    serialData = Serial.readStringUntil('\n');
    while(Serial.available())
      char r = Serial.read();
    serialData.trim();
    jsonBuffer.clear();
    DeserializationError error = deserializeJson(jsonBuffer, serialData);
    if (error) {
      return;
    }  
    if(jsonBuffer.containsKey("c"))
    {
      int cmd;
      cmd = int(jsonBuffer["c"]);
      Serial.println(cmd);
      switch(cmd){
        case 0:
          clearLCD();
          break;
        case 1:
          digitalWrite(bkled,LOW);
          break;
        case 2:
          digitalWrite(bkled,HIGH);
          break;
        case 3:
          if(jsonBuffer.containsKey("v"))
          {
            int v = int(jsonBuffer["v"]);
            hx1230SetContrast(v);
          }
          break;
        case 4:
          for(int i=0; i<5; i++)
          {
            digitalWrite(bkled,!digitalRead(bkled));
            delay(100);
            digitalWrite(bkled,!digitalRead(bkled));
            delay(100);
          }
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
}

void button_check()
{
  if(digitalRead(BTN1) == HIGH)
  {
    delay(10);
    if(lastPin != 1)
    {
      lastPin = 1;
      Serial.println("left_top()");
    }
  }
  else if(digitalRead(BTN2) == HIGH)
  {
    delay(10);
    if(lastPin != 2)
    {
      lastPin = 2;
      Serial.println("right_top()");
    }
  }
  else if(digitalRead(BTN3) == HIGH)
  {
    delay(10);
    if(lastPin != 3)
    {
      lastPin = 3;
      Serial.println("left_bottom()");
    }
  }  
  else if(digitalRead(BTN4) == HIGH)
  {
    delay(10);
    if(lastPin != 4)
    {
      lastPin = 4;
      Serial.println("right_bottom()");
    }
  }
  else if(digitalRead(BTN5) == HIGH)
  {
    delay(10);
    if(lastPin != 5)
    {
      lastPin = 5;
      gps_data();
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
  delay(1);
}

void clearLCD()
{
  hx1230Fill(0);
}

void lcdDisplay(const char* message, int line)
{ 
  hx1230WriteString(1, line, message, FONT_SMALL, 0);
}
