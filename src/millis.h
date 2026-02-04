#pragma once

extern volatile uint32_t systick_millis;

void systick_init();

uint32_t millis();
