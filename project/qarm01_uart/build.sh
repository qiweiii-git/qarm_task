#*****************************************************************************
#    # #              Name   : build.sh
#  #     #            Date   : Nov. 15, 2020
# #    #  #  #     #  Author : Qiwei Wu
#  #     #  # #  # #  Version: 1.0
#    # #  #    #   #
# build.sh.
#*****************************************************************************
#!/bin/bash

cd ../../
rm -rf _build
mkdir _build
cp -r ./* _build
cp ./code/Makefile _build/project/qarm01_uart

cd _build/project/qarm01_uart
make obj=QArm01Uart.o

cd ../../../
cp -f ./_build/project/qarm01_uart/QArmTask.bin ./project/qarm01_uart
rm -rf ./_build
