#ifndef __LOGS_H__
#define __LOGS_H__

#define LED_DBG(args...)    printk(KERN_ALERT ## args)
#define LED_INFO(args...)   printk(KERN_ALERT ## args)
#define LED_WARN(args...)   printk(KERN_ALERT ## args)
#define LED_ERR(args...)    printk(KERN_ALERT ## args)

#endif