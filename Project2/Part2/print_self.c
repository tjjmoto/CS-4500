#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

int self_init_module(void) {
    struct task_struct *task;

    /* Prints all child and parent processes that result from print_self until init*/
    printk(KERN_INFO "Child Process Name: %s\n", current->comm);
    printk(KERN_INFO "Child Process ID: %d\n", current->pid);
    printk(KERN_INFO "Child Process State: ");

    // Prints the state of the child process based on the state ID sent to the machine.
    if (current->state == -1) {
        printk("TASK_UNRUNNABLE\n");
    } else if (current->state == 0) {
        printk("TASK_RUNNING\n");
    } else {
        printk("TASK_STOPPED\n");
    }

    // Prints every remaining parent process that is running unit init
    for (task = current; task != &init_task; task = task->parent) {
        printk(KERN_INFO "Parent Process Name: %s\n", task->comm);
        printk(KERN_INFO "Parent Process ID: %d\n", task->pid);
        printk(KERN_INFO "Parent Process State: ");

        // Prints the state of the parent process based on the state ID sent to the machine.
        if (task->state == -1) {
            printk("TASK_UNRUNNABLE\n");
        } else if (task->state == 0) {
            printk("TASK_RUNNING\n");
        } else {
            printk("TASK_STOPPED\n");
        }
    }

    return 0;
}

void self_cleanup_module(void) {
    printk(KERN_INFO "Print Self Clean Up\n");
}

module_init(self_init_module);
module_exit(self_cleanup_module);