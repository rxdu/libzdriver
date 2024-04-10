#-------------------------------------------------------------------------------
# Zephyr Example Application
#
# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(app LANGUAGES C)

if (CONFIG_BOARD_TBOT)
    message(STATUS "Building with BSP: tbot")
    set(BSP_SRC src/bsp/tbot_bsp.c)
endif ()

target_sources(app PRIVATE src/main.c ${BSP_SRC})
target_include_directories(app PRIVATE src)
