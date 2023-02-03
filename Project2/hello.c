#include <linux/module.h>
#include <linux/kernel.h>

int init_module2(void) 
{
	printk(KERN_INFO "Hello world !\n");
	return 0;
}

void cleanup_module2(void)
{
	printk(KERN_INFO "Goodbye world !\n");
}

module_init(init_module2);
module_exit(cleanup_module2);

MODULE_LICENSE("GPL");
