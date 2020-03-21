#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init_task.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Stepanov");
MODULE_DESCRIPTION("BMSTU operating sysytems lab_03_01");

static int __init alex_module_init(void)
{
    printk(KERN_INFO "Module loaded\n");

    struct task_struct *task = &init_task;

    do
    {
        printk(KERN_INFO "%s -- %d, parent: %s -- %d\n",
            task->comm, task->pid, task->parent->comm, task->parent->pid);
    }
    while ((task = next_task(task)) != &init_task);

 
    printk(KERN_INFO "current: %s -- %d, parent: %s -- %d\n",
        current->comm, current->pid, current->parent->comm, current->parent->pid);

    return 0;
}

static void __exit alex_module_exit(void)
{
    printk(KERN_INFO "Module exited\n");
}

module_init(alex_module_init);
module_exit(alex_module_exit);
