#ifndef TIME_H
#define TIME_H

#define CLK 0
#define DIO 4

#define SHOW_TIME_PERIOD 1000
#define NTP_TIMEOUT 1500

#include <Arduino.h>

#include <Time.h>
#include <TimeLib.h>
#include <Timezone.h>
#include <TM1637Display.h>
#include <NTPClientLib.h>
#include <ESP8266WiFi.h>

void setup_ntp();
void processSyncEvent(NTPSyncEvent_t ntpEvent);
uint16_t get_time();
void display_time(uint16_t);

#endif