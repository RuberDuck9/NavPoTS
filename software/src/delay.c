#include "delay.h"

static volatile uint32_t clock_ms = 0;

void sys_tick_handler(void){
	clock_ms++;
}

void configure_systick(void){
	uint32_t cpu_freq = rcc_get_bus_clk_freq(RCC_CPUCLK);
	systick_set_frequency(1000, cpu_freq);
	systick_counter_enable();
	systick_interrupt_enable();
}

void delay(uint32_t delay_ms){
	uint32_t start_ms = clock_ms;
	while ( (clock_ms - start_ms) < delay_ms){
		__asm__("nop");
	}
}
