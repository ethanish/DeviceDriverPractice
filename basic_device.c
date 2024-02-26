/* basic_device.c */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/module.h>
#define IOM_MYDEVICE_MAJOR_NUM 0
#define DEV_NAME "/dev/mydevice"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ISH");
int mydevice_init(void);
void mydevice_exit(void);
module_init(mydevice_init);
module_exit(mydevice_exit);
int mydevice_open (struct inode *, struct file *);
int mydevice_release (struct inode *, struct file *);
ssize_t mydevice_read (struct file *, char __user *, size_t, loff_t *);
ssize_t mydevice_write (struct file *, const char __user *, size_t, loff_t *);
int mydevice_ioctl (struct inode *, struct file *, unsigned int, unsigned long);
struct file_operations mydevice_fops = {
.owner = THIS_MODULE,
.open = mydevice_open,
.release = mydevice_release,
.read = mydevice_read,
.write = mydevice_write,
.ioctl = mydevice_ioctl,
};
int mydevice_open (struct inode *inode, struct file *filp)
{
return 0;
}
int device_release (struct inode *inode, struct file *filp)
{
return 0;
}
ssize_t device_read (struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
return 0;
}

ssize_t device_write (struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
return 0;
}
int device_ioctl (struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
return 0;
}
int __init mydevice_init(void)
{
int major_num;
major_num = register_chrdev(IOM_MYDEVICE_MAJOR_NUM , DEV_NAME, &mydevice_fops);
if ( major_num < 0 ) {
printk(KERN_WARNING"%s: can't get or assign major number %d\n", DEV_NAME,
IOM_MYDEVICE_MAJOR_NUM );
return major_num;
}
printk("Success to load the device %s. Major number is %d\n", DEV_NAME,
IOM_MYDEVICE_MAJOR_NUM );
return 0;
}
void __exit mydevice_exit(void)
{
unregister_chrdev(IOM_MYDEVICE_MAJOR_NUM , DEV_NAME);
printk("Success to unload the device %s...\n", DEV_NAME);
}
