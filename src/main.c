#include <u.h>
#include <string.h>
#include <lpc213x.h>

#include <timer.h>

typedef struct {
	bool on;
	int  nr;
	u32  delay;
} LedPattern;

static IrqFn timerHandle;
static LedPattern pattern[] = {
	{true,  2, 100},
	{true,  3, 500},
	{false, 3, 700},
	{false, 2, 700}
};
static u32 patternIdx = 0;

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
timerHandle(void)
{
	LedPattern p;

	p = pattern[patternIdx];
	patternIdx = (patternIdx+1) % LEN(pattern);

	setLed(p.nr, p.on);
	setTimerInt(p.delay);;
	setTimerISR(timerHandle);
}

void
main(void)
{
	bool led = false;

	init();
	timerHandle();

	for(;;) {
		setLed(7, led);
		led = !led;
		delay(20e3);
	}

	return;
}
