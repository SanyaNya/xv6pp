bits 16

%define KBRD_PORT1 0x64
%define KBRD_PORT2 0x60

%define CR_PM_ON 0x1

%define PM_CS (gdt_cs_sel - gdt)
%define PM_DS (gdt_ds_sel - gdt)

%define SEG_NULL dq 0x0
%macro SEG 3;(type,base,lim)
    dw (((%3) >> 12) & 0xffff), ((%2) & 0xffff)
    db (((%2) >> 16) & 0xff), (0x90 | (%1)), (0xc0 | (((%3) >> 28) & 0xf)), (((%2) >> 24) & 0xff)
%endmacro

%define STA_A   0x1 ;Accessed
%define STA_RE  0x2 ;Readable(exec)
%define STA_WNE 0x2 ;Writable(non exec)
%define STA_CE  0x4 ;Conforming code segment(exec only)
%define STA_ENE 0x4 ;Expand down(non exec)
%define STA_X   0x8 ;Exec seg

org 0x7c00

start:
    cli ;disable interrupts

    ;clear ds, es, ss
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax

    ;enable 21th address line
    set_a20_1:
        in al, KBRD_PORT1
        test al, 0x2
        jnz set_a20_1

    mov al, 0xd1
    out 0x64, al

    set_a20_2:
        in al, KBRD_PORT1
        test al, 0x2
        jnz set_a20_2

    mov al, 0xdf
    out 0x60, al

    ;switch to protected mode
    lgdt [gdtdesc]
    mov eax, cr0
    or eax, CR_PM_ON
    mov cr0, eax

    jmp PM_CS:pm_start

bits 32

pm_start:
    ;set segment regs to cs
    mov ax, PM_DS
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ;call cpp_main
    mov esi, msg
    mov ebx, 0xb8000
    print_loop:
        lodsb
        or al,al
        jz inf_loop
        or eax,0x0200
        mov word [ebx], ax
        add ebx,2
        jmp print_loop

;if cpp_main fails then infinite loop
inf_loop: jmp inf_loop

align 4
gdt:
    SEG_NULL                           ;null seg
    gdt_cs_sel: SEG STA_X|STA_RE, 0x0, 0xffffffff ;code seg
    gdt_ds_sel: SEG STA_WNE, 0x0, 0xffffffff      ;data seg
gdt_end:


gdtdesc:
    dw (gdt_end-gdt)
    dd gdt

msg: db "Hello Fluffer (UwU)", 0
msg_len: equ $-msg

times 510 - ($-$$) db 0 ; pad remaining 510 bytes with zeroes
dw 0xaa55 ; magic bootloader magic - marks this 512 byte sector bootable!
