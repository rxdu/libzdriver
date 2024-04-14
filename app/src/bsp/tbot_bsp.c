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
#include <zephyr/drivers/uart.h>

#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

//#define USART2_DEVICE_NODE DT_NODELABEL(usart2)
//static const struct device *const usart2_dev = DEVICE_DT_GET(USART2_DEVICE_NODE);
//
//#define UART4_DEVICE_NODE DT_NODELABEL(uart4)
//static const struct device *const uart4_dev = DEVICE_DT_GET(UART4_DEVICE_NODE);

//#define ASYNC_UART2_DEVICE_NODE DT_NODELABEL(zdrv_async_usart2)
#define ASYNC_UART2_DEVICE_NODE DT_NODELABEL(async_uart2)
static const struct device *const async_uart2_dev = DEVICE_DT_GET(ASYNC_UART2_DEVICE_NODE);

struct uart_config uart_cfg = {
        .baudrate = 115200,
        .parity = UART_CFG_PARITY_NONE,
        .stop_bits = UART_CFG_STOP_BITS_1,
        .flow_ctrl = UART_CFG_FLOW_CTRL_NONE,
        .data_bits = UART_CFG_DATA_BITS_8,
};

void uart_callback(const struct device *dev, struct uart_event *evt, void *user_data) {
    ARG_UNUSED(user_data);

//    if (evt->type == UART_TX_DONE) {
//        printk("TX_DONE\n");
//    } else if (evt->type == UART_TX_ABORTED) {
//        printk("TX_ABORTED\n");
//    } else
    if (evt->type == UART_RX_RDY) {
        printk("RX_RDY\n");
    } else if (evt->type == UART_RX_BUF_REQUEST) {
        printk("RX_BUF_REQUEST\n");
    } else if (evt->type == UART_RX_BUF_RELEASED) {
        printk("RX_BUF_RELEASED\n");
    } else if (evt->type == UART_RX_DISABLED) {
        printk("RX_DISABLED\n");
    } else if (evt->type == UART_RX_STOPPED) {
        printk("RX_STOPPED\n");
    }
}

bool InitBoard(void) {
    // gpio
    if (!gpio_is_ready_dt(&led1) || !gpio_is_ready_dt(&led2) || !gpio_is_ready_dt(&led3)) {
        return false;
    }

    if (gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE) < 0 || gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE) < 0 ||
        gpio_pin_configure_dt(&led3, GPIO_OUTPUT_ACTIVE) < 0) {
        printk("Error: failed to configure LED device\n");
        return false;
    }

    // uart
//    if (!device_is_ready(usart2_dev)) {
//        printk("USART2 device not found!");
//        return false;
//    }
//
//    int rc = uart_configure(usart2_dev, &uart_cfg);
//    if (rc) {
//        printk("Could not configure device %s", usart2_dev->name);
//    }
//
//    uart_callback_set(usart2_dev, uart_callback, NULL);
//
//    if (!device_is_ready(uart4_dev)) {
//        printk("UART4 device not found!");
//        return 0;
//    }

    // async uart
    if (!device_is_ready(async_uart2_dev)) {
        printk("ASYNC_UART2 device not found!");
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

//void TestUartRx(void) {
//    uint8_t rx_data[100];
//    int32_t timeout = 50000;
//    int ret = uart_rx_enable(usart2_dev, rx_data, sizeof(rx_data), timeout);
//    if (ret < 0) {
//        printk("Error receiving data\n");
//    }
//}
//
//void TestUartTx(void) {
//    uint8_t tx_data[] = "Filler text is text that shares some characteristics of a real written text, but is random or otherwise generated. It may be used to display a sample of fonts, generate text for testing, or to spoof an e-mail spam filter.";
//
//    int32_t timeout = 50000;
////    printk("Sending data of size: %d\n", sizeof(tx_data));
//    int ret = uart_tx(usart2_dev, tx_data, sizeof(tx_data), timeout);
//    if (ret < 0) {
//        printk("Error sending data\n");
//    }
////    printk("Data sent: %s", tx_data);
//}
