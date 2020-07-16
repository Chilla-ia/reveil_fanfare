#include "time.h"
extern bool wifiFirstConnected;

TM1637Display display(CLK, DIO);

int8_t timeZone = 1;
int8_t minutesTimeZone = 0;

const PROGMEM char *ntpServer = "pool.ntp.org";

boolean syncEventTriggered = false; // True if a time even has been triggered
NTPSyncEvent_t ntpEvent;            // Last triggered event

void setup_ntp()
{

    NTP.onNTPSyncEvent([](NTPSyncEvent_t event) {
        ntpEvent = event;
        syncEventTriggered = true;
    });

    Serial.println("NTP OK !");
}

void processSyncEvent(NTPSyncEvent_t ntpEvent)
{

    if (ntpEvent < 0)
    {
        Serial.printf("Time Sync error: %d\n", ntpEvent);
        if (ntpEvent == noResponse)
            Serial.println("NTP server not reachable");
        else if (ntpEvent == invalidAddress)
            Serial.println("Invalid NTP server address");
        else if (ntpEvent == errorSending)
            Serial.println("Error sending request");
        else if (ntpEvent == responseError)
            Serial.println("NTP response error");
    }
    else
    {
        if (ntpEvent == timeSyncd)
        {
            Serial.print("Got NTP time: ");
            Serial.println(NTP.getTimeDateString(NTP.getLastNTPSync()));
        }
    }
}

uint16_t get_time()
{
    static int i = 0;
    static int last = 0;
    if (wifiFirstConnected)
    {
        wifiFirstConnected = false;
        NTP.setInterval(63);
        NTP.setNTPTimeout(NTP_TIMEOUT);
        NTP.begin(ntpServer, timeZone, true, minutesTimeZone);
    }
    if (syncEventTriggered)
    {
        processSyncEvent(ntpEvent);
        syncEventTriggered = false;
    }

    uint8_t heure = hour();
    uint8_t min = minute();
    uint16_t heureXmin = (heure * 100) + min;

    if ((millis() - last) > SHOW_TIME_PERIOD)
    {
        //Serial.println(millis() - last);
        last = millis();
        Serial.println(NTP.getTimeDateString());
        // Serial.println(heure);
        // Serial.println(min);
        i++;
    }
    return heureXmin;
}

void display_time(uint16_t hour)
{

    display.clear();
    display.setBrightness(0x0f);

    display.showNumberDec(hour, true);
    display.showNumberDecEx(hour, (0xf0), true);
    delay(1000);
}
