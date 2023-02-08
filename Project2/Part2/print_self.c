#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

int self_init_module(void) {
    struct task_struct *task;
    char childState[25];

    if (current->state == -1) {
        printk("TASK_UNRUNNABLE\n");
        childState = "TASK_UNRUNNABLE";
    } else if (current->state == 0) {
        printk("TASK_RUNNING\n");
        childState = "TASK_RUNNING";
    } else {
        printk("TASK_STOPPED\n");
        childState = "TASK_STOPPED";
    }

    printk(KERN_INFO "Child Process Name: %s\n", current->comm);
    printk(KERN_INFO "Child Process ID: %d\n", current->pid);
    printk(KERN_INFO "Child Process State: %s\n", childState);

    for (task=current; task!=&init_task; task=task->parent) {
        printk(KERN_INFO "Parent Process Name: %s\n", task->comm);
        printk(KERN_INFO "Parent Process ID: %d\n", task->pid);
    }

    return 0;
}

void self_cleanup_module(void) {
    printk(KERN_INFO "Print Self Clean Up\n");
}

module_init(self_init_module);
module_exit(self_cleanup_module);