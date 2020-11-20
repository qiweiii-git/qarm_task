
.text
.global _start

_start:
   /* 关闭看门狗 */
   ldr r0, =0x53000000
   ldr r1, =0
   str r1, [r0]

   /* 设置CPU工作频率 */
   /* FCLK = 400MHz */
   /* HCLK = 100MHz */
   /* PCLK = 50MHz */
   /* LOCKTIME(0x4C000000) = 0xFFFFFFFF */
   ldr r0, =0x4c000000
   ldr r1, =0xffffffff
   str r1, [r0]
   /* CLKDIVN(0x4C000014) = 0x5 */
   ldr r0, =0x4c000014
   ldr r1, =0x5
   str r1, [r0]
   /* 设置CPU工作在异步模式 */
   mrc p15, 0, r0, c1, c0, 0
   orr r0, r0, #0xC0000000
   mcr p15, 0, r0, c1, c0, 0
   /* MPLLCON(0x4C000004) = 92<<12|1<<4|1<<0 */
   ldr r0, =0x4c000004
   ldr r1, =(92<<12)|(1<<4)|(1<<0)
   str r1, [r0]

   /* 自动判断是NAND启动还是NOR启动 */
   /* NOR启动时，0地址指向的是NOR Flash, NOR Flash写入需要依赖一定的格式 */
   /* NAND启动时，0地址指向的是片内内存 */
   /* 写0到0地址，读出来如果为0，则表示是NAND启动（写入了片内内存），否则则为NOR启动 */
   mov r1, #0
   ldr r0, [r1] /* 备份原来的值 */ 
   str r1, [r1] /* 0写入0地址 */
   ldr r2, [r1]
   cmp r1, r2
   /* 设置内存：sp栈(局部变量) */
   ldr sp, =0x40000000+4096 /* nor启动 */
   moveq sp, #4096 /* nand启动 */ /* cmp相等时才执行 */
   streq r0, [r1] /* 恢复原来的值 */

   /* 调用main */
   bl main

halt:
   b halt
