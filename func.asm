global  func

section .data

color_B: equ     3
color_G: equ     7
color_R: equ     5

const_R     db 0x20 ;

section	.text

func:
	push    rbp
	mov	    rbp, rsp
	push    rbx
    ;RAX -> mul
    ;RBX = width counter
    ;RCX = height counter
    ;RDX =
    ;RDI = struct
    ;RSI = array
    ;R8W -> tmp counter
    cmp     RDI, 0 ;check if struct is null
    je      error
    cmp     RSI, 0 ;check if array is null
    je      error
;THIS IS BEGIN OF
    mov     RCX, QWORD [RDI+8]
loop_Y:
    mov     RBX, QWORD [RDI]
    cmp     RCX, 0
    je      fin
    dec     RCX
loop_X:
    cmp     RBX, 0
    je      loop_Y
    dec     RBX
prepare:
;TODO - load floats
compute:
;TODO - algorithm
    add     R8W, 1
;TODO - je prepare
save:
    mov     RAX, 0
    mov     AL, R8B
    mov     DL, color_B
    mul     DL
    mov     [RSI], AL
    inc     RSI
    mov     RAX, 0
    mov     AL, R8B
    mov     DL, color_G
    mul     DL
    mov     [RSI], AL
    inc     RSI
    mov     RAX, 0
    mov     AL, R8B
    mov     DL, color_R
    mul     DL
    mov     [RSI], AL
    inc     RSI
    jmp     loop_X
;THIS IS END OF
fin:
	mov     rax, 0
	pop     rbx
	pop	    rbp
	ret
error:
    mov     rax, 1
    pop     rbx
    pop     rbp
    ret
