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
projectName='qarm05_rootfs'
buildUboot='0'
buildKernel='0'
buildYaffs='0'
buildRootfs='1'
buildSw='0'

if [ ! $1 -eq '' ]; then
   projectName=$1
   buildUboot=$2
   buildKernel=$3
   buildSw=$3
fi

depends=('qarm_base' 'git clone https://gitee.com/qiweiii-gitee/qarm_base.git')

patchs=( 'qarm_base/u-boot-1.1.6' 'u-boot-1.1.6_jz2440.patch' 
         'qarm_base/linux-2.6.22.6' 'linux-2.6.22.6_jz2440_v2v3.patch' 
         'qarm_base/yaffs' 'yaffs_util_mkyaffsimage.patch' )

#*****************************************************************************
# Get depends
#*****************************************************************************
workDir=$(pwd)

if [ ! -d .depend ]; then
   mkdir .depend
   echo "Info: .depend created"
fi

dependCnt=${#depends[*]}

if (( $dependCnt > 0 )); then
   cd .depend
   for((i=0; i<dependCnt; i=i+2))
   do
      if [ ! -d ${depends[i]} ]; then
         echo "Getting ${depends[i]}"
         ${depends[i+1]}
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
      git add ./ --all
      git reset --hard HEAD
      echo "Applying patch ${patchs[i+1]}"
      patch -f -p1 < $workDir/code/patchs/${patchs[i+1]}
   done
   sudo chmod 0755 -R ./
   cd $workDir
   echo "Info: All patchs applied"
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
   cp config_ok .config
   make uImage
   cd $workDir
   cp .depend/qarm_base/linux-2.6.22.6/arch/arm/boot/uImage project/$projectName/bin
}

#*****************************************************************************
# Build yaffs
#*****************************************************************************
BuildYaffs() {
   cd .depend/qarm_base/yaffs_patched/yaffs2/utils
   make
   cd $workDir/.depend/qarm_base/
   rm -rf fs_mini
   sudo tar xjf fs_mini.tar.bz2
   yaffs_patched/yaffs2/utils/mkyaffs2image fs_mini rootfs_yaffs2.yaffs2
   cd $workDir
   cp .depend/qarm_base/rootfs_yaffs2.yaffs2 project/$projectName/bin
}

#*****************************************************************************
# Build rootfs
#*****************************************************************************
BuildRootfs() {
   cd .depend/qarm_base/
   rm -rf busybox-1.7.0_patched
   sudo tar xjf busybox-1.7.0_patched.tar.bz2
   cd busybox-1.7.0_patched
   make
   make CONFIG_PREFIX=$workDir/.build/code/rootfs install
   cp /work/tools/gcc-3.4.5-glibc-2.3.6/arm-linux/lib/*.so* $workDir/.build/code/rootfs/lib -d
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
