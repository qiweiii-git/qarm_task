#*****************************************************************************
#    # #              Name   : build.sh
#  #     #            Date   : Dec. 05, 2020
# #    #  #  #     #  Author : Qiwei Wu
#  #     #  # #  # #  Version: 1.0
#    # #  #    #   #
# build.sh.
#*****************************************************************************
#!/bin/bash

#*****************************************************************************
# Build setting
#*****************************************************************************
projectName='qarm06_ledDrv'
buildUboot='0'
buildKernel='1'
buildYaffs='0'
buildRootfs='1'
buildSw='0'
buildDriver='1'

if [ ! $1 -eq '' ]; then
   projectName=$1
   buildUboot=$2
   buildKernel=$3
   buildSw=$4
fi

depends=('qarm_base' 'git clone https://gitee.com/qiweiii-gitee/qarm_base.git')

patchs=( 'qarm_base/u-boot-1.1.6' 'u-boot-1.1.6_jz2440.patch' 
         'qarm_base/linux-2.6.22.6' 'linux-2.6.22.6_jz2440_v2v3.patch' 
         'qarm_base/linux-2.6.22.6' 'linux-2.6.22.6_drivers.patch' 
         'qarm_base/yaffs' 'yaffs_util_mkyaffsimage.patch' )

#*****************************************************************************
# Get depends
#*****************************************************************************
workDir=$(pwd)

if [ ! -d .depend ]; then
   mkdir .depend
   echo "Info: .depend created"

   dependCnt=${#depends[*]}

   if (( $dependCnt > 0 )); then
      cd .depend
      for((i=0; i<dependCnt; i=i+2))
      do
         if [ ! -d ${depends[i]} ]; then
            echo "Getting ${depends[i]}"
            ${depends[i+1]}

            if [[ ${depends[i]} -eq 'qarm_base' ]]; then
               cd ${depends[i]}
               sudo tar xjf busybox-1.7.0_patched.tar.bz2
               sudo tar xjf fs_mini.tar.bz2
               sudo tar xjf linux-2.6.22.6.tar.bz2
            fi
         fi
      done
      sudo chmod 0755 -R ./
      cd $workDir
      echo "Info: All depends got"
   fi

#*****************************************************************************
# Apply patchs
#*****************************************************************************
   patchsCnt=${#patchs[*]}

   if (( $patchsCnt > 0 )); then
      cd .depend
      dependDir=$(pwd)
      for((i=0; i<patchsCnt; i=i+2))
      do
         cd $dependDir
         cd ${patchs[i]}
         #git add ./ --all
         #sudo git reset --hard HEAD
         echo "Applying patch ${patchs[i+1]}"
         sudo patch -p1 < $workDir/code/patchs/${patchs[i+1]}
      done
      sudo chmod 0755 -R ./
      cd $workDir
      echo "Info: All patchs applied"
   fi
fi

#*****************************************************************************
# Copy files
#*****************************************************************************
MkdirBuild() {
   rm -rf .build
   mkdir .build
   cp -ra ./* .build
}

#*****************************************************************************
# Build u-boot
#*****************************************************************************
BuildUboot() {
   cd .depend/qarm_base/u-boot-1.1.6
   make 100ask24x0_config
   make all
   cd $workDir
   cp .depend/qarm_base/u-boot-1.1.6/u-boot.bin project/$projectName/bin
}

#*****************************************************************************
# Build kernel
#*****************************************************************************
BuildKernel() {
   cd .depend/qarm_base/linux-2.6.22.6
   sudo cp config_ok .config
   make uImage
   cd $workDir
   cp .depend/qarm_base/linux-2.6.22.6/arch/arm/boot/uImage project/$projectName/bin
}

#*****************************************************************************
# Build drivers
#*****************************************************************************
BuildDriver() {
   cd .depend/qarm_base/linux-2.6.22.6
   cp config_ok .config
   #cp $workDir/code/drivers/led/*.c drivers/char/
   make modules
   #cp drivers/char/LedDriver.ko $workDir/project/$projectName/bin
   cd $workDir/.build/code/drivers/
   make
   arm-linux-gcc -o ./led/LedTest ./led/LedTest.c
   arm-linux-gcc -o ./led/LedRun ./led/LedRun.c
   cp led/LedDriver.ko $workDir/project/$projectName/bin
   cp led/LedTest $workDir/project/$projectName/bin
   cp led/LedRun $workDir/project/$projectName/bin
   cd $workDir
}

#*****************************************************************************
# Build yaffs
#*****************************************************************************
BuildYaffs() {
   cd .depend/qarm_base/yaffs_patched/yaffs2/utils
   make
   cd $workDir/.depend/qarm_base/
   yaffs_patched/yaffs2/utils/mkyaffs2image fs_mini rootfs_yaffs2.yaffs2
   cd $workDir
   cp .depend/qarm_base/rootfs_yaffs2.yaffs2 project/$projectName/bin
}

#*****************************************************************************
# Build rootfs
#*****************************************************************************
BuildRootfs() {
   cd .depend/qarm_base/
   cd busybox-1.7.0_patched
   make
   make CONFIG_PREFIX=$workDir/.build/code/rootfs install
   cp /work/tools/gcc-3.4.5-glibc-2.3.6/arm-linux/lib/*.so* $workDir/.build/code/rootfs/lib -d
   cp $workDir/.build/project/$projectName/bin/*.ko* $workDir/.build/code/rootfs/lib/modules -d
   rm -f $workDir/.build/project/$projectName/bin/*.*
   rm -f $workDir/.build/project/$projectName/bin/uImage
   cp $workDir/.build/project/$projectName/bin/* $workDir/.build/code/rootfs/usr/bin -d
   cd $workDir/.depend/qarm_base/yaffs_patched/yaffs2/utils
   make
   cd $workDir/.depend/qarm_base/yaffs_patched/yaffs2/utils
   make
   sudo chmod +x -R $workDir/.build/code/rootfs
   cd $workDir/.build/code/rootfs/dev/
   sudo chmod +x -R mknod.sh
   ./mknod.sh
   cd $workDir/.build/code/
   $workDir/.depend/qarm_base/yaffs_patched/yaffs2/utils/mkyaffs2image rootfs rootfs_yaffs2.yaffs2
   cd $workDir
   cp .build/code/rootfs_yaffs2.yaffs2 project/$projectName/bin
}

#*****************************************************************************
# Build sw
#*****************************************************************************
BuildSw() {
   cp ./code/Makefile .build/project/$projectName
   cd .build/project/$projectName
   make obj=$projectName
   cd $workDir
   cp -f .build/project/$projectName/QArmTask.bin ./project/$projectName/bin
}

#*****************************************************************************
# Main
#*****************************************************************************
if [[ $buildUboot -eq 1 ]]; then
   MkdirBuild
   BuildUboot
fi

if [[ $buildKernel -eq 1 ]]; then
   MkdirBuild
   BuildKernel
fi

if [[ $buildDriver -eq 1 ]]; then
   MkdirBuild
   BuildDriver
fi

if [[ $buildYaffs -eq 1 ]]; then
   MkdirBuild
   BuildYaffs
fi

if [[ $buildRootfs -eq 1 ]]; then
   MkdirBuild
   BuildRootfs
fi

if [[ $buildSw -eq 1 ]]; then
   MkdirBuild
   BuildSw
fi

echo "Info: All builds got"
