/* 
 * zdrv_async_uart.c
 *
 * Created on 4/14/24 10:06 PM
 * Description:
 *
 * Copyright (c) 2024 Ruixiang Du (rdu)
 */

#define DT_DRV_COMPAT zdriver_async_uart

#include <zephyr/device.h>
#include <zephyr/devicetree.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "zdrivers/zdrv_async_uart.h"

LOG_MODULE_REGISTER(zdriver_async_uart, CONFIG_ZDRV_ASYNC_UART_LOG_LEVEL
);

struct zdrv_async_uart_config {
    const struct device *uart_dev;
    unsigned int period_ms;
};

struct zdrv_async_uart_data {
    unsigned int period_ms;
};

static int async_uart_init(const struct device *dev) {
    const struct zdrv_async_uart_config *config = dev->config;
    struct zdrv_async_uart_data *data = dev->data;

    printk("zdrv async uart device name: %s\n", dev->name);

    data->period_ms = config->period_ms;

    return 0;
}

static const struct zdrv_async_uart_driver_api zdrv_async_uart_api = {
//        .zdrv_async_uart_setup = async_uart_init
};

#define ZDRV_ASYNC_UART_DEFINE(inst) \
    static struct zdrv_async_uart_data data##inst;                          \
                                                                            \
    static const struct zdrv_async_uart_config config##inst = {             \
        .uart_dev = DEVICE_DT_GET(DT_INST_PARENT(inst)),                    \
        .period_ms = DT_INST_PROP_OR(inst, blink_period_ms, 0U),            \
    };                                                                      \
                                                                            \
	DEVICE_DT_INST_DEFINE(inst, async_uart_init, NULL, &data##inst,     \
			      &config##inst, POST_KERNEL,                      \
			      CONFIG_ZDRV_ASYNC_UART_INIT_PRIORITY,                      \
			      &zdrv_async_uart_api);

DT_INST_FOREACH_STATUS_OKAY(ZDRV_ASYNC_UART_DEFINE)