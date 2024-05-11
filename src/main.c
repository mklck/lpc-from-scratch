#include <u.h>
#include <lpc213x.h>

typedef struct {
	u32 stopMask;
	u32 startMask;
} BitWalkPattern;

static void
delay(u32 d)
{
	for (; d; d--)
		;
}

static void
bitWalk(BitWalkPattern *p, u32 *bm)
{
	*bm &= p->stopMask;
	*bm = *bm? *bm << 1: p->startMask;
}

void
main(void)
{
	BitWalkPattern p = {
		.stopMask = 0xFF << 16,
		.startMask = 1 << 16
	};
	u32 bm = p.startMask;

	IO1DIR = 0xFF << 16;

	for (;;) {
		IO1CLR = IO1DIR;
		IO1SET = bm;
		bitWalk(&p, &bm);
		delay(20000);
	}


	return;
}
