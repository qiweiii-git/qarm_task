//*****************************************************************************
//    # #              Name   : S3c2440Def.h
//  #     #            Date   : Nov. 15, 2020
// #    #  #  #     #  Author : Qiwei Wu
//  #     #  # #  # #  Version: 1.0
//    # #  #    #   #
// The defines of S3c2440 chip.
//*****************************************************************************

#ifndef  __S3C2440_DEF_H
#define  __S3C2440_DEF_H

// Includes
#include <s3c2440_soc.h>

// GPx define
enum
{
   GPXCON_INPUT    = 0,
   GPXCON_OUTPUT   = 1,
   GPXCON_FUNC     = 2,
   GPXCON_RESERVED = 3,
}e_gpxcon;

enum
{
   GPXUP_ENABLE    = 0,
   GPXUP_DISABLE   = 1,
}e_gpxup;

typedef union
{
   struct
   {
      unsigned GPX0        : 2;
      unsigned GPX1        : 2;
      unsigned GPX2        : 2;
      unsigned GPX3        : 2;
      unsigned GPX4        : 2;
      unsigned GPX5        : 2;
      unsigned GPX6        : 2;
      unsigned GPX7        : 2;
      unsigned GPX8        : 2;
      unsigned GPX9        : 2;
      unsigned GPX10       : 2;
      unsigned GPX11       : 2;
      unsigned GPX12       : 2;
      unsigned GPX13       : 2;
      unsigned GPX14       : 2;
      unsigned GPX15       : 2;
   }DATA32_t;
   unsigned data32;
}GPX_CON_t;

typedef union
{
   struct
   {
      unsigned GPX0        : 1;
      unsigned GPX1        : 1;
      unsigned GPX2        : 1;
      unsigned GPX3        : 1;
      unsigned GPX4        : 1;
      unsigned GPX5        : 1;
      unsigned GPX6        : 1;
      unsigned GPX7        : 1;
      unsigned GPX8        : 1;
      unsigned GPX9        : 1;
      unsigned GPX10       : 1;
      unsigned GPX11       : 1;
      unsigned GPX12       : 1;
      unsigned GPX13       : 1;
      unsigned GPX14       : 1;
      unsigned GPX15       : 1;
      unsigned reserved    : 16;
   }DATA32_t;
   unsigned data32;
}GPX_DAT_t;

typedef union
{
   struct
   {
      unsigned GPX0        : 1;
      unsigned GPX1        : 1;
      unsigned GPX2        : 1;
      unsigned GPX3        : 1;
      unsigned GPX4        : 1;
      unsigned GPX5        : 1;
      unsigned GPX6        : 1;
      unsigned GPX7        : 1;
      unsigned GPX8        : 1;
      unsigned GPX9        : 1;
      unsigned GPX10       : 1;
      unsigned GPX11       : 1;
      unsigned GPX12       : 1;
      unsigned GPX13       : 1;
      unsigned GPX14       : 1;
      unsigned GPX15       : 1;
      unsigned reserved    : 16;
   }DATA32_t;
   unsigned data32;
}GPX_UP_t;

// UART define
typedef union
{
   struct
   {
      unsigned wordLen     : 2;
      unsigned stopBit     : 1;
      unsigned parityMode  : 3;
      unsigned infrared    : 1;
      unsigned reserved    : 25;
   }DATA32_t;
   unsigned data32;
}UART_LCON_t;

typedef union
{
   struct
   {
      unsigned rxMode      : 2;
      unsigned txMode      : 2;
      unsigned breakSend   : 1;
      unsigned loopback    : 1;
      unsigned rxErrInt    : 1;
      unsigned rxTimeOut   : 1;
      unsigned rxIntType   : 1;
      unsigned txIntType   : 1;
      unsigned clockSel    : 2;
      unsigned fclkDiv     : 4;
      unsigned reserved    : 16;
   }DATA32_t;
   unsigned data32;
}UART_CON_t;

typedef union
{
   struct
   {
      unsigned rxRdy       : 1;
      unsigned txBufEmpty  : 1;
      unsigned txEmpty     : 1;
      unsigned reserved    : 29;
   }DATA32_t;
   unsigned data32;
}UART_STATUS_t;

#endif
