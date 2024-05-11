reset:          b _start
invalid_op:     b .
siq:            b .
prefetch_abort: b .
data_abort:     b .
reserved:       nop
irq:            b .
fiq:            b .

_start:
	ldr sp, =SRAM_END
	bl main
	b .
