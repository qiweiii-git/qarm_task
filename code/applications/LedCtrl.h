//*****************************************************************************
//    # #              Name   : LedCtrl.h
//  #     #            Date   : Nov. 14, 2020
// #    #  #  #     #  Author : Qiwei Wu
//  #     #  # #  # #  Version: 1.0
//    # #  #    #   #
// The LED control.
//*****************************************************************************

#ifndef  __LED_CTRL_H
#define  __LED_CTRL_H

// Includes
#include <S3c2440Def.h>

// Defines
#define LEDCON GPFCON
#define LEDDAT GPFDAT

enum
{
   LEDCTRL_ON  = 0,
   LEDCTRL_OFF = 1,
}e_ledctrl;

// Functions
int LedCtrlInit(int index);
int LedCtrlSet(int on, int index);

#endif
