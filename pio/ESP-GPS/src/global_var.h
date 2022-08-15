#ifndef global_var
    #define global_var
    #include <Arduino.h>
    #include <ESP8266WiFi.h>
    #include <Ticker.h>
    #include <ArduinoJson.h>
    #include <DNSServer.h>
    #include <ESPAsyncTCP.h>
    #include <ESPAsyncWebServer.h>
    #include <ESP8266mDNS.h> 

    #include "functions.h"
    #include "button_control.h"
    #include "gps_control.h"
    #include "lcd_functions.h"
    
    extern Ticker TickerForSerial;
    extern bool debug_mode;
    extern WiFiEventHandler wifiConnectHandler;
    extern WiFiEventHandler wifiDisconnectHandler;
    extern IPAddress apIP;
    extern IPAddress apGatewayIP;
    extern IPAddress apSubnet;
    extern AsyncWebServer server;
    extern DNSServer dnsServer;
    extern AsyncWebSocket webSocket;
#endif // MACRO

