#include <linux/proc_fs.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/seq_file.h>

#include "./../logs.h"

static struct proc_dir_entry *proc_entry = NULL;

static int dbg_read(struct seq_file *m, void *v)
{
    seq_printf(m, "dbg = %d\n", dbg); 
    
    return 0;
}

static int dbg_open(struct inode *inode, struct file *file)
{
    return single_open(file, dbg_read, NULL);
}

static ssize_t dbg_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
    return count;
}

struct file_operations fops_dbg = {
    .owner = THIS_MODULE,
    .open = dbg_open,          //read接口
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
    .write = dbg_write,     //write接口
};

void create_procfs(void *priv)
{
    proc_entry = proc_mkdir("rpi_led", NULL);
    proc_create_data("dbg", S_IRUGO | S_IWUGO | S_IXUGO, proc_entry, &fops_dbg, priv);
}

void cleanup_procfs(void)
{
    remove_proc_entry("dbg", NULL);
    proc_remove(proc_entry);
}
