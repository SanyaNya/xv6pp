global outb
global inb
global insd
global insd_skip

;void outb(unsigned short port, unsigned char data)
outb:
    push ebp
    mov ebp, esp

    mov dx, [ebp+6] ;dx = port
    mov al, [ebp+7] ;al = data

    out dx, al ;data -> port

    pop ebp
    ret

;unsigned char inb(unsigned short port)
inb:
    push ebp
    mov ebp, esp

    mov dx, [ebp+6] ;dx = port

    in al, dx ;port -> al

    pop ebp
    ret

;void insd(unsigned short port, unsigned int* dest, unsigned int count)
insd:
    push ebp
    push edi
    mov ebp, esp

    mov dx,  [ebp+10] ;dx = port
    mov edi, [ebp+14] ;edi = dest
    mov ecx, [ebp+18] ;ecx = count

    rep insd

    pop edi
    pop ebp
    ret

;void insd_skip(unsigned short port, unsigned int count)
; ebp+12 | count |
; ebp+10 | port  |
; ebp+6  | ebp   |
; ebp+2  | edi   | <- esp
; ebp+0  | trash |
insd_skip:
    push ebp
    push edi
    mov ebp, esp
    mov edi, ebp ;edi = &trash
    sub ebp, 2   ;unsigned short trash;
    
    mov  dx, [ebp+10] ;dx = port
    mov ecx, [ebp+12] ;ecx = count

    loop_label:
        insd ;dx -> edi
        sub edi, 2
        loop loop_label

    pop edi
    pop ebp
    ret
