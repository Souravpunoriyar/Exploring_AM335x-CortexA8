#ifndef ARM_H

#define ARM_H

typedef enum
{
	cm_usr = 0x10,
	cm_fiq = 0x11,
	cm_irq = 0x12,
	cm_svc = 0x13,
	cm_abt = 0x17,
	cm_und = 0x1B,
	cm_sys = 0x1F,
	cm_mask = 0x1F
} CPUMode;

/*
 * isb/dsb/dmb memory barriors
 * https://community.arm.com/processors/b/blog/posts/memory-access-ordering-part-3---memory-access-ordering-in-the-arm-architecture
 * 
 * */


static inline void mb(void)
{
	__asm__ __volatile__("dsb\n"); /*Memory barrior concept: whenever a memory access needs to have completed before program execution progresses.*/
}
static inline void ib(void)
{
	__asm__ __volatile__("isb\n"); /*Memory barrior concept:whenever instruction fetches need to explicitly take place after a certain point in the program, for example after memory map updates or after writing code to be executed. (In practice, this means "throw away any prefetched instructions at this point".)*/
}
unsigned long cpu_mode_get(void);
void cpu_mode_set(CPUMode cm);
void neon_enable(void);
void neon_disable(void);

#endif
