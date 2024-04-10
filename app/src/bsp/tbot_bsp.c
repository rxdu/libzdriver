/* 
 * tbot.c
 *
 * Created on 4/10/24 11:24 PM
 * Description:
 *
 * Copyright (c) 2024 Ruixiang Du (rdu)
 */

#include "tbot_bsp.h"

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

bool InitBoard(void) {
    if (!gpio_is_ready_dt(&led1) || !gpio_is_ready_dt(&led2) || !gpio_is_ready_dt(&led3)) {
        return false;
    }

    if (gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE) < 0 || gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE) < 0 ||
        gpio_pin_configure_dt(&led3, GPIO_OUTPUT_ACTIVE) < 0) {
        printk("Error: failed to configure LED device\n");
        return false;
    }

    return true;
}

void ToggleLED(LED led) {
    switch (led) {
        case LED1:
            gpio_pin_toggle_dt(&led1);
            break;
        case LED2:
            gpio_pin_toggle_dt(&led2);
            break;
        case LED3:
            gpio_pin_toggle_dt(&led3);
            break;
        default:
            break;
    }
}
