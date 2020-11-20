//*****************************************************************************
//    # #              Name   : LedCtrl.c
//  #     #            Date   : Nov. 14, 2020
// #    #  #  #     #  Author : Qiwei Wu
//  #     #  # #  # #  Version: 1.0
//    # #  #    #   #
// The LED control.
//*****************************************************************************

#include <LedCtrl.h>

// Initialization of LED control
int LedCtrlInit(int index)
{
   GPX_CON_t ledGpxCon;

   ledGpxCon.data32 = LEDCON;

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

   LEDCON = ledGpxCon.data32;

   return 0;
}

// Control set of LED
int LedCtrlSet(int index, int on)
{
   int ledCtrlBit;
   GPX_DAT_t ledGpxDat;

   ledGpxDat.data32 = LEDDAT;

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

   LEDDAT = ledGpxDat.data32;

   return 0;
}
