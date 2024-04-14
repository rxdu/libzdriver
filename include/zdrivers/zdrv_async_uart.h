/* 
 * zdrv_async_uart.h
 *
 * Created on 4/14/24 9:33 PM
 * Description:
 *
 * Copyright (c) 2024 Ruixiang Du (rdu)
 */

#ifndef ZDRV_ASYNC_UART_H
#define ZDRV_ASYNC_UART_H

#include <zephyr/device.h>
#include <zephyr/toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

__subsystem struct zdrv_async_uart_driver_api {
//    int (*zdrv_async_uart_setup)(const struct device *dev);
};

//__syscall int zdrv_async_uart_setup(const struct device *dev);
//
//static inline int z_impl_zdrv_async_uart_setup(const struct device *dev) {
//    const struct zdrv_async_uart_driver_api *api =
//            (const struct zdrv_async_uart_setup *) dev->api;
//    return api->zdrv_async_uart_setup(dev);
//}

#ifdef __cplusplus
}
#endif

#endif //ZDRV_ASYNC_UART_H
