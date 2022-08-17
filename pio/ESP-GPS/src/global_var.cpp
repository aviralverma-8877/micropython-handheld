#include "global_var.h"

Ticker TickerForGPS;
bool debug_mode = false;
bool gps_recording = false;
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
IPAddress apIP(192, 168, 4, 1);
IPAddress apGatewayIP(192, 168, 4, 1);
IPAddress apSubnet(255, 255, 255, 0);
AsyncWebServer server(80);
DNSServer dnsServer;
AsyncWebSocket webSocket("/ws");
