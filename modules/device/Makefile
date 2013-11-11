ifneq ($(KERNELRELEASE),)
obj-m:=char_dev.o
else
KD ?=/lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
default:
	$(MAKE) -C $(KD) M=$(PWD) modules
clean:
	rm $(obj-m) *.o *.ko Module* module* *.mod.c
endif
