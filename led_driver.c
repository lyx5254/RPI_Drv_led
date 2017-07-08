#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>

#include "logs.h"
#include "model.h"

int open_state = 0;         //文件打开状态  

static int rpi_leds_open(struct inode *inode, struct file *filp)  
{
    if(open_state == 0)    
    {
        open_state =  1;    
        printk("Open file suc!\n");    
        return 0;    
    }
    else    
    {
        printk("The file has opened!\n");    
        return -1;    
    }
}

static long rpi_leds_ioctl(struct file*filp, unsigned int cmd, unsigned long arg)  
{  
    switch(cmd)    
    {    
        case 0:    
            printk("LED OFF!\n");  
            break;    
        case 1:    
            printk("LED ON!\n");  
            break;    
  
        default:    
            return-EINVAL;    
    }    
  
    return 0;  
}  

static int rpi_leds_release(struct inode *inode, struct file *filp)  
{
    if(open_state == 1)    
    {
        open_state =  0;    
        printk("close file suc!\n");    
        return 0;    
    }
    else    
    {
        printk("The file has closed!\n");    
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
  
    //注册混杂设备  
    ret =misc_register(&rpi_led);  
  
    printk(KERN_ALERT"version: %s\n", VERSION);
    printk(KERN_ALERT "rpi led init\n");
    return ret;  
}  

static void __exit rpi_leds_exit(void)
{
    misc_deregister(&rpi_led);
    printk(KERN_ALERT "rpi led exit\n");
}  

module_init(rpi_leds_init);  
module_exit(rpi_leds_exit);  

MODULE_AUTHOR("linyanx for rpi led");  
MODULE_LICENSE("GPL");  