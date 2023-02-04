#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

int self_init_module(void) {
    struct task_struct *task;

    printk(KERN_INFO "Child Process Name: %s\n", current->comm);
    printk(KERN_INFO "Child Process ID: %d\n", current->pid);
    printk(KERN_INFO "Child Process State: ");
    switch(current->state) {
        case -1:
            printk("can't run\n");
            break;
        case 0:
            printk("can run\n");
            break;
        default: 
            printk("stopped\n");
            break;
    }
}