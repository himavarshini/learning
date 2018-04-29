#include <linux/init.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/list.h>

static int __init task_prints(void)
{
	struct task_struct *task;
	for_each_process(task) {
		printk("name [%s], pid[%d]\n",
			task->comm, task->pid);
	}
	return 0;
}

static void __exit task_stops(void)
{

}

module_init(task_prints);
module_exit(task_stops);
MODULE_LICENSE("GPL");
