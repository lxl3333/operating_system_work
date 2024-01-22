#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

static struct task_struct *mytask = NULL;

static int print(void *data)
{
    while (!kthread_should_stop())
    {
        printk("New kthread is running.\n")
            msleep(2000);
    }
    return 0;
}

static int __init kthread_init(void)
{
    printk("module init\n");
    mytask = kthread_run(print, NULL, "print");
    return 0;
}

static void __exit kthread_exit(void)
{
    printk("module exit\n");
    if (mytask)
        kthread_stop(mytask);
}

module_init(kthread_init);
module_exit(kthread_exit);
