#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>

static int irq = 1;
static int irq_call_count = 0;
static int dev_id;
static struct workqueue_struct *workq = NULL;

void work_function(struct work_struct *work)
{
    printk(KERN_INFO "[workqueue_module] work: { data: %ld }", atomic_long_read(&work->data));
}

DECLARE_WORK(work, work_function);

static irqreturn_t interrupt_handler(int irq, void *dev_id)
{
    irq_call_count++;
    queue_work(workq, &work);
    printk(KERN_INFO "[workqueue_module] irq call count = %d\n", irq_call_count);
    return IRQ_NONE;
}

static int __init workqueue_module_init(void)
{
    int ret = request_irq(irq, interrupt_handler, IRQF_SHARED, "interrupt_handler", &dev_id);

    if (ret)
    {
        printk(KERN_ERR "[workqueue_module] error while handle irq");
        return -1;
    }

    workq = create_workqueue("workqueue");

    if (workq == NULL)
    {
        printk(KERN_ERR "[workqueue_module] error while create workqueue");
        return -1;
    }

    printk(KERN_INFO "[workqueue_module] success load");
    return 0;
}

static void __exit workqueue_module_exit(void)
{
    flush_workqueue(workq);
    destroy_workqueue(workq);
    free_irq(irq, &dev_id);
    printk(KERN_INFO "[workqueue_module] unload module");
}

module_init(workqueue_module_init);
module_exit(workqueue_module_exit);
