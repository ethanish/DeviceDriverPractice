#include <linux/module.h>
#include <linux/platform_device.h>

#define DRIVER_NAME "my_platform_driver"

static int my_platform_probe(struct platform_device *pdev) {
    pr_info("Probe called\n");
    // When platform device is detected.
    return 0;
}

static int my_platform_remove(struct platform_device *pdev) {
    pr_info("Remove called\n");
    // When platform device is removed.
    return 0;
}

static struct platform_driver my_platform_driver = {
    .probe = my_platform_probe,
    .remove = my_platform_remove,
    .driver = {
        .name = DRIVER_NAME,
        .owner = THIS_MODULE,
    },
};

static int __init my_platform_init(void) {
    int ret;
    ret = platform_driver_register(&my_platform_driver);
    if (ret)
        pr_err("Failed to register platform driver\n");
    return ret;
}

static void __exit my_platform_exit(void) {
    platform_driver_unregister(&my_platform_driver);
}

module_init(my_platform_init);
module_exit(my_platform_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ethanish");
MODULE_DESCRIPTION("A simple example platform driver");
MODULE_VERSION("0.1");
