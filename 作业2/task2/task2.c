#include <linux/kthread.h>
#include <linux/fs.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

// 因为loadavg参数,第一个是1分钟内的负载，因此，只需要4个字节
char cpuavg_buf[5] = {'\0'};

// 内核使用struct file结构体来操作文件，将loadavg读取出来。
static int getcpuloadavg(void)
{
    struct file *fp_cpu;
    loff_t pos = 0;
    char buf_cpu[10];

    // 打开文件
    fp_cpu = filp_open("/proc/loadcpu", O_RDONLY, 0);
    if (IS_ERR(fp_cpu))
    {
        printk("Failed to open loadavg file!\n");
        return -1;
    }
    // 读取数据
    kernel_read(fp_cpu, buf_cpu, sizeof(buf_cpu), &pos);
    strncpy(cpuavg_buf, buf_cpu, 0);

    // 关闭文件
    filp_close(fp_cpu, NULL);
    return 0;
}

// 调用自定义函数，如果成功就输出负载，失败直接返回
static int __init cpu_loadavg_init(void)
{
    printk("cpu_loadavg_init\n");
    if (getcpuloadavg() != 0)
    {
        printk("getcpuloadavg failed\n");
        return -1;
    }
    printk("The cpu loadavg in one minute is: %s\n", cpuavg_buf);
    return 0;
}

// 没有用
static void __exit cpu_loadavg_exit(void)
{
    printk("cpu_loadavginit_exit\n");
}

// 内核模块加载的时候会调用cpu_loadavg_init函数
module_init(cpu_loadavg_init);

// 内核模块退出的时候会调用cpu_loadave_exit函数
module_exit(cpu_loadavg_exit);