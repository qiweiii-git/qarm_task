//*****************************************************************************
//    # #              Name   : QArm01Uart.c
//  #     #            Date   : Nov. 15, 2020
// #    #  #  #     #  Author : Qiwei Wu
//  #     #  # #  # #  Version: 1.0
//    # #  #    #   #
// The qarm01_uart project.
//*****************************************************************************

#include <LedCtrl.h>
#include <UartCtrl.h>

int main()
{
   unsigned char charData;

   // Set a LED on
   LedCtrlInit(1);
   LedCtrlSet(1, 1);

   // Uart function
   UartCtrlInit();
   PutString("\r\nqarm01_uart project\r\n");

   while(1)
   {
      GetChar(&charData);

      if(charData == '\r' || charData == '\n')
      {
         PutString("\r\n");
      }
      else
      {
         PutChar(charData);
      }
   }
   return 0;
}
