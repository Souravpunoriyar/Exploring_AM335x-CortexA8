ENTRY(BABA_entry)

SECTIONS
{
	. = 0x402F0400; /*Internal SRAM Start address, couter initialized to this address value*/
	.text : /*Adding all code */
	{
		startup.o (RESET_VECTOR)
		*(.text) /*add all code here after*/
	}
	.data :
	{
		*(.data) /*Global initialized data are kept here after 0x402f0400+size of text*/
	}
	.bss :
	{
		bss_begin = .;
		*(.bss)
		. = ALIGN(4); /*align address to 4 byte boundary*/
		bss_end = .;
		
	}
	stack_top = 0x4030B800;	/* 6KiB stack */

}
