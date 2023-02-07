#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <string.h>

int other_init_module(task_struct *task) {
    struct task_struct *task;
    char childState[25];

    if (task->state == -1) {
        printk("TASK_UNRUNNABLE\n");
        childState = "TASK_UNRUNNABLE";
    } else if (task->state == 0) {
        printk("TASK_RUNNING\n");
        childState = "TASK_RUNNING";
    } else {
        printk("TASK_STOPPED\n");
        childState = "TASK_STOPPED";
    }

    printk(KERN_INFO "Child Process Name: %s\n", task->comm);
    printk(KERN_INFO "Child Process ID: %d\n", task->pid);
    printk(KERN_INFO "Child Process State: %s\n", childState);
    
    if(task!=&init_task)
	{
		task=task->parent;
	}

    for (task=current; task!=&init_task; task=task->parent) {
        printk(KERN_INFO "Parent Process Name: %s\n", task->comm);
        printk(KERN_INFO "Parent Process ID: %d\n", task->pid);
    }

    return 0;
}

void other_cleanup_module(void) {
    printk(KERN_INFO "Print Other Clean Up\n");
}

module_init(other_init_module);
module_exit(other_cleanup_module);
