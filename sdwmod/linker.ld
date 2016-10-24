OUTPUT_FORMAT(elf32-littlearm)
ENTRY(default)

SECTIONS
{
	. = 0x00000000;
	. = ALIGN(4);
	.text : {
	    start = .;
	    *main.S.o(.main)
	}
	. = ALIGN(4);
	.text : {
		text = .;
		*(.text);
	}
	. = ALIGN(4);
	.text : {
		rodata = .;
		*(.rodata);
	}
	. = ALIGN(4);
	.text :	{
		data = .;
		*(.data)
	}
	. = ALIGN(4);
	.text : {
		bss = .;
		*(.bss);
	}
	.text : {
		. = ALIGN(4);
		got = .;
		*(.gen_got_start*)
		*(.got*)
		*(.gen_got_end*)
	}
	. = ALIGN(4);
	.text : {
		LC0 = .;
		*(.LC0);
	}
	. = ALIGN(4);
	.text : {
		*end.S.o(.end)
	}
	/DISCARD/ : {
		*(.ARM.attributes);
		*(.comment);
	}
		
}
