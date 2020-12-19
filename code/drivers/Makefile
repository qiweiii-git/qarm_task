KERN_DIR = ../../../.depend/qarm_base/linux-2.6.22.6

all:
	make -C $(KERN_DIR) M=`pwd` modules 

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order
	rm -rf Module.symvers

obj-m	+= ./led/LedDriver.o
