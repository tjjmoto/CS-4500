#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>

int other_init_module(int pid) {
    struct task_struct *task;
	
	// Setting the current task to the task struct
	task = current; 

	/* Checks to see if the process pid is the process that is input then prints out the details
	 that pertain to the specific task PID that was sent into the module.*/
	if(task->pid != pid)
	{
		printk(KERN_INFO "Child Process Name: %s\n", task->comm);
		printk(KERN_INFO "Child Process ID: %d\n", task->pid);
		printk(KERN_INFO "Child Process State: ");
		
		// Prints the state of the child process based on the state ID sent to the machine.
		if (task->state == -1) {
		    printk("TASK_UNRUNNABLE\n");
		} else if (task->state == 0) {
		    printk("TASK_RUNNING\n");
		} else {
		    printk("TASK_STOPPED\n");
		}
		
		if(task!=&init_task)
		{
			task=task->parent;
		}
		
		// Prints every remaining parent process that is running unit init
		for (task=current; task!=&init_task; task=task->parent) {
		    printk(KERN_INFO "Parent Process Name: %s\n", task->comm);
		    printk(KERN_INFO "Parent Process ID: %d\n", task->pid);
		}
		
	}
    return 0;
}

void other_cleanup_module(void) {
    printk(KERN_INFO "Print Other Clean Up\n");
}

module_init(other_init_module);
module_exit(other_cleanup_module);
