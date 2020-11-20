//*****************************************************************************
//    # #              Name   : QArm00Led.c
//  #     #            Date   : Nov. 14, 2020
// #    #  #  #     #  Author : Qiwei Wu
//  #     #  # #  # #  Version: 1.0
//    # #  #    #   #
// The qarm00_led project.
//*****************************************************************************

#include <LedCtrl.h>

#define LEDNUM 3

void delay(volatile int delayCnt)
{
    while(delayCnt)
    {
        delayCnt--;
    }
}

int main()
{
   int i;

   // Init
   for(i = 0; i < LEDNUM; i++)
   {
      LedCtrlInit(i);
   }

   while(1)
   {
      delay(100000);
      // Set LED on
      for(i = 0; i < LEDNUM; i++)
      {
         LedCtrlSet(i, 1);
      }

      delay(100000);
      // Set LED off
      for(i = 0; i < LEDNUM; i++)
      {
         LedCtrlSet(i, 0);
      }
   }

   return 0;
}

