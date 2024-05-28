.global memcpy, memset

/*
	void * memcpy(void *dst, void *src, size_t len);
*/
memcpy:
	push {r4}
	mov r4, r0
memcpy_loop:
	cmp r2, #0
	beq memcpy_end
	ldrb r3, [r1], #1
	strb r3, [r0], #1
	sub r2, r2, #1
	b memcpy_loop
memcpy_end:
	mov r0, r4
	pop {r4}
	bx lr

/*
	void * memset(void *dst, int c, size_t len);
*/
memset:
	mov r3, r0
memset_loop:
	cmp r2, #0
	beq memset_end
	strb r1, [r0], #1
	sub r2, r2, #1
	b memset_loop
memset_end:
	mov r0, r3
	bx lr

