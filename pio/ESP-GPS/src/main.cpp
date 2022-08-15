#include "global_var.h"

void setup() {
  SPIFFS.begin();
  Serial.begin(9600);
  Serial.setTimeout(10);
  
  handle_wifi();
  setup_web_server();

  print_debug("DEBUG","Ready");
  print_intro();
}

void loop() {
  dnsServer.processNextRequest();
  MDNS.update();
  read_serial_inputs();
}