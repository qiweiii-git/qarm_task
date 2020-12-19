//*****************************************************************************
//    # #              Name   : LedRun.c
//  #     #            Date   : Dec. 19, 2020
// #    #  #  #     #  Author : Qiwei Wu
//  #     #  # #  # #  Version: 1.0
//    # #  #    #   #
// The LED Runner.
//*****************************************************************************

// include
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void delay(volatile int delayCnt)
{
    while(delayCnt)
    {
        delayCnt--;
    }
}

// main
int main(int argc, char **argv)
{
   int fd;
   int ledIndex;

   fd = open("/dev/leds", 0);
   if(fd < 0)
   {
      printf("could not open /dev/leds\n");
      return 0;
   }
   printf("opened /dev/leds\n");

   ledIndex = 0;

   while (1)
   {
      delay(30000000);
      ioctl(fd, ledIndex, 1);
      //printf("opened led[%d]\n", ledIndex);

      delay(30000000);
      ioctl(fd, ledIndex, 0);
      //printf("closed led[%d]\n", ledIndex);
   }
}
