%define CR_PM_ON 0x1

%define PM_CS (1 << 3)
%define PM_DS (2 << 3)

bits 16

section .start

global start
extern gdtdesc
extern bootmain

start:
    cli ;disable interrupts

    ;switch to protected mode
    lgdt [gdtdesc]
    mov eax, cr0
    inc ax ;or eax, CR_PM_ON
    mov cr0, eax

    jmp PM_CS:pm_start

bits 32

pm_start:
    ;set segment regs to ds
    mov ax, PM_DS
    mov ds, ax
    mov es, ax
    mov ss, ax

    mov esp, start
    jmp bootmain
