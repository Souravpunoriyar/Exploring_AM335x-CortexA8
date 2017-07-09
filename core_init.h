void core_init(void);
unsigned long read_SCTLR(void);
#define BIT_STATUS(value,position) (((value >> position) & 1 )?1:0)
