



ifneq  ($(KERNELRELEASE),)
obj-m:=$(OBJ_NAME).o
$(info "##OBJ_NAME: $(obj-m)##")
else
$(info "##Entry $(CURDIR)##")
KERDIR=/lib/modules/`uname -r`/build
PWD:=$(shell pwd)
all:
	make -C $(KERDIR) M=$(PWD) modules OBJ_NAME=$(notdir $(CURDIR))
clean:
	rm -f *.ko *.o *.symvers *.cmd *.cmd.o modules.* *.mod.c  .*.cmd *.mod
endif

