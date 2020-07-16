#include <Arduino.h>

#include "led.h"
#include "connection.h"
#include "time.h"

boolean reveil = false;
const int buttonInput = 5; // D1
uint16_t heure_save = 0;

// Checks if motion was detected, sets LED HIGH and starts a timer
ICACHE_RAM_ATTR void buttonPressed()
{
    reveil = false;
    Serial.println("arrêt reveil !");
}

void setup()
{
    // Mettre GPIO (General Purpose Input Output) en INPUT (Entrée) : Bouton
    pinMode(buttonInput, INPUT);
    attachInterrupt(digitalPinToInterrupt(buttonInput), buttonPressed, RISING);

    pinMode(5, INPUT);               // Mettre GPIO (General Purpose Input Output) D1 en INPUT (Entrée) : Bouton
    pinMode(16, OUTPUT);             // Mettre GPIO (General Purpose Input Output) D0 en OUTPUT (Sortie) : LED
    pinMode(LED_BUILTIN, OUTPUT);    // Onboard LED
    digitalWrite(LED_BUILTIN, HIGH); // Switch off LED

    Serial.begin(115200);

    connecting_wifi_network();
    setup_ntp();
}

void loop()
{
    uint16_t heure = get_time();
    display_time(heure);

    if (heure != heure_save)
    {
        heure_save = heure;

        // if (heure == 950)
        if (heure % 2 == 0)
        {
            reveil = true;
            Serial.println("reveil declanché !");
        }
    }

    if (reveil)
    {
        clignoter_led();
    }
}
