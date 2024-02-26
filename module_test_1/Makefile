obj-m = module_test_1.o
#KDIR = /usr/src/linux-headers-2.6.32-38-generic
#KDIR = /usr/src/linux-headers-`uname -r`
KDIR = /lib/modules/$(shell uname –r)/build
PWD = $(shell pwd)
all: module
module:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	rm -rf *.ko
	rm -rf *.o
	rm -rf *.symvers *.order *.mod.o