#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

static int __init dynctl_init(void)
{
	pr_debug("dev" "hey dbydbg man!\n");

	return 0;
}

static void __exit dyndbg_stop(void)
{

	pr_debug("dev" "dbndbg \n");

}

module_init(dynctl_init);
module_exit(dyndbg_stop);
