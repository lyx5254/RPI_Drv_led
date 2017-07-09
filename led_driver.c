#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>

#include "logs.h"
#include "model.h"
#include "procfs/procfs.h"

unsigned int dbg = 0;

module_param(dbg, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

int open_state = 0;         //文件打开状态  

static int rpi_leds_open(struct inode *inode, struct file *filp)  
{
    if(open_state == 0)    
    {
        open_state =  1;    
        LED_INFO("Open file suc!\n");
        return 0;    
    }
    else    
    {
        LED_INFO("The file has opened!\n");
        return -1;    
    }
}

static long rpi_leds_ioctl(struct file*filp, unsigned int cmd, unsigned long arg)  
{  
    switch(cmd)    
    {    
        case 0:    
            LED_INFO("LED OFF!\n");
            break;    
        case 1:    
            LED_INFO("LED ON!\n");
            break;    
  
        default:    
            return -EINVAL;    
    }    
  
    return 0;  
}  

static int rpi_leds_release(struct inode *inode, struct file *filp)  
{
    if(open_state == 1)    
    {
        open_state =  0;    
        LED_INFO("close file suc!\n");
        return 0;    
    }
    else    
    {
        LED_INFO("The file has closed!\n");
        return -1;    
    }
}

static const struct file_operations leds_fops = {  
    .owner = THIS_MODULE,
    .open = rpi_leds_open,
    .unlocked_ioctl = rpi_leds_ioctl,
    .release = rpi_leds_release,
};

static struct miscdevice rpi_led = {  
    .minor =MISC_DYNAMIC_MINOR,  
    .name ="rpi_led",  
    .fops =&leds_fops,  
};  

static int __init rpi_leds_init(void)
{
    int ret;  

    LED_ANY("VERSION: %s DATE: %s TIME: %s\n", VERSION, __DATE__, __TIME__);
    LED_ANY("rpi led init\n");

    //注册混杂设备  
    ret =misc_register(&rpi_led);

    create_procfs(NULL);

    return ret;  
}  

static void __exit rpi_leds_exit(void)
{
    LED_ANY("rpi led exit\n");

    misc_deregister(&rpi_led);

    cleanup_procfs();
}  

module_init(rpi_leds_init);  
module_exit(rpi_leds_exit);  

MODULE_AUTHOR("linyanx for rpi led");  
MODULE_LICENSE("GPL");  