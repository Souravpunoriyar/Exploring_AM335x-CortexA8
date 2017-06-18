/*assembler directives : http://downloads.ti.com/docs/esd/SLAU131K/Content/SLAU131K_HTML/assembler_directives.html*/
/*The ".global" directive declares a symbol external so that it is 
available to other modules at link time. (For more information about 
global symbols, see Section 2.6.1). The .global directive does double 
duty, acting as a .def for defined symbols and as a .ref for undefined 
symbols. The linker resolves an undefined global symbol reference only 
if the symbol is used in the program. The .global directive declares a 
16-bit symbol.*/

.global _asm_entry
.global _undefined_instruction
.global _software_interrupt
.global _prefetch_abort
.global _data_abort
.global _interrupt
.global _fast_interrupt

/*The ".set" and ".equ" directives set a constant value to a symbol. T*/
.set MODE_IRQ, 0x12
.set MODE_SVC, 0x13
.set I_F_BIT, 0xC0

.set SVC_STACK_SIZE, 0x1000 /* 4 KiB */

/*https://sourceware.org/binutils/docs/as/Section.html*/
/*Use the ".section" directive to assemble the following code into a section named name.
"x" = executable section
*/

.section RESET_VECTOR, "x"
_asm_entry:
	LDR r0, =stack_top  /*Load stack_top value in r0*/
	MOV sp, r0			/* Set supervisor mode stack pointer sp = 0x4030B800 */
	SUB r0, r0, #SVC_STACK_SIZE /*0x4030B800 - 0x1000 = 0x4030a800*/
	/*IRQ mode needs to be set-up if we are using interrupts in the bare-metal code*/
	MSR cpsr, #MODE_IRQ | I_F_BIT /*SET CPSR to IRQ (10010) mode  (processor mode to IRQ) and also disable IRQand FIQ 11000000*/
	MOV sp, r0			/* Set irq mode stack pointer = 0x4030a800 */
	MSR cpsr, #MODE_SVC | I_F_BIT /*SET CPSR to SVC (10011) mode  (processor mode to SVC) and also disable IRQand FIQ 11000000*/
	BL _clear_bss		/* Zero out the BSS */
	BL c_entry			/* C code entry point */
	B .					/* Loop forever after return from C code */

_clear_bss:
/* loop to zero out the bss region

while(r1! = r2) {
*r1 = 0;
r1++;
}

*/
	MOV r0, #0 
	LDR r1, =bss_begin
	LDR r2, =bss_end
1:
	CMP r1, r2
	BEQ 2f   /*jump to label2: if previously compared values were equal*/
	STR r0, [r1]
	ADD r1, #4
	B 1b /*branch to 1 :*/
2:
	BX lr /*return*/

.align	2
_undefined_instruction:
	B undefined_instruction_vector	/* Undefined Instruction */
.align	2
_software_interrupt:
	B software_interrupt_vector		/* Software Interrupt (SWI) */
.align	2
_prefetch_abort:
	B prefetch_abort_vector			/* Prefetch Abort */
.align	2
_data_abort:
	B data_abort_vector				/* Data Abort */
.align	2
_interrupt:
	B interrupt_vector				/* IRQ (Interrupt) */
.align	2
_fast_interrupt:
	B fast_interrupt_vector			/* FIQ (Fast Interrupt) */
