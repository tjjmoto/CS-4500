#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

int other_init_module(task_struct *task) {
    struct task_struct *task;

    task = pid_task(find_vpid(pid), PIDTYPE_PID);

    printk(KERN_INFO "Child Process Name: %s\n", task->comm);
    printk(KERN_INFO "Child Process ID: %d\n", task->pid);
    printk(KERN_INFO "Child Process State: ");

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
