/**
 * @file timer.c
 * @author your name (you@domain.com)
 * @brief 8253定时器 
 *        单核系统使用，多核系统下使用LAPIC的时钟
 * @version 0.1
 * @date 2022-08-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/types.h"
#include "../include/defs.h"
#include "../include/traps.h"
#include "../include/x86.h"

