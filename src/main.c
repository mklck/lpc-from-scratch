#include <u.h>
#include <lpc213x.h>

#include <timer.h>

static IrqFn timerHandle1, timerHandle2;

static void
delay(u32 d)
{
	for (; d; d--)
		;
}

static void
init(void)
{
	IO1DIR = 0xFF << 16;
	IO1CLR = IO1DIR;
	timerInit();
}

static void
setLed(int nr, bool on)
{
	Port *p;
	p = (on? &IO1SET : &IO1CLR);
	*p = 1 << (nr + 16);
}

static void
timerHandle2(void)
{
	setLed(0, false);
	setTimerInt(750);
	setTimerISR(timerHandle1);
}

static void
timerHandle1(void)
{
	setLed(0, true);
	setTimerInt(250);
	setTimerISR(timerHandle2);
}

void
main(void)
{
	bool led = false;

	init();
	setTimerInt(500);
	setTimerISR(timerHandle1);

	for(;;) {
		if (led)
			IO1SET = 1 << 23;
		else
			IO1CLR = 1 << 23;
		led = !led;
		delay(20e3);
	}

	return;
}
