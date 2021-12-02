global outb
global inb
global insd

;void outb(unsigned short port, unsigned char data)
outb:
    push ebp
    mov ebp, esp

    mov dx, [ebp-6] ;dx = port
    mov al, [ebp-7] ;al = data

    out dx, al ;data -> port

    pop ebp
    ret

;unsigned char inb(unsigned short port)
inb:
    push ebp
    mov ebp, esp

    mov dx, [ebp-6] ;dx = port

    in al, dx ;port -> al

    pop ebp
    ret

;void insd(unsigned short port, unsigned int* dest, unsigned int count)
insd:
    push ebp
    push edi
    mov ebp, esp

    mov dx,  [ebp-10] ;dx = port
    mov edi, [ebp-14] ;edi = dest
    mov ecx, [ebp-18] ;ecx = count

    rep insd

    pop edi
    pop ebp
    ret
