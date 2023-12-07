


ifneq  ($(KERNELRELEASE),)
$(info "Building in kernel space: $(KERNELRELEASE)")
obj-m:=led_drv.o
else
$(info "KERDIR############")
#KERDIR := /lib/modules/$(shell uname -r)/build
#KERDIR=/home/yss/kernel_x86/linux-5.15.89
KERDIR=/lib/modules/`uname -r`/build
PWD:=$(shell pwd)
all:
	make -C $(KERDIR) M=$(PWD) modules
clean:
	rm -f *.ko *.o *.symvers *.cmd *.cmd.o modules.* *.mod.c  .*.cmd *.mod
endif

