#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/notifier.h>

BLOCKING_NOTIFIER_HEAD(learning_notifier_list);

static struct blocking_notifier_head nh;
static struct notifier_block nb;

static struct notifier_block new;

int notify_sample_cb(struct notifier_block *, unsigned long val, void *data);

static int __init notifier_learning_module_init(void)
{
	int ret;

	new.notifier_call = notify_sample_cb;
	new.next = 0;
	new.priority = 1;

	ret = blocking_notifier_chain_register(&learning_notifier_list, &new);

	printk("registering.. %d\n", ret);
	if (ret) {
		printk("failed to register notifier chains\n");
		return -1;
	}


	blocking_notifier_call_chain(&learning_notifier_list, 1, 0);

	return 0;
}

int notify_sample_cb(struct notifier_block *nb, unsigned long val, void *data)
{
	printk("called in the sample\n");
	return NOTIFY_OK;
}

static void __exit notifier_exit(void)
{
	blocking_notifier_chain_unregister(&learning_notifier_list, &new);
}

MODULE_LICENSE("GPL");
module_init(notifier_learning_module_init);
module_exit(notifier_exit);
