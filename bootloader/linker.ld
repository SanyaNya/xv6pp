ENTRY(start)
OUTPUT_FORMAT("binary")
SECTIONS {
    . = 0x7c00;
    .text :
    {
        *(.start)
        *(.text)
    }
    .rodata :
    {
        *(.rodata)
    }
    .data :
    {
        *(.data)
    }
    .bss :
    {
        *(.bss)
    }

    . = 0x7dfe;
    .bootmagic : 
    {
        BYTE(0x55);
        BYTE(0xaa);
    }
}
