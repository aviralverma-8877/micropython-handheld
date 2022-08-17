#ifndef functions
    #define functions
    #include "global_var.h"

    void print_debug(String type, String log);
    void read_serial_inputs();
    void handle_wifi();
    void onWifiConnect(const WiFiEventStationModeGotIP& event);
    void onWifiDisconnect(const WiFiEventStationModeDisconnected& event);
    void enable_ap();
    void setup_web_server();
    void initWebSocket();
    void notifyClients(String msg);
    void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len);
#endif