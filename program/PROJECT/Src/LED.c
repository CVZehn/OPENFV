#include "led.h"

void led_red_on()
{
     LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_10);
}

void led_red_off()
{
     LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_10);
}
void led_red_toggle()
{
     LL_GPIO_TogglePin(GPIOE, LL_GPIO_PIN_10);
}

void led_blue_on()
{
     LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_11);
}

void led_blue_off()
{
     LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_11);
}
void led_blue_toggle()
{
     LL_GPIO_TogglePin(GPIOE, LL_GPIO_PIN_11);
}