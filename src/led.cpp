#include "led.h"

uint8_t val_led = 0;

uint8_t clignoter_led()
{
    val_led = !val_led;
    digitalWrite(16, val_led);

    Serial.print("LED :");
    Serial.println(val_led);

    return val_led;
}

// uint8_t led_value()
// {
//     clignoter_led();
//     return val_led;
// }
