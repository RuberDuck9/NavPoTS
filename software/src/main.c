#include "io.h"

int main(void){

	set_pin(RCC_GPIOE, GPIOE, GPIO14);
	
	for (int i = 0; i < 999999999; i++){
		__asm__("nop");
	}

	clear_pin(RCC_GPIOE, GPIOE, GPIO15);

	return 0;
}
