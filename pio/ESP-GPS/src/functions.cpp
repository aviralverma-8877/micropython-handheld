#include "functions.h"

class CaptiveRequestHandler : public AsyncWebHandler {
  public:
    CaptiveRequestHandler() {}
    virtual ~CaptiveRequestHandler() {}

    bool canHandle(AsyncWebServerRequest *request){
      //request->addInterestingHeader("ANY");
      return true;
    }

    void handleRequest(AsyncWebServerRequest *request) {
        File index = SPIFFS.open("/index.html", "r");
        if(index)
        {
            AsyncResponseStream *response = request->beginResponseStream("text/html");
            response->printf("<!DOCTYPE html><html><head><meta http-equiv=\"refresh\" content=\"3;url=http://%s/index\" /><title>Redirecting...</title></head><body>", WiFi.softAPIP().toString().c_str());
            response->printf("<p>Redirecting to <a href='http://%s/index'>this link</a><br />Please Wait.....</p>", WiFi.softAPIP().toString().c_str());
            response->print("</body></html>");
            request->send(response);
        }
        else
            print_debug("ERROR","SPIFFS not found");
        index.close();
    }
};

void print_debug(String type, String log)
{
    if(debug_mode)
    {
        Serial.println();
        Serial.print(type);
        Serial.print(" >> ");
        Serial.println(log.c_str());
    }
}

void read_serial_inputs()
{
    if(Serial.available())
    {
        String serial_data = "";
        serial_data = Serial.readString();       
        serial_data.trim();
        print_debug("DEBUG",serial_data);
        DynamicJsonDocument doc(500);
        DeserializationError error = deserializeJson(doc, serial_data);
        if(error)
        {
            print_debug("ERROR",error.c_str());
            return;
        }
        if(doc.containsKey("action"))
        {
            if(doc.containsKey("value"))
            {
                String action = doc["action"];
                String value = doc["value"];
                print_debug("DEBUG",action);
                print_debug("DEBUG",value);
                if(action.equals(String("botton_press")))
                {
                    if(value.equals("top_right"))
                    {
                        top_right(value);
                    }
                    if(value.equals("top_left"))
                    {
                        top_left(value);
                    }
                    if(value.equals("bottom_right"))
                    {
                        bottom_right(value);
                    }
                    if(value.equals("bottom_left"))
                    {
                        bottom_left(value);
                    }
                    if(value.equals("select"))
                    {
                        select(value);
                    }
                }
                if(action.equals(String("gps_data")))
                {
                    process_nmea(value);
                }
            }
        }
    }
}

void handle_wifi()
{
    wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
    wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
    int start = millis();
    WiFi.begin();
    while(WiFi.status() != WL_CONNECTED)
    {
        int current = millis();
        if((current - start) > 1000)
            break;
    }
    if(WiFi.status() == WL_CONNECTED)
    {
        String ssid = WiFi.SSID();
        print_debug("DEBUG","WiFi Connected to "+ssid);
    }
}

void onWifiConnect(const WiFiEventStationModeGotIP& event)
{

}

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event)
{

}

void enable_ap()
{
  print_debug("DEBUG","Enabling AP");
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apGatewayIP, apSubnet);
  WiFi.softAP("neo-6m", "", 10);
}

void setup_web_server()
{
    print_debug("DEBUG","Setting up webserver");
    dnsServer.start(53, "*", WiFi.softAPIP());
    server.on("/index", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        File index = SPIFFS.open("/index.html", "r");
        if(index)
            request->send(SPIFFS, "/index.html", "text/html");
        else
            print_debug("ERROR","Index not found");
        index.close();
    });
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        File index = SPIFFS.open("/index.html", "r");
        if(index)
            request->send(SPIFFS, "/index.html", "text/html");
        else
            print_debug("ERROR","Index not found");
        index.close();
    });
    serv
    server.serveStatic("/script.js", SPIFFS, "/script.js");
    initWebSocket();
    server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
    server.begin();
    if (MDNS.begin("neo6m")) {  //Start mDNS with name esp8266
      MDNS.addService("http", "tcp", 80);
      print_debug("DEBUG","MDNS has started");
    }
}

void notifyClients(String msg) {
  webSocket.textAll(msg);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    String ws_data = "";
    char r;
    for(int i=0; i<len; i++)
    {
        r = data[i];
        ws_data += r;
    }
    DynamicJsonDocument doc(500);
    DeserializationError error = deserializeJson(doc, ws_data);
    if(error)
    {
        print_debug("ERROR",error.c_str());
        return;
    }
    print_debug("DEBUG",ws_data);
    if(doc.containsKey("action"))
    {
        String action = doc["action"];
        print_debug("DEBUG",action);
        if((bool)action.equals(String("wifi_update")))
        {
            if(doc.containsKey("ssid"))
            {
                String ssid = doc["ssid"];
                print_debug("DEBUG",ssid);
                if(doc.containsKey("psk"))
                {
                    String psk = doc["psk"];
                    print_debug("DEBUG","Connecting wifi to "+ssid+" / "+psk);
                    WiFi.disconnect();
                    WiFi.mode(WIFI_STA);
                    WiFi.begin(ssid,psk);
                    WiFi.setAutoReconnect(true);
                    WiFi.persistent(true);
                    DynamicJsonDocument res(100);
                    res["action"] = "alret";
                    res["msg"] = "WiFi switched to "+ssid;
                    String msg;
                    serializeJsonPretty(res, msg);
                    notifyClients(msg);
                }
                else
                    return;
            }
            else
                return;
        }
        else
            return;
    }
    else
        return;
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        print_debug("DEBUG","WebSocket client connected from "+ client->remoteIP().toString());
        break;
      case WS_EVT_DISCONNECT:
        print_debug("DEBUG","WebSocket client disconnected");
        break;
      case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}

void initWebSocket() {
    webSocket.onEvent(onEvent);
    server.addHandler(&webSocket);
}