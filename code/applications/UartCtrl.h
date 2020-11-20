//*****************************************************************************
//    # #              Name   : UartCtrl.h
//  #     #            Date   : Nov. 15, 2020
// #    #  #  #     #  Author : Qiwei Wu
//  #     #  # #  # #  Version: 1.0
//    # #  #    #   #
// The UART control.
//*****************************************************************************

#ifndef  __UART_CTRL_H
#define  __UART_CTRL_H

// Includes
#include <S3c2440Def.h>

// Defines
#define UARTGPCON  GPHCON
#define UARTGPUP   GPHUP
#define UARTLCON   ULCON0
#define UARTCON    UCON0
#define UARTBRDIV  UBRDIV0
#define UARTSTATUS UTRSTAT0
#define UARTTXD    UTXH0
#define UARTRXD    URXH0

// Variables

// Functions
int UartCtrlInit();
int GetChar(char *charData);
int PutChar(char charData);
int PutString(const char *charData);

#endif
