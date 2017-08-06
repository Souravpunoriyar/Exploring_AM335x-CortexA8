#include "common.h"
#include "interrupt.h"
#include "bbb.h"
#include "arm.h"
#include "serial.h"
#include "core_init.h"

/*to enable debugs #define CORE_INIT_DEBUG*/

#ifdef CORE_INIT_DEBUG
  #define SERIAL_DEBUG(a) serial_tx(a)
#else
  #define SERIAL_DEBUG(a)
#endif



/*Why only to enable L1 instruction cache, Disable L1 Data Cache
 * answer: https://stackoverflow.com/questions/21262014/arm-bootloader-disable-mmu-and-caches
 * */

unsigned long read_SCTLR(void) /*Reading CP15 system control register*/
{
  unsigned long system_register = 0;
  char hex_string[50] ={0};
  __asm__ __volatile__("mrc p15, 0, %0, c1, c0, 0 \n" : "=r" (system_register) : : );
  SERIAL_DEBUG("SCTLR_Register = ");
  get_hex_string( system_register , hex_string, 50);
  SERIAL_DEBUG(hex_string);
  SERIAL_DEBUG("\r\n");
  return system_register;
}

void enable_Icache_L1(void)
{
 unsigned long system_register = 0; 
 
 /*check status of system register*/
 system_register = read_SCTLR();

 /*if I-cache disable then enable I-cache L1*/
  if( !(BIT_STATUS( system_register, 12))) 
  {
     SERIAL_DEBUG("Enable Icache \r\n ");
      asm(
	 "MRC p15, 0, r1, c1, c0, 0\n\t" // Read System Control Register (SCTLR)
     "BIC r1, r1, #1\n\t" // mmu off
     "BIC r1, r1, #(1 << 12)\n\t" //i-cache off
     "BIC r1, r1, #(1 << 2)\n\t" //d-cache & L2-$ off
     "MCR p15, 0, r1, c1, c0, 0\n\t" //Write System Control Register (SCTLR)
     );
     
     asm(
      "MRC p15, 0, r0, c1, c0, 0\n\t"      // System control register
      "ORR r0, r0, #1 << 12\n\t"          // Instruction cache enable
      "ORR r0, r0, #1 << 11\n\t"         //Program flow prediction
      "MCR p15, 0, r0, c1, c0, 0\n\t"   //System control register
     );
     	  
  }
  else
    SERIAL_DEBUG("Icache already enabled \r\n ");   	   
   
}


/* The following code needs -mfpu=neon to be added as compiler flag */
void neon_enable(void)
{
        __asm__ __volatile__("mrc p15, 0, r1, c1, c0, 2\n"); // r1 = Access Control Register
        __asm__ __volatile__("orr r1, r1, (0xF << 20)\n"); // Enable full access for coprocessor p10,11
        __asm__ __volatile__("mcr p15, 0, r1, c1, c0, 2\n"); // Access Control Register = r1
        __asm__ __volatile__("mov r0, 0x40000000\n");  // Switch on the VFP and NEON hardware
        __asm__ __volatile__("vmsr fpexc, r0\n"); // Set Neon/VFP Enable bit - fmxr <=> vmsr
}

void neon_disable(void)
{
        __asm__ __volatile__("mov r0, 0x00000000\n");
        __asm__ __volatile__("vmsr fpexc, r0\n"); // Clear Neon/VFP Enable bit - fmxr <=> vmsr
        __asm__ __volatile__("mrc p15, 0, r1, c1, c0, 2\n"); // r1 = Access Control Register
        __asm__ __volatile__("bic r1, r1, (0xF << 20)\n"); // Disable full access for p10,11
        __asm__ __volatile__("mcr p15, 0, r1, c1, c0, 2\n"); // Access Control Register = r1
}



void core_init(void)
{
	interrupt_init(); //setup interrupt vector table
	enable_Icache_L1(); //disable mmu and l1-data cache , only enable l1 instruction cache
	neon_enable(); //Enable NEON and FPU	
}
