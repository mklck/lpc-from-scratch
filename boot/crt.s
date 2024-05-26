
mode_usr = 0b10000
mode_irq = 0b10010

IRQ_STACK  = SRAM_END
USER_STACK = (IRQ_STACK - 32)

reset:          b _start
invalid_op:     b .
siq:            b .
prefetch_abort: b .
data_abort:     b .
reserved:       nop
irq:            b irq_handler
fiq:            b .

_start:
	ldr r0, =USER_STACK
	ldr r1, =IRQ_STACK
	msr CPSR_c, #mode_irq
	mov sp, r1
	msr CPSR_c, #mode_usr
	mov sp, r0
	bl main
	b .

irq_handler:
	push {r0}
	ldr r0, =VICVectAddr
	mov lr, pc
	ldr pc, [r0] // run ISR

	ldr r0, =VICVectAddr
	str r0, [r0]

	pop {r0}
	mrs lr, SPSR
	msr CPSR, lr
	sub pc, lr, #4
