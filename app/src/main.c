/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#include <app_version.h>

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL
);

#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

int main(void) {
    printk("Zephyr Example Application %s\n", APP_VERSION_STRING);

    if (!gpio_is_ready_dt(&led1) || !gpio_is_ready_dt(&led2) || !gpio_is_ready_dt(&led3)) {
        return -1;
    }

    if (gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE) < 0 || gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE) < 0 ||
        gpio_pin_configure_dt(&led3, GPIO_OUTPUT_ACTIVE) < 0) {
        printk("Error: failed to configure LED device\n");
        return -1;
    }

    while (1) {
        gpio_pin_toggle_dt(&led1);
        gpio_pin_toggle_dt(&led2);
        gpio_pin_toggle_dt(&led3);

        k_sleep(K_MSEC(500));
    }

    return 0;
}

