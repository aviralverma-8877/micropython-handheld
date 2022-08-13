#include <ArduinoJson.h>
#include <bb_hx1230.h>
#include <SoftwareSerial.h>
#include <Gpsneo.h>

const byte rxPin = 4;
const byte txPin = 11;
String serialData;

char latitud[11];
char latitudHemisphere[3];
char longitud[11];
char longitudMeridiano[3];

Gpsneo gps(rxPin,txPin);

byte lastPin = 0;

DynamicJsonDocument jsonBuffer(300);
SoftwareSerial myGPS(rxPin, txPin); // RX, TX

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
  Serial.setTimeout(2);
  myGPS.begin(9600);
  pinMode(bkled, OUTPUT);
  hx1230Backlight(1);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);
  pinMode(BTN4, INPUT);
  pinMode(BTN5, INPUT);
}

void serial_check()
{
  if(Serial.available())
  {
    serialData = Serial.readString();
    Serial.flush();
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
      switch(cmd){
        case 0:
          clearLCD();
          break;
        case 1:
          hx1230Backlight(0);
          break;
        case 2:
          hx1230Backlight(1);
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
            hx1230Backlight(0);
            delay(100);
            hx1230Backlight(1);
            delay(100);
          }
          break;
        case 5:
          gps_data();
          break;
        default:
          lcdDisplay("Unknown CMD", 0);
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

void gps_data()
{
  gps.getDataGPRMC( latitud,
                    latitudHemisphere,
                    longitud,
                    longitudMeridiano);
  Serial.print("gps_data('");
  Serial.print(latitud);
  Serial.print("','");
  Serial.print(longitud);
  Serial.println("')");
  lcdDisplay("Latitude:",0);
  lcdDisplay(latitud,1);
  lcdDisplay("Longitude:",2);
  lcdDisplay(longitud,3);
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
}

void clearLCD()
{
  hx1230Fill(0);
}

void lcdDisplay(const char* message, int line)
{ 
  hx1230WriteString(1, line, message, FONT_SMALL, 0);
}
