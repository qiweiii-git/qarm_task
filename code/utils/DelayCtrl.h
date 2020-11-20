//*****************************************************************************
//    # #              Name   : DelayCtrl.h
//  #     #            Date   : Nov. 14, 2020
// #    #  #  #     #  Author : Qiwei Wu
//  #     #  # #  # #  Version: 1.0
//    # #  #    #   #
// The delay control.
//*****************************************************************************

#include <sys/time.h>

#if 0
struct
{
   int tz_minuteswest;/*格林威治时间往西方的时差*/
   int tz_dsttime;    /*DST 时间的修正方式*/
}timeZone_t;

struct
{
   long int tv_sec;  // 秒数
   long int tv_usec; // 微秒数
}timeVal_t;
#endif

void DelayUs(int uSec)
{
   struct timeval timeValBegin, timeValEnd;
   struct timezone timeZone;

   // 获取当前时间
   gettimeofday(&timeValBegin, &timeZone);

   unsigned int delaySec;
   unsigned int delayUSec;

   // 获取准确的延迟时间（s和us）
   if(uSec > 1000000)
   {
      delaySec = uSec / 1000000;
   }
   else
   {
      delaySec = 0;
   }
   
   delayUSec = uSec % 1000000;

   while(1)
   {
      // 获取当前时间
      gettimeofday(&timeValEnd, &timeZone);

      // 判断是否满足延迟，若是，则退出循环，延迟完成
      if(timeValEnd.tv_sec - timeValBegin.tv_sec >= delaySec &&
         timeValEnd.tv_usec - timeValBegin.tv_usec >= delayUSec)
      {
         break;
      }
   }
}
