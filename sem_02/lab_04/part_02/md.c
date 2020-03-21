#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/vmalloc.h>

#define MAX_COOKIE_LENGTH PAGE_SIZE

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Liran B.H");

static struct proc_dir_entry *proc_entry;
static char *cookie_pot;
static int cookie_index;
static int next_fortune;

static ssize_t fortune_write(struct file *file, const char __user *buff, size_t len, loff_t *data)
{
    int space_available = (MAX_COOKIE_LENGTH-cookie_index)+1;

    if (len > space_available)
    {
        printk(KERN_INFO "fortune: cookie pot is full!\n");
        return -ENOSPC;
    }

    /*if (*/copy_from_user(&cookie_pot[cookie_index], buff, len);/*)*/
    /*{
        return -EFAULT;
    }*/

    cookie_index += len;
    cookie_pot[cookie_index-1] = 0;

    printk(KERN_INFO "fortune: write to file");

    return len;
}

static ssize_t fortune_read(struct file *file, char __user *buff, size_t len, loff_t *data)
{
    if (next_fortune >= cookie_index)
        next_fortune = 0;

    len = copy_to_user(&cookie_pot[next_fortune], buff, len);
    // len = sprintf(page, "%s\n", &cookie_pot[next_fortune]);
    next_fortune += len;

    printk(KERN_INFO "fortune: read from file");

    return len;
}

static struct file_operations ops =
{
    .owner =  THIS_MODULE,
    .read = fortune_read,
    .write = fortune_write,
};

static int md_init(void)
{
    int ret = 0;
    cookie_pot = (char *)vmalloc( MAX_COOKIE_LENGTH );

    if (!cookie_pot)
    {
        ret = -ENOMEM;
    }
    else
    {
        memset( cookie_pot, 0, MAX_COOKIE_LENGTH );
        proc_entry = proc_create( "fortune", 0644, NULL, &ops );

        if (proc_entry == NULL)
        {
            ret = -ENOMEM;
            vfree(cookie_pot);
            printk(KERN_INFO "fortune: Couldn't create proc entry\n");
        }
        else
        {
            cookie_index = 0;
            next_fortune = 0;
            printk(KERN_INFO "fortune: Module loaded.\n");
        }
    }

    return ret;
}

static void md_exit(void)
{
    remove_proc_entry("fortune", proc_entry);
    vfree(cookie_pot);
    printk(KERN_INFO "fortune: Module unloaded.\n");
}

module_init(md_init);
module_exit(md_exit);
