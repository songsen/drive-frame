/**
 * @file led_drv.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _LED_DRV_H
#define _LED_DRV_H

#define LED_IOC_MAGIC 'L'
#define LED_ON _IO(LED_IOC_MAGIC, 0)
#define LED_OFF _IO(LED_IOC_MAGIC, 1)

#define LED_IOCTL_MAXNR 2

#endif /*_LED_DRV_H*/