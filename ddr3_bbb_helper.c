#include "ddr3_bbb_config.h"

static unsigned int pll_sigma_delta_val(unsigned int clkout_dco)
{
        unsigned int sig_val = 0;

        sig_val = (clkout_dco + 225) / 250;
        sig_val = sig_val << 24;
 
         return sig_val;
 }
 

static unsigned int pll_dco_freq_sel(unsigned int clkout_dco)
{
        if (clkout_dco >= DCO_HS2_MIN && clkout_dco < DCO_HS2_MAX)
                return SELFREQDCO_HS2;
        else if (clkout_dco >= DCO_HS1_MIN && clkout_dco < DCO_HS1_MAX)
                return SELFREQDCO_HS1;
        else
                return -1;
}




static void pll_config(unsigned int base, unsigned int n, unsigned int m, unsigned int m2,
                       unsigned int clkctrl_val, int adpllj)
{
        const struct ad_pll *adpll = (struct ad_pll *)base;
        unsigned int m2nval, mn2val, read_clkctrl = 0, clkout_dco = 0;
        unsigned int sig_val = 0, hs_mod = 0;

        m2nval = (m2 << ADPLLJ_M2NDIV_M2SHIFT) | n;
        mn2val = m;

        /* calculate clkout_dco */
        clkout_dco = ((OSC_0_FREQ / (n+1)) * m);

        /* sigma delta & Hs mode selection skip for ADPLLS*/
        if (adpllj) {
                sig_val = pll_sigma_delta_val(clkout_dco);
                hs_mod = pll_dco_freq_sel(clkout_dco);
        }

        /* by-pass pll */
        read_clkctrl = readl(&adpll->clkctrl);
        writel((read_clkctrl | ADPLLJ_CLKCTRL_IDLE), &adpll->clkctrl);
        while ((readl(&adpll->status) & ADPLLJ_STATUS_BYPASSANDACK)
                != ADPLLJ_STATUS_BYPASSANDACK)
                ;

        /* clear TINITZ */
        read_clkctrl = readl(&adpll->clkctrl);
        writel((read_clkctrl & ~ADPLLJ_CLKCTRL_TINITZ), &adpll->clkctrl);

        /*
         * ref_clk = 20/(n + 1);
         * clkout_dco = ref_clk * m;
         * clk_out = clkout_dco/m2;
        */
        read_clkctrl = readl(&adpll->clkctrl) &
                             ~(ADPLLJ_CLKCTRL_LPMODE |
                             ADPLLJ_CLKCTRL_DRIFTGUARDIAN |
                             ADPLLJ_CLKCTRL_REGM4XEN);
        writel(m2nval, &adpll->m2ndiv);
        writel(mn2val, &adpll->mn2div);

        /* Skip for modena(ADPLLS) */
        if (adpllj) {
                writel(sig_val, &adpll->fracdiv);
                 writel((read_clkctrl | hs_mod), &adpll->clkctrl);
         }
 
         /* Load M2, N2 dividers of ADPLL */
         writel(ADPLLJ_TENABLEDIV_ENB, &adpll->tenablediv);
         writel(~ADPLLJ_TENABLEDIV_ENB, &adpll->tenablediv);
 
         /* Load M, N dividers of ADPLL */
         writel(ADPLLJ_TENABLE_ENB, &adpll->tenable);
         writel(~ADPLLJ_TENABLE_ENB, &adpll->tenable);
 
         /* Configure CLKDCOLDOEN,CLKOUTLDOEN,CLKOUT Enable BITS */
         read_clkctrl = readl(&adpll->clkctrl) & ~ADPLLJ_CLKCTRL_CLKDCO;
         if (adpllj)
                 writel((read_clkctrl | ADPLLJ_CLKCTRL_CLKDCO),
                                                 &adpll->clkctrl);
 
         /* Enable TINTZ and disable IDLE(PLL in Active & Locked Mode */
         read_clkctrl = readl(&adpll->clkctrl) & ~ADPLLJ_CLKCTRL_IDLE;
         writel((read_clkctrl | ADPLLJ_CLKCTRL_TINITZ), &adpll->clkctrl);
 
         /* Wait for phase and freq lock */
         while ((readl(&adpll->status) & ADPLLJ_STATUS_PHSFRQLOCK) !=
                ADPLLJ_STATUS_PHSFRQLOCK);
 }
 


void ddr_pll_config(unsigned int ddrpll_m)
{
        pll_config(DDR_PLL_BASE, DDR_N, DDR_M, DDR_M2, DDR_CLKCTRL, 1);
}



/**
 * Configure DDR CMD control registers
 */
 void config_cmd_ctrl(const struct cmd_control *cmd, int nr)
 {
         if (!cmd)
                 return;
 
         writel(cmd->cmd0csratio, &ddr_cmd_reg[nr]->cm0csratio);
         writel(cmd->cmd0iclkout, &ddr_cmd_reg[nr]->cm0iclkout);
 
         writel(cmd->cmd1csratio, &ddr_cmd_reg[nr]->cm1csratio);
         writel(cmd->cmd1iclkout, &ddr_cmd_reg[nr]->cm1iclkout);
 
         writel(cmd->cmd2csratio, &ddr_cmd_reg[nr]->cm2csratio);
         writel(cmd->cmd2iclkout, &ddr_cmd_reg[nr]->cm2iclkout);
 }


/**
 * Configure DDR DATA registers
 */
void config_ddr_data(const struct ddr_data *data, int nr)
{
        int i;

        if (!data)
                 return;
 
         for (i = 0; i < DDR_DATA_REGS_NR; i++) {
                 writel(data->datardsratio0,
                         &(ddr_data_reg[nr]+i)->dt0rdsratio0);
                 writel(data->datawdsratio0,
                         &(ddr_data_reg[nr]+i)->dt0wdsratio0);
                 writel(data->datawiratio0,
                         &(ddr_data_reg[nr]+i)->dt0wiratio0);
                 writel(data->datagiratio0,
                         &(ddr_data_reg[nr]+i)->dt0giratio0);
                 writel(data->datafwsratio0,
                         &(ddr_data_reg[nr]+i)->dt0fwsratio0);
                 writel(data->datawrsratio0,
                         &(ddr_data_reg[nr]+i)->dt0wrsratio0);
         }
 }
 
void config_io_ctrl(const struct ctrl_ioregs *ioregs)
{
        if (!ioregs)
                return;

        writel(ioregs->cm0ioctl, &ioctrl_reg->cm0ioctl);
        writel(ioregs->cm1ioctl, &ioctrl_reg->cm1ioctl);
        writel(ioregs->cm2ioctl, &ioctrl_reg->cm2ioctl);
        writel(ioregs->dt0ioctl, &ioctrl_reg->dt0ioctl);
        writel(ioregs->dt1ioctl, &ioctrl_reg->dt1ioctl);
}

