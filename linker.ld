ENTRY(kernel_entry)

SECTIONS
{
	. = 1M;
	
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
	
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
	
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
	
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
	
	.comment BLOCK(4K) : ALIGN(4K)
	{
		*(.comment)
	}
}