#ifndef __LOGS_H__
#define __LOGS_H__

extern unsigned int dbg;

#define LED_DBG(fmt, args...)  do{  \
    if(dbg >= 4)                    \
        printk(KERN_ALERT "DBG:" "%s():" "%d: " fmt, __FUNCTION__, __LINE__, ## args);      \
} while (0)

#define LED_INFO(fmt, args...)  do{ \
    if(dbg >= 2)                    \
        printk(KERN_ALERT "INFO:" "%s():" "%d: " fmt, __FUNCTION__, __LINE__, ## args);     \
}while (0)

#define LED_WARN(fmt, args...)  do{ \
    if(dbg >= 1)                    \
        printk(KERN_ALERT "WARN:" "%s():" "%d: " fmt, __FUNCTION__, __LINE__, ## args);     \
}while (0)

#define LED_ERR(fmt, args...)  do{  \
        printk(KERN_ALERT "ERR:" "%s():" "%d: " fmt, __FUNCTION__, __LINE__, ## args);     \
}while (0)

#define LED_ANY(fmt, args...)  do{  \
        printk(KERN_ALERT "ANY:" "%s():" "%d: " fmt, __FUNCTION__, __LINE__, ## args);     \
}while (0)


#endif