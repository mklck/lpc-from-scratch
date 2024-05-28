
INCLUDE boot/regmap.ld;

SRAM_START  = 0x40000000;
SRAM_END    = 0x40008000;
SRAM_LENGTH = SRAM_END - SRAM_START;

MEMORY
{
	flash : ORIGIN = 0x0,        LENGTH = 256K
	sram  : ORIGIN = SRAM_START, LENGTH = SRAM_LENGTH
}

SECTIONS
{
	.text : 
	{
		*/crt.o(.text)
		*(.text)
		__text_end = .;
	} > flash

	
	.data :
	{
		__data_begin = .;
		*(.data)
		__data_end = .;
	} > sram AT > flash

	.bss :
	{
		__bss_begin = .;
		*(.bss)
		__bss_end = .;
	} > sram
}

__data_size = __data_end - __data_begin;
__bss_size  = __bss_end - __bss_begin;
