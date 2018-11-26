#include "stm32f1xx_hal_delay.h"

void DelayUs(uint32_t us){
	uint16_t  t0 = TIM2->CNT;
	for (;;) {
		int  t = TIM2->CNT;
		if (t < t0)
			t += 0x10000;

		if (us < t - t0)
			return;

		us -= t - t0;
		t0  = t;
	}
}

void DelayMs(uint32_t ms){
	DelayUs(ms * 1000);
}

void DelayInit(void){
    __HAL_RCC_TIM2_CLK_ENABLE();
    TIM2->PSC = (HAL_RCC_GetPCLK2Freq() / 1000000) - 1;
    TIM2->ARR = 0xFFFF;
    TIM2->CR1 = TIM_CR1_CEN;
}

