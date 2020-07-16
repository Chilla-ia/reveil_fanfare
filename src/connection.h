#ifndef CONNECTION_H
#define CONNECTION_H

#define STASSID "TouchMetiv"
#define STAPSK "tupuesdesbras"

#include <Arduino.h>
#include <ESP8266WiFi.h>

void onSTAConnected(WiFiEventStationModeConnected ipInfo);
void onSTAGotIP(WiFiEventStationModeGotIP ipInfo);
void onSTADisconnected(WiFiEventStationModeDisconnected event_info);
void connecting_wifi_network(void);

#endif