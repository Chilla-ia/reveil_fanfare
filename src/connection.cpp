#include "connection.h"

const char *ssid = STASSID;
const char *password = STAPSK;
bool wifiFirstConnected = false;

void onSTAConnected(WiFiEventStationModeConnected ipInfo)
{
    Serial.printf("Connected to %s\r\n", ipInfo.ssid.c_str());
}
// Start NTP only after IP network is connected
void onSTAGotIP(WiFiEventStationModeGotIP ipInfo)
{
    Serial.printf("Got IP: %s\r\n", ipInfo.ip.toString().c_str());
    Serial.printf("Connected: %s\r\n", WiFi.status() == WL_CONNECTED ? "yes" : "no");
    digitalWrite(LED_BUILTIN, LOW); // Turn on LED
    wifiFirstConnected = true;
}
// Manage network disconnection
void onSTADisconnected(WiFiEventStationModeDisconnected event_info)
{
    Serial.printf("Disconnected from SSID: %s\n", event_info.ssid.c_str());
    Serial.printf("Reason: %d\n", event_info.reason);
    digitalWrite(LED_BUILTIN, HIGH); // Turn off LED
    //NTP.stop(); // NTP sync can be disabled to avoid sync errors
    WiFi.reconnect();
}

void connecting_wifi_network(void)
{
    static WiFiEventHandler e1, e2, e3;
    e1 = WiFi.onStationModeGotIP(onSTAGotIP); // As soon WiFi is connected, start NTP Client
    e2 = WiFi.onStationModeDisconnected(onSTADisconnected);
    e3 = WiFi.onStationModeConnected(onSTAConnected);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}