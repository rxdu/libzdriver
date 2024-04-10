# SPDX-License-Identifier: Apache-2.0

add_subdirectory_ifdef(CONFIG_SBUS sbus)
add_subdirectory_ifdef(CONFIG_VESC vesc)
add_subdirectory_ifdef(CONFIG_ROBOTIO robotio)
