#*****************************************************************************
#    # #              Name   : Makefile
#  #     #            Date   : Nov. 14, 2020
# #    #  #  #     #  Author : Qiwei Wu
#  #     #  # #  # #  Version: 1.0
#    # #  #    #   #
# Makefile.
#*****************************************************************************

objs =../../code/applications/LedCtrl.o
objs +=../../code/applications/UartCtrl.o
objs += $(obj)

#CFLAGS = -Werror -std=c99
CFLAGS = -Werror
CINC = -I../../code -I../../code/applications -I../../code/utils

deps := $(patsubst %, %.d, $(objs))
deps := $(wildcard $(deps))

task:$(objs)
	arm-linux-gcc -c -o ../../code/utils/start.o ../../code/utils/start.S
	arm-linux-ld -Ttext 0 ../../code/utils/start.o $^ -o QArmTask.elf
	arm-linux-objcopy -O binary -S QArmTask.elf QArmTask.bin

ifneq ($(deps), )
include $(deps)
endif

%.o:%.c
	arm-linux-gcc $(CFLAGS) $(CINC) -c -o $@ $< -MD -MF $@.d

clean:
	rm *.d QArmTask

distclean:
	rm $(deps)

.PHONY:clean
.PHONY:distclean
