#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "my_device"
#define EXAMPLE_MSG "Hello from the device driver!"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ISH");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.1");

static int major_num;
static int device_open_count = 0;

static int device_open(struct inode *inode, struct file *file) {
    if (device_open_count)
        return -EBUSY;
    device_open_count++;
    try_module_get(THIS_MODULE);
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    device_open_count--;
    module_put(THIS_MODULE);
    return 0;
}

static ssize_t device_read(struct file *file, char *buffer, size_t length, loff_t *offset) {
    int bytes_read = 0;
    if (*offset != 0)
        return 0;
    bytes_read = sprintf(buffer, "%s\n", EXAMPLE_MSG);
    *offset += bytes_read;
    return bytes_read;
}

static struct file_operations fops = {
    .read = device_read,
    .open = device_open,
    .release = device_release,
};

static int __init device_driver_init(void) {
    major_num = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_num < 0) {
        printk(KERN_ALERT "Could not register a major number for %s\n", DEVICE_NAME);
        return major_num;
    } else {
        printk(KERN_INFO "Device driver module %s registered with major number %d\n", DEVICE_NAME, major_num);
        return 0;
    }
}

static void __exit device_driver_exit(void) {
    unregister_chrdev(major_num, DEVICE_NAME);
    printk(KERN_INFO "Device driver module %s unregistered\n", DEVICE_NAME);
}

module_init(device_driver_init);
module_exit(device_driver_exit);
