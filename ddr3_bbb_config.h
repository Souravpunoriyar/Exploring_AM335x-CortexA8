

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

#define writel(v,c)     ({ unsigned int __v = v; __iowmb(); __arch_putl(__v,c); __v; })
#define readl(c)        ({ unsigned int __v = __arch_getl(c); __iormb(); __v; })


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


struct emif_reg_struct {
         unsigned int emif_mod_id_rev;
        unsigned int emif_status;
         unsigned int emif_sdram_config;
         unsigned int emif_lpddr2_nvm_config;
         unsigned int emif_sdram_ref_ctrl;
         unsigned int emif_sdram_ref_ctrl_shdw;
         unsigned int emif_sdram_tim_1;
         unsigned int emif_sdram_tim_1_shdw;
         unsigned int emif_sdram_tim_2;
         unsigned int emif_sdram_tim_2_shdw;
         unsigned int emif_sdram_tim_3;
        unsigned int emif_sdram_tim_3_shdw;
        unsigned int emif_lpddr2_nvm_tim;
         unsigned int emif_lpddr2_nvm_tim_shdw;
         unsigned int emif_pwr_mgmt_ctrl;
         unsigned int emif_pwr_mgmt_ctrl_shdw;
         unsigned int emif_lpddr2_mode_reg_data;
         unsigned int padding1[1];
         unsigned int emif_lpddr2_mode_reg_data_es2;
         unsigned int padding11[1];
         unsigned int emif_lpddr2_mode_reg_cfg;
         unsigned int emif_l3_config;
         unsigned int emif_l3_cfg_val_1;
         unsigned int emif_l3_cfg_val_2;
         unsigned int emif_iodft_tlgc;
         unsigned int padding2[7];
         unsigned int emif_perf_cnt_1;
         unsigned int emif_perf_cnt_2;
         unsigned int emif_perf_cnt_cfg;
         unsigned int emif_perf_cnt_sel;
         unsigned int emif_perf_cnt_tim;
         unsigned int padding3;
         unsigned int emif_read_idlectrl;
         unsigned int emif_read_idlectrl_shdw;
         unsigned int padding4;
         unsigned int emif_irqstatus_raw_sys;
         unsigned int emif_irqstatus_raw_ll;
         unsigned int emif_irqstatus_sys;
         unsigned int emif_irqstatus_ll;
         unsigned int emif_irqenable_set_sys;
         unsigned int emif_irqenable_set_ll;
         unsigned int emif_irqenable_clr_sys;
         unsigned int emif_irqenable_clr_ll;
         unsigned int padding5;
         unsigned int emif_zq_config;
         unsigned int emif_temp_alert_config;
         unsigned int emif_l3_err_log;
         unsigned int emif_rd_wr_lvl_rmp_win;
         unsigned int emif_rd_wr_lvl_rmp_ctl;
         unsigned int emif_rd_wr_lvl_ctl;
         unsigned int padding6[1];
         unsigned int emif_ddr_phy_ctrl_1;
         unsigned int emif_ddr_phy_ctrl_1_shdw;
         unsigned int emif_ddr_phy_ctrl_2;
         unsigned int padding7[4];
         unsigned int emif_prio_class_serv_map;
         unsigned int emif_connect_id_serv_1_map;
         unsigned int emif_connect_id_serv_2_map;
         unsigned int padding8[5];
         unsigned int emif_rd_wr_exec_thresh;
         unsigned int emif_cos_config;
         unsigned int padding9[6];
         unsigned int emif_ddr_phy_status[28];
         unsigned int padding10[20];
         unsigned int emif_ddr_ext_phy_ctrl_1;
         unsigned int emif_ddr_ext_phy_ctrl_1_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_2;
         unsigned int emif_ddr_ext_phy_ctrl_2_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_3;
         unsigned int emif_ddr_ext_phy_ctrl_3_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_4;
         unsigned int emif_ddr_ext_phy_ctrl_4_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_5;
         unsigned int emif_ddr_ext_phy_ctrl_5_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_6;
         unsigned int emif_ddr_ext_phy_ctrl_6_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_7;
         unsigned int emif_ddr_ext_phy_ctrl_7_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_8;
         unsigned int emif_ddr_ext_phy_ctrl_8_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_9;
         unsigned int emif_ddr_ext_phy_ctrl_9_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_10;
         unsigned int emif_ddr_ext_phy_ctrl_10_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_11;
         unsigned int emif_ddr_ext_phy_ctrl_11_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_12;
         unsigned int emif_ddr_ext_phy_ctrl_12_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_13;
         unsigned int emif_ddr_ext_phy_ctrl_13_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_14;
         unsigned int emif_ddr_ext_phy_ctrl_14_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_15;
         unsigned int emif_ddr_ext_phy_ctrl_15_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_16;
         unsigned int emif_ddr_ext_phy_ctrl_16_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_17;
         unsigned int emif_ddr_ext_phy_ctrl_17_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_18;
         unsigned int emif_ddr_ext_phy_ctrl_18_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_19;
         unsigned int emif_ddr_ext_phy_ctrl_19_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_20;
         unsigned int emif_ddr_ext_phy_ctrl_20_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_21;
         unsigned int emif_ddr_ext_phy_ctrl_21_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_22;
         unsigned int emif_ddr_ext_phy_ctrl_22_shdw;
         unsigned int emif_ddr_ext_phy_ctrl_23;
         unsigned int emif_ddr_ext_phy_ctrl_23_shdw;
          unsigned int emif_ddr_ext_phy_ctrl_24;
        unsigned int emif_ddr_ext_phy_ctrl_24_shdw;
        unsigned int emif_ddr_ext_phy_ctrl_25;
        unsigned int emif_ddr_ext_phy_ctrl_25_shdw;
        unsigned int emif_ddr_ext_phy_ctrl_26;
        unsigned int emif_ddr_ext_phy_ctrl_26_shdw;
        unsigned int emif_ddr_ext_phy_ctrl_27;
        unsigned int emif_ddr_ext_phy_ctrl_27_shdw;
        unsigned int emif_ddr_ext_phy_ctrl_28;
        unsigned int emif_ddr_ext_phy_ctrl_28_shdw;
        unsigned int emif_ddr_ext_phy_ctrl_29;
        unsigned int emif_ddr_ext_phy_ctrl_29_shdw;
        unsigned int emif_ddr_ext_phy_ctrl_30;
        unsigned int emif_ddr_ext_phy_ctrl_30_shdw;
        unsigned int emif_ddr_ext_phy_ctrl_31;
        unsigned int emif_ddr_ext_phy_ctrl_31_shdw;
        unsigned int emif_ddr_ext_phy_ctrl_32;
        unsigned int emif_ddr_ext_phy_ctrl_32_shdw;
        unsigned int emif_ddr_ext_phy_ctrl_33;
        unsigned int emif_ddr_ext_phy_ctrl_33_shdw;
        unsigned int emif_ddr_ext_phy_ctrl_34;
        unsigned int emif_ddr_ext_phy_ctrl_34_shdw;
        unsigned int emif_ddr_ext_phy_ctrl_35;
        unsigned int emif_ddr_ext_phy_ctrl_35_shdw;
        union {
                unsigned int emif_ddr_ext_phy_ctrl_36;
                unsigned int emif_ddr_fifo_misaligned_clear_1;
        };
        union {
                unsigned int emif_ddr_ext_phy_ctrl_36_shdw;
                unsigned int emif_ddr_fifo_misaligned_clear_2;
        };
};



struct ctrl_stat {
         unsigned int resv1[16];
         unsigned int statusreg;         /* ofset 0x40 */
         unsigned int resv2[51];
         unsigned int secure_emif_sdram_config;  /* offset 0x0110 */
         unsigned int resv3[319];
         unsigned int dev_attr;
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
 


struct ddr_cmd_regs {
        unsigned int resv0[7];
        unsigned int cm0csratio;        /* offset 0x01C */
        unsigned int resv1[3];
        unsigned int cm0iclkout;        /* offset 0x02C */
        unsigned int resv2[8];
        unsigned int cm1csratio;        /* offset 0x050 */
        unsigned int resv3[3];
        unsigned int cm1iclkout;        /* offset 0x060 */
        unsigned int resv4[8];
        unsigned int cm2csratio;        /* offset 0x084 */
        unsigned int resv5[3];
        unsigned int cm2iclkout;        /* offset 0x094 */
        unsigned int resv6[3];
};


/* DDR Base address */
#define DDR_PHY_CMD_ADDR                0x44E12000
#define DDR_PHY_DATA_ADDR               0x44E120C8
#define DDR_PHY_CMD_ADDR2               0x47C0C800
#define DDR_PHY_DATA_ADDR2              0x47C0C8C8
#define DDR_DATA_REGS_NR                2



static struct ddr_cmd_regs *ddr_cmd_reg[2] = {
                                  (struct ddr_cmd_regs *)DDR_PHY_CMD_ADDR,
                                  (struct ddr_cmd_regs *)DDR_PHY_CMD_ADDR2};




struct ddr_data_regs {
        unsigned int dt0rdsratio0;      /* offset 0x0C8 */
        unsigned int resv1[4];
        unsigned int dt0wdsratio0;      /* offset 0x0DC */
        unsigned int resv2[4];
        unsigned int dt0wiratio0;       /* offset 0x0F0 */
        unsigned int resv3;
        unsigned int dt0wimode0;        /* offset 0x0F8 */
        unsigned int dt0giratio0;       /* offset 0x0FC */
        unsigned int resv4;
        unsigned int dt0gimode0;        /* offset 0x104 */
        unsigned int dt0fwsratio0;      /* offset 0x108 */
        unsigned int resv5[4];
        unsigned int dt0dqoffset;       /* offset 0x11C */
        unsigned int dt0wrsratio0;      /* offset 0x120 */
        unsigned int resv6[4];
        unsigned int dt0rdelays0;       /* offset 0x134 */
        unsigned int dt0dldiff0;        /* offset 0x138 */
        unsigned int resv7[12];
};


static struct ddr_data_regs *ddr_data_reg[2] = {
                                (struct ddr_data_regs *)DDR_PHY_DATA_ADDR,
                                (struct ddr_data_regs *)DDR_PHY_DATA_ADDR2};



 void config_ddr(unsigned int pll, const struct ctrl_ioregs *ioregs,
                 const struct ddr_data *data, const struct cmd_control *ctrl,
                 const struct emif_regs *regs, int nr);

 struct ddr_cmdtctrl {
         unsigned int cm0ioctl;
         unsigned int cm1ioctl;
         unsigned int cm2ioctl;
         unsigned int resv2[12];
         unsigned int dt0ioctl;
         unsigned int dt1ioctl;
         unsigned int dt2ioctrl;
         unsigned int dt3ioctrl;
         unsigned int resv3[4];
         unsigned int emif_sdram_config_ext;
 };

/* DDR Base address */
#define DDR_CTRL_ADDR                   0x44E10E04
#define DDR_CONTROL_BASE_ADDR           0x44E11404

static struct ddr_cmdtctrl *ioctrl_reg = {
                          (struct ddr_cmdtctrl *)DDR_CONTROL_BASE_ADDR};



void ddr3_bbb_init();
