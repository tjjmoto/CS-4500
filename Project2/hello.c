#include <linux /module . h>
#include <linux / kernel . h>

int init module ( void ) 
{
	printk (KERN_INFO "Hello world !\ n" ) ;
	return 0;
}

void cleanup module ( void )
{
	printk (KERN_INFO "Goodbye world !\ n" ) ;
}

module_init ( init_module ) ;
module_exit ( cleanup_module ) ;

MODULE_LICENSE( ”GPL” ) ;
