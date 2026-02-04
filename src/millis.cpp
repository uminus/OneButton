#include "ch32fun.h"
#include "millis.h"

volatile uint32_t systick_millis;

uint32_t millis() {
    return systick_millis;
}

void systick_init() {
    SysTick->CTLR = 0x0000;
    SysTick->CMP = DELAY_MS_TIME - 1;
    SysTick->CNT = 0x00000000;
    systick_millis = 0x00000000;
    SysTick->CTLR |= SYSTICK_CTLR_STE |
            SYSTICK_CTLR_STIE;
    // SYSTICK_CTLR_STCLK ;  // Set Clock Source to HCLK/1
    NVIC_EnableIRQ(SysTicK_IRQn);
}

extern "C" {
    void SysTick_Handler(void) __attribute__((interrupt));

    void SysTick_Handler(void) {
        SysTick->CMP += DELAY_MS_TIME;
        SysTick->SR = 0x00000000;
        systick_millis++;
    }
}
