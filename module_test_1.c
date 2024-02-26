/* filename: module_test_1.c */
#include <linux/module.h>
MODULE_LICENSE("GPL");
int init_module(void) /* module_init() */
{
printk("Loading my first device driver...\n");
return 0;
}
void cleanup_module(void) /* module_exit() */
{
printk("Unloading my first device driver..\n");
}
