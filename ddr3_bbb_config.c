#include "ddr3_bbb_config.h"

static const struct ddr_data ddr3_beagleblack_data = {
	.datardsratio0 = MT41K256M16HA125E_RD_DQS,
	.datawdsratio0 = MT41K256M16HA125E_WR_DQS,
	.datafwsratio0 = MT41K256M16HA125E_PHY_FIFO_WE,
	.datawrsratio0 = MT41K256M16HA125E_PHY_WR_DATA,
};



const struct ctrl_ioregs ioregs_bonelt = {
	.cm0ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
	.cm1ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
	.cm2ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
	.dt0ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
	.dt1ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
};


static const struct cmd_control ddr3_beagleblack_cmd_ctrl_data = {
	.cmd0csratio = MT41K256M16HA125E_RATIO,
	.cmd0iclkout = MT41K256M16HA125E_INVERT_CLKOUT,

	.cmd1csratio = MT41K256M16HA125E_RATIO,
	.cmd1iclkout = MT41K256M16HA125E_INVERT_CLKOUT,

	.cmd2csratio = MT41K256M16HA125E_RATIO,
	.cmd2iclkout = MT41K256M16HA125E_INVERT_CLKOUT,
};



static struct emif_regs ddr3_beagleblack_emif_reg_data = {
         .sdram_config = MT41K256M16HA125E_EMIF_SDCFG,
         .ref_ctrl = MT41K256M16HA125E_EMIF_SDREF,
         .sdram_tim1 = MT41K256M16HA125E_EMIF_TIM1,
         .sdram_tim2 = MT41K256M16HA125E_EMIF_TIM2,
         .sdram_tim3 = MT41K256M16HA125E_EMIF_TIM3,
         .zq_config = MT41K256M16HA125E_ZQ_CFG,
         .emif_ddr_phy_ctlr_1 = MT41K256M16HA125E_EMIF_READ_LATENCY,
 };
 


#define DDR_CKE_CTRL_NORMAL     0x1
/* DDR Base address */
#define DDR_CTRL_ADDR                   0x44E10E04
#define DDR_CONTROL_BASE_ADDR           0x44E11404





/**
 * Base address for EMIF instances
 */
 /* EMIF Base address */
#define EMIF4_0_CFG_BASE                0x4C000000
#define EMIF4_1_CFG_BASE                0x4D000000
static struct emif_reg_struct *emif_reg[2] = {
                                (struct emif_reg_struct *)EMIF4_0_CFG_BASE,
                                (struct emif_reg_struct *)EMIF4_1_CFG_BASE};

struct ddr_ctrl {
        unsigned int ddrioctrl;
        unsigned int resv1[325];
        unsigned int ddrckectrl;
};
 

static struct ddr_ctrl *ddrctrl = (struct ddr_ctrl *)DDR_CTRL_ADDR;

/* Control Module Base Address */
#define CTRL_BASE                       0x44E10000
#define CTRL_DEVICE_BASE                0x44E10600

struct ctrl_stat *cstat = (struct ctrl_stat *)CTRL_BASE;
void config_sdram(const struct emif_regs *regs, int nr)
{
	unsigned int i = 1000;
        if (regs->zq_config) {
                writel(regs->zq_config, &emif_reg[nr]->emif_zq_config);
                writel(regs->sdram_config, &cstat->secure_emif_sdram_config);
                writel(regs->sdram_config, &emif_reg[nr]->emif_sdram_config);

                /* Trigger initialization */
                writel(0x00003100, &emif_reg[nr]->emif_sdram_ref_ctrl);
               /* Wait 1ms because of L3 timeout error */
                //udelay(1000);
                while(i)
                 i--;
   
                /* Write proper sdram_ref_cref_ctrl value */
                writel(regs->ref_ctrl, &emif_reg[nr]->emif_sdram_ref_ctrl);
                writel(regs->ref_ctrl, &emif_reg[nr]->emif_sdram_ref_ctrl_shdw);
        }
        writel(regs->ref_ctrl, &emif_reg[nr]->emif_sdram_ref_ctrl);
        writel(regs->ref_ctrl, &emif_reg[nr]->emif_sdram_ref_ctrl_shdw);
        writel(regs->sdram_config, &emif_reg[nr]->emif_sdram_config);
}



void config_ddr(unsigned int pll, const struct ctrl_ioregs *ioregs,
                 const struct ddr_data *data, const struct cmd_control *ctrl,
                 const struct emif_regs *regs, int nr)
 {
        // ddr_pll_config(pll);
         config_cmd_ctrl(ctrl, nr);
 
         config_ddr_data(data, nr);
         config_io_ctrl(ioregs);
         /* Set CKE to be controlled by EMIF/DDR PHY */
         writel(DDR_CKE_CTRL_NORMAL, &ddrctrl->ddrckectrl);
 
         /* Program EMIF instance */
         //	(regs, nr);
         //set_sdram_timings(regs, nr);
        // if (get_emif_rev(EMIF1_BASE) == EMIF_4D5)
          //       config_sdram_emif4d5(regs, nr);
         //else
                 config_sdram(regs, nr);
 }
 







void ddr3_bbb_init()
{
    config_ddr(400, &ioregs_bonelt,
			   &ddr3_beagleblack_data,
			   &ddr3_beagleblack_cmd_ctrl_data,
			   &ddr3_beagleblack_emif_reg_data, 0);
}













