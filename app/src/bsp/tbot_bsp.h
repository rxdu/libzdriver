/* 
 * tbot.h
 *
 * Created on 4/10/24 11:24 PM
 * Description:
 *
 * Copyright (c) 2024 Ruixiang Du (rdu)
 */

#ifndef LIBZDRIVER_TBOT_H
#define LIBZDRIVER_TBOT_H

#include <stdbool.h>

typedef enum {
    LED1,
    LED2,
    LED3
} LED;

bool InitBoard(void);

void ToggleLED(LED led);

#endif //LIBZDRIVER_TBOT_H
