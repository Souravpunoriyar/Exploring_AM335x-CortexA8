

 /* Micron MT41K256M16HA-125E */
 #define MT41K256M16HA125E_EMIF_READ_LATENCY     0x100007
 #define MT41K256M16HA125E_EMIF_TIM1             0x0AAAD4DB
 #define MT41K256M16HA125E_EMIF_TIM2             0x266B7FDA
 #define MT41K256M16HA125E_EMIF_TIM3             0x501F867F
 #define MT41K256M16HA125E_EMIF_SDCFG            0x61C05332
 #define MT41K256M16HA125E_EMIF_SDREF            0xC30
 #define MT41K256M16HA125E_ZQ_CFG                0x50074BE4
 #define MT41K256M16HA125E_RATIO                 0x80
 #define MT41K256M16HA125E_INVERT_CLKOUT         0x0
 #define MT41K256M16HA125E_RD_DQS                0x38
 #define MT41K256M16HA125E_WR_DQS                0x44
 #define MT41K256M16HA125E_PHY_WR_DATA           0x7D
 #define MT41K256M16HA125E_PHY_FIFO_WE           0x94
 #define MT41K256M16HA125E_IOCTRL_VALUE          0x18B

/*memory barriers*/
#define CP15ISB asm volatile ("mcr     p15, 0, %0, c7, c5, 4" : : "r" (0))
#define CP15DSB asm volatile ("mcr     p15, 0, %0, c7, c10, 4" : : "r" (0))
#define CP15DMB asm volatile ("mcr     p15, 0, %0, c7, c10, 5" : : "r" (0))


#define ISB     CP15ISB
#define DSB     CP15DSB
#define DMB     CP15DMB

#define isb()   ISB
#define dsb()   DSB
#define dmb()   DMB


/*for readl and writel*/
#define __arch_getl(a)                  (*(volatile unsigned int *)(a))
#define __arch_putl(v,a)                (*(volatile unsigned int *)(a) = (v))

#define mb()            dsb()
#define __iormb()       dmb()
#define __iowmb()       dmb()

#define writel(v,c)     ({ u32 __v = v; __iowmb(); __arch_putl(__v,c); __v; })
#define readl(c)        ({ u32 __v = __arch_getl(c); __iormb(); __v; })


/* PLL Subsystem Base Address */
#define PLL_SUBSYS_BASE                 0x481C5000

/* PRCM */
#define PRCM_MOD_EN             0x2

/* CLK_SRC */
#define OSC_SRC0                0
#define OSC_SRC1                1

#define L3_OSC_SRC              OSC_SRC0

#define OSC_0_FREQ              20

#define DCO_HS2_MIN             500
#define DCO_HS2_MAX             1000
#define DCO_HS1_MIN             1000
#define DCO_HS1_MAX             2000

#define SELFREQDCO_HS2          0x00000801
#define SELFREQDCO_HS1          0x00001001

#define MPU_N                   0x1
#define MPU_M                   0x3C
#define MPU_M2                  1
#define MPU_CLKCTRL             0x1

#define L3_N                    19
#define L3_M                    880
#define L3_M2                   4
#define L3_CLKCTRL              0x801

#define DDR_N                   19
#define DDR_M                   666
#define DDR_M2                  2
#define DDR_CLKCTRL             0x801

/* ADPLLJ register values */
#define ADPLLJ_CLKCTRL_HS2      0x00000801 /* HS2 mode, TINT2 = 1 */
#define ADPLLJ_CLKCTRL_HS1      0x00001001 /* HS1 mode, TINT2 = 1 */
#define ADPLLJ_CLKCTRL_CLKDCOLDOEN      (1 << 29)
#define ADPLLJ_CLKCTRL_IDLE             (1 << 23)
#define ADPLLJ_CLKCTRL_CLKOUTEN         (1 << 20)
#define ADPLLJ_CLKCTRL_CLKOUTLDOEN      (1 << 19)
#define ADPLLJ_CLKCTRL_CLKDCOLDOPWDNZ   (1 << 17)
#define ADPLLJ_CLKCTRL_LPMODE           (1 << 12)
#define ADPLLJ_CLKCTRL_DRIFTGUARDIAN    (1 << 11)
#define ADPLLJ_CLKCTRL_REGM4XEN         (1 << 10)
#define ADPLLJ_CLKCTRL_TINITZ           (1 << 0)
#define ADPLLJ_CLKCTRL_CLKDCO           (ADPLLJ_CLKCTRL_CLKDCOLDOEN | \
                                         ADPLLJ_CLKCTRL_CLKOUTEN | \
                                         ADPLLJ_CLKCTRL_CLKOUTLDOEN | \
                                         ADPLLJ_CLKCTRL_CLKDCOLDOPWDNZ)

#define ADPLLJ_STATUS_PHASELOCK         (1 << 10)
#define ADPLLJ_STATUS_FREQLOCK          (1 << 9)
#define ADPLLJ_STATUS_PHSFRQLOCK        (ADPLLJ_STATUS_PHASELOCK | \
                                         ADPLLJ_STATUS_FREQLOCK)
#define ADPLLJ_STATUS_BYPASSACK         (1 << 8)
#define ADPLLJ_STATUS_BYPASS            (1 << 0)
#define ADPLLJ_STATUS_BYPASSANDACK      (ADPLLJ_STATUS_BYPASSACK | \
                                         ADPLLJ_STATUS_BYPASS)

#define ADPLLJ_TENABLE_ENB              (1 << 0)
#define ADPLLJ_TENABLEDIV_ENB           (1 << 0)

#define ADPLLJ_M2NDIV_M2SHIFT           16

#define MPU_PLL_BASE                    (PLL_SUBSYS_BASE + 0x048)
#define L3_PLL_BASE                     (PLL_SUBSYS_BASE + 0x110)
#define DDR_PLL_BASE                    (PLL_SUBSYS_BASE + 0x290)


struct ad_pll {
          unsigned int pwrctrl;
          unsigned int clkctrl;
          unsigned int tenable;
          unsigned int tenablediv;
          unsigned int m2ndiv;
          unsigned int mn2div;
          unsigned int fracdiv;
          unsigned int bwctrl;
          unsigned int fracctrl;
          unsigned int status;
          unsigned int m3div;
          unsigned int rampctrl;
  };









/*
 * Structure containing shadow of important registers in EMIF
 * The calculation function fills in this structure to be later used for
 * initialization and DVFS
 */
struct emif_regs {
        unsigned int freq;
        unsigned int sdram_config_init;
        unsigned int sdram_config;
        unsigned int sdram_config2;
        unsigned int ref_ctrl;
        unsigned int ref_ctrl_final;
        unsigned int sdram_tim1;
        unsigned int sdram_tim2;
        unsigned int sdram_tim3;
        unsigned int ocp_config;
        unsigned int read_idle_ctrl;
        unsigned int zq_config;
        unsigned int temp_alert_config;
        unsigned int emif_ddr_phy_ctlr_1_init;
        unsigned int emif_ddr_phy_ctlr_1;
        unsigned int emif_ddr_ext_phy_ctrl_1;
        unsigned int emif_ddr_ext_phy_ctrl_2;
        unsigned int emif_ddr_ext_phy_ctrl_3;
        unsigned int emif_ddr_ext_phy_ctrl_4;
        unsigned int emif_ddr_ext_phy_ctrl_5;
        unsigned int emif_rd_wr_lvl_rmp_win;
        unsigned int emif_rd_wr_lvl_rmp_ctl;
        unsigned int emif_rd_wr_lvl_ctl;
        unsigned int emif_rd_wr_exec_thresh;
        unsigned int emif_prio_class_serv_map;
        unsigned int emif_connect_id_serv_1_map;
        unsigned int emif_connect_id_serv_2_map;
        unsigned int emif_cos_config;
};



struct ctrl_ioregs {
         unsigned int cm0ioctl;
         unsigned int cm1ioctl;
         unsigned int cm2ioctl;
         unsigned int dt0ioctl;
         unsigned int dt1ioctl;
         unsigned int dt2ioctrl;
         unsigned int dt3ioctrl;
         unsigned int emif_sdram_config_ext;
 };


struct ddr_data {
        unsigned long datardsratio0;
        unsigned long datawdsratio0;
        unsigned long datawiratio0;
        unsigned long datagiratio0;
        unsigned long datafwsratio0;
         unsigned long datawrsratio0;
 };

struct cmd_control {
         unsigned long cmd0csratio;
         unsigned long cmd0csforce;
         unsigned long cmd0csdelay;
         unsigned long cmd0iclkout;
         unsigned long cmd1csratio;
         unsigned long cmd1csforce;
         unsigned long cmd1csdelay;
         unsigned long cmd1iclkout;
         unsigned long cmd2csratio;
         unsigned long cmd2csforce;
         unsigned long cmd2csdelay;
         unsigned long cmd2iclkout;
 };
 

 void config_ddr(unsigned int pll, const struct ctrl_ioregs *ioregs,
                 const struct ddr_data *data, const struct cmd_control *ctrl,
                 const struct emif_regs *regs, int nr);
