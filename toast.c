#include <linux/init.h>
#include <linux/module.h>

static int __init toast_init(void) 
{
	printk("Hello World");
	return 0;
}

static void __exit toast_exit(void)
{
	printk("Goodbye. Module unloaded");
}

module_init(toast_init);
moudle_exit(toast_exit);

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Wir3dToast");