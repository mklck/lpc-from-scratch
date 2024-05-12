#include <u.h>
#include <lpc213x.h>

#include <timer.h>

#define RESET_BM  0b10
#define ENABLE_BM 0b01

#define MCU_FREQ 16e6

void
timerInit(void)
{
	T0TCR = RESET_BM;
	T0PR   = MCU_FREQ / 4e3;
}

void
timerSet(u32 ms)
{
	T0MR0  = ms;
	T0MCR  = 0b100;
	T0TCR  = RESET_BM;
	T0TCR  = ENABLE_BM;
}

void
wait(void)
{
	while (T0TCR & ENABLE_BM)
		;
}
