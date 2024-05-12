#include <u.h>
#include <lpc213x.h>

#include <timer.h>

typedef struct {
	u32 stopMask;
	u32 startMask;
} BitWalkPattern;

static void
bitWalk(BitWalkPattern *p, u32 *bm)
{
	*bm &= p->stopMask;
	*bm = *bm? *bm << 1: p->startMask;
}

static void
init(void)
{
	IO1DIR = 0xFF << 16;
	timerInit();
}

void
main(void)
{
	BitWalkPattern p = {
		.stopMask = 0xFF << 16,
		.startMask = 1 << 16
	};
	u32 bm = p.startMask;

	init();

	for (;;) {
		IO1CLR = IO1DIR;
		IO1SET = bm;
		bitWalk(&p, &bm);
		timerSet(1000);
		wait();
	}

	return;
}
