#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

int self_init_module(void) {
    struct task_struct *task;

    printk(KERN_INFO "Child Process name: %s\n", current->comm);
}