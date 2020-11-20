#*****************************************************************************
#    # #              Name   : build.sh
#  #     #            Date   : Nov. 14, 2020
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
cp ./code/Makefile _build/project/qarm00_led

cd _build/project/qarm00_led
make objs=QArm00Led.o ../../code/applications/LedCtrl.o

cd ../../../
cp -f ./_build/project/qarm00_led/QArmTask.bin ./project/qarm00_led
rm -rf ./_build
