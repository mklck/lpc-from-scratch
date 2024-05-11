
INCLUDE boot/regmap.ld;

SRAM_START = 0x40000000;
SRAM_END   = 0x40008000;

SECTIONS
{
	.text : { */crt.o(.text) }
	.text : { *(.text) }
	.data : { *(.data) }
	.bss  : { *(.bss) }
}
