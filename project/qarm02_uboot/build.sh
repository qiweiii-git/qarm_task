#*****************************************************************************
#    # #              Name   : build.sh
#  #     #            Date   : Nov. 20, 2020
# #    #  #  #     #  Author : Qiwei Wu
#  #     #  # #  # #  Version: 1.0
#    # #  #    #   #
# build.sh.
#*****************************************************************************
#!/bin/bash

#*****************************************************************************
# depends
#*****************************************************************************
depends=('qarm_base' 'git clone https://github.com/qiweiii-git/qarm_base.git')

#*****************************************************************************
# Get depends
#*****************************************************************************
cd ../../
DependFileDir=.depend
if [ ! -d $DependFileDir ]; then
   mkdir $DependFileDir
   echo "Info: $DependFileDir created"
fi

dependLen=${#depends[*]}

if (( $dependLen > 0 )); then
   cd $DependFileDir
   for((i=0; i<dependLen; i=i+2))
   do
      if [ ! -d ${depends[i]} ]; then
         echo "Getting ${depends[i]}"
         ${depends[i+1]}
      fi
   done
   cd ../
   echo "Info: All depends got"
fi

chmod 0755 -R $DependFileDir

#*****************************************************************************
# Build
#*****************************************************************************
rm -rf _build
mkdir _build
cp -ra ./* _build
cp -ra ./$DependFileDir _build

cd _build/$DependFileDir/qarm_base/u-boot-1.1.6
patch -p1 < ../../../project/qarm02_uboot/u-boot-1.1.6_jz2440.patch
make 100ask24x0_config
make all

cp u-boot.bin ../../../../project/qarm02_uboot/
cd ../../../../
rm -rf ./_build
