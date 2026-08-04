#include "clock.h"

static const struct rcc_pll_config rcc_hse_20mhz_400mhz = {
	.sysclock_source = RCC_PLL, // select which oscillator to use
	.pll_source = RCC_PLLCKSELR_PLLSRC_HSE, // select which oscillator to use as refernce
	.hse_frequency = 20000000, // identify which frequency the selected reference crystal runs at
	.pll1 = { // multiple/divide chain which feeds PLL1
		.divm = 4, // 20 / 4 = 5 mhz multiplier
		.divn = 160, // 5 * 160 = 800 mhz PLL internal VCO frequency
		.divp = 2, // 800 / 2 = 400mhz sysclk because sysclock_source is set to RCC_PLL
		.divq = 4, 
		.divr = 2,
	},
	.core_pre = RCC_D1CFGR_D1CPRE_BYP, // domain 1 core prescaler, byp because m7 core clock runs at full 400mhz
	.hpre     = RCC_D1CFGR_D1HPRE_DIV2, // divides core clock by 2 to bring HCLK down to its 200mhz max
	.ppre1    = RCC_D2CFGR_D2PPRE_DIV2, // APB1 prescaler
	.ppre2    = RCC_D2CFGR_D2PPRE_DIV2, // APB2 prescaler
	.ppre3    = RCC_D1CFGR_D1PPRE_DIV2, // APB3 prescaler, APB3 uses domain 1 unlike APB1 and APB2, hence D1CFGR
	.ppre4    = RCC_D3CFGR_D3PPRE_DIV2, // APB4 prescaler, APB4 uses domain 3
	.flash_waitstates = 4, // insert 4 wait states per flash access to insure memory read integrity
	.voltage_scale = PWR_VOS_SCALE_1, // configure internal voltage regulator's output level
	.power_mode = PWR_SYS_SCU_LDO, // select which power delivery path to use
};

void configure_system_clock(void){ // set internal clock to 180mhz
	rcc_clock_setup_pll(&rcc_hse_20mhz_400mhz);
}
