/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/debug/thread_analyzer.h>

#include <app_version.h>

#include "bsp/tbot_bsp.h"

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL
);

int main(void) {
    printk("Zephyr Example Application %s\n", APP_VERSION_STRING);

    if (InitBoard() == false) {
        return -1;
    }

    ToggleLED(LED2);

    TestUartRx();

    while (1) {
//        thread_analyzer_print();

        ToggleLED(LED1);
        ToggleLED(LED2);
        ToggleLED(LED3);

        TestUartTx();
        k_sleep(K_MSEC(500));
    }

    return 0;
}

