//*****************************************************************************
//    # #              Name   : UartCtrl.c
//  #     #            Date   : Nov. 15, 2020
// #    #  #  #     #  Author : Qiwei Wu
//  #     #  # #  # #  Version: 1.0
//    # #  #    #   #
// The UART control.
//*****************************************************************************

#include <UartCtrl.h>

// Initialization of UART control
int UartCtrlInit()
{
   // Set hardware pins
   GPX_CON_t uartGpxCon;
   GPX_UP_t  uartGpxUp;

   uartGpxCon.data32 = UARTGPCON;
   uartGpxUp.data32  = UARTGPUP;

   uartGpxCon.DATA32_t.GPX2 = GPXCON_FUNC;
   uartGpxCon.DATA32_t.GPX3 = GPXCON_FUNC;

   uartGpxUp.DATA32_t.GPX2  = GPXUP_ENABLE;
   uartGpxUp.DATA32_t.GPX3  = GPXUP_ENABLE;

   UARTGPCON = uartGpxCon.data32;
   UARTGPUP  = uartGpxUp.data32;

   // Set UART mode
   UART_LCON_t uartLCon;
   UART_CON_t  uartCon;

   uartLCon.data32 = UARTLCON;
   uartCon.data32  = UARTCON;

   uartLCon.DATA32_t.wordLen = 3;

   uartCon.DATA32_t.txMode = 1;
   uartCon.DATA32_t.rxMode = 1;

   UARTLCON = uartLCon.data32;
   UARTCON  = uartCon.data32;

   // Set bitrate to 115200
   // UBRDIVn = (int)( UART clock / ( buad rate x 16) ) –1
   // UBRDIVn = 50M/115200/16 - 1 = 26
   UARTBRDIV = 26;

   return 0;
}

// Get char
int GetChar(char *charData)
{
   UART_STATUS_t uartStatus;

   uartStatus.data32 = UARTSTATUS;

   while(uartStatus.DATA32_t.rxRdy == 0)
   {
      uartStatus.data32 = UARTSTATUS;
   }

   *charData = UARTRXD;

   return 0;
}

// Put char
int PutChar(char charData)
{
   UART_STATUS_t uartStatus;

   uartStatus.data32 = UARTSTATUS;

   while(uartStatus.DATA32_t.txEmpty == 0)
   {
      uartStatus.data32 = UARTSTATUS;
   }

   UARTTXD = charData;

   return 0;
}

// Put string
int PutString(const char *charData)
{
   while(*charData)
   {
      PutChar(*charData);
      charData++;
   }
}
