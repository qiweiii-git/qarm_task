//*****************************************************************************
//    # #              Name   : LedDriver.c
//  #     #            Date   : Dec. 14, 2020
// #    #  #  #     #  Author : Qiwei Wu
//  #     #  # #  # #  Version: 1.0
//    # #  #    #   #
// The LED driver.
//*****************************************************************************

// include
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>
#include <LedCtrl.h>

// define
#define LED_MAJOR 231
#define DEVICE_NAME "leds"

// variables
volatile unsigned long *m_LedCon = NULL;
volatile unsigned long *m_LedDat = NULL;

// LED control
// Initialization of LED control
int LedCtrlInit(int index)
{
   GPX_CON_t ledGpxCon;

   ledGpxCon.data32 = *m_LedCon;

   switch (index)
   {
      case 0:
         ledGpxCon.DATA32_t.GPX4 = GPXCON_OUTPUT;
         break;

      case 1:
         ledGpxCon.DATA32_t.GPX5 = GPXCON_OUTPUT;
         break;

      case 2:
         ledGpxCon.DATA32_t.GPX6 = GPXCON_OUTPUT;
         break;

      default:
         break;
   }

   *m_LedCon = ledGpxCon.data32;

   return 0;
}

// Control set of LED
int LedCtrlSet(int index, int on)
{
   int ledCtrlBit;
   GPX_DAT_t ledGpxDat;

   ledGpxDat.data32 = *m_LedDat;

   if(on == 0)
   {
      ledCtrlBit = LEDCTRL_OFF;
   }
   else
   {
      ledCtrlBit = LEDCTRL_ON;
   }

   switch (index)
   {
      case 0:
         ledGpxDat.DATA32_t.GPX4 = ledCtrlBit;
         break;

      case 1:
         ledGpxDat.DATA32_t.GPX5 = ledCtrlBit;
         break;

      case 2:
         ledGpxDat.DATA32_t.GPX6 = ledCtrlBit;
         break;

      default:
         break;
   }

   *m_LedDat = ledGpxDat.data32;

   return 0;
}


// called from open(/dev/leds)
static int LedDriverOpen(struct inode *inode, struct file *file)
{
   int i;
   for(i = 0; i < 3; i++)
   {
      LedCtrlInit(i);
   }
}

// called from ioctl(/dev/leds)
static int LedDriverIoctl(struct inode *inode, struct file *file, int index, int ledOn)
{
   LedCtrlSet(index, ledOn);
}

// file operations
static struct file_operations ledDriverFops =
{
   .owner = THIS_MODULE,
   .open  = LedDriverOpen,
   .ioctl = LedDriverIoctl,
};

// called from 'insmod LedDriver.ko'
static int __init LedDriverInit(void)
{
   int ret;
   /* 注册字符设备驱动程序
    * 参数为：主设备号，设备名字，file_operations结构
    * 主设备号可以为0，表示由内核自动分配主设备号
    */
   ret = register_chrdev(LED_MAJOR, DEVICE_NAME, &ledDriverFops);
   if(ret < 0)
   {
      printk(DEVICE_NAME "Can not register major number\n");
      return ret;
   }

   m_LedCon = (volatile unsigned long *)ioremap(0x56000050, 16);
	m_LedDat = m_LedCon + 1;

   printk(DEVICE_NAME " initialized\n");
   return 0;
}

// called from 'rmmod LedDriver.ko'
static void __exit LedDriverExit(void)
{
   // 卸载驱动程序
   unregister_chrdev(LED_MAJOR, DEVICE_NAME);

   iounmap(m_LedCon);
}

module_init(LedDriverInit);
module_exit(LedDriverExit);
