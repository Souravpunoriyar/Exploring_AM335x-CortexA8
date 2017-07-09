#include "common.h"
#include "interrupt.h"
#include "bbb.h"
#include "arm.h"
#include "serial.h"

void read_SCTLR(void)
{
  unsigned long system_register = 0;
  char hex_string[50] ={0};
  __asm__ __volatile__("mrc p15, 0, %0, c1, c0, 0 \n" : "=r" (system_register) : : );
  serial_tx("SCTLR_Register = ");
  get_hex_string( system_register , hex_string, 50);
  serial_tx(hex_string);
  serial_tx("\r\n");
}


void toggle_cache_bit(void)
{
	
  read_SCTLR();
    
    asm(
	 "MRC p15, 0, r1, c1, c0, 0\n\t" // Read System Control Register (SCTLR)
     "BIC r1, r1, #1\n\t" // mmu off
     "BIC r1, r1, #(1 << 12)\n\t" //i-cache off
     "BIC r1, r1, #(1 << 2)\n\t" //d-cache & L2-$ off
     "MCR p15, 0, r1, c1, c0, 0\n\t" //Write System Control Register (SCTLR)
     );
   
   read_SCTLR();
   asm(
      "MRC p15, 0, r0, c1, c0, 0\n\t"      // System control register
      "ORR r0, r0, #1 << 12\n\t"          // Instruction cache enable
      "ORR r0, r0, #1 << 11\n\t"         //Program flow prediction
      "MCR p15, 0, r0, c1, c0, 0\n\t"   //System control register
     );
   read_SCTLR();
}

#if 0
void enable_Icache_L1(void)
{
 unsigned long system_register = 0; 
 unsigned long system_result = 0
 /*check status of system register*/
 //read_SCTLR();

 /*if I-cache disable then enable I-cache L1*/
 /*in C
  * if(result = ((r0 >> position)&(1)))
  *    bit is set
  * */
 //__asm__ __volatile__("mrc p15, 0, %0, c1, c0, 0 \n" : "=r" (system_register) : : );
 //__asm__ __volatile__(");
  
}
#endif


void core_init(void)
{
	interrupt_init(); //setup interrupt vector table
	toggle_cache_bit();
		
}
