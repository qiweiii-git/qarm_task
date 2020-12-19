//*****************************************************************************
//    # #              Name   : LedTest.c
//  #     #            Date   : Dec. 18, 2020
// #    #  #  #     #  Author : Qiwei Wu
//  #     #  # #  # #  Version: 1.0
//    # #  #    #   #
// The LED Tester.
//*****************************************************************************

// include
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

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

   ledIndex = strtoul(argv[1], 0, 0);

   if(!strcmp(argv[2], "on"))
   {
      ioctl(fd, ledIndex, 1);
      printf("opened led[%d]\n", ledIndex);
   }
   else if(!strcmp(argv[2], "off"))
   {
      ioctl(fd, ledIndex, 0);
      printf("closed led[%d]\n", ledIndex);
   }
   else
   {
      printf("Invalid argv\n");
      return 0;
   }
}
