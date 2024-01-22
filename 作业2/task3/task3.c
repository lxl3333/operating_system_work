#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");

// 定义一个结构体指针而已
struct task_struct *p;

static int __init process_info_init(void)
{
    // for_each_process是一个宏，他会依此将进程给遍历，如果状态为0,那么就是当前正在运行的进程
    for_each_process(p)
    {
        // 没有用  if (p->state == 0)
        {
            printk("1)name:%s  2)pid:%d  3)state:%ld\n", p->comm, p->pid, p->state);
        }
    }
}

// 没有用
static void __exit process_info_exit(void)
{
    printk("process_info_exit\n");
}

// 内核模块加载的时候会调用cpu_loadavg_init函数
module_init(process_info_init);

// 内核模块退出的时候会调用cpu_loadave_exit函数
module_exit(process_info_exit);