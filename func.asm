global  func

section .data

color_B: equ     1
color_G: equ     4
color_R: equ     2

align 32
CONST   DQ 0.66 , 0.012
DOUBLE_RADIUS    DQ 3.0
STEP    DQ 0.002
BEGIN   DQ -0.90
BEGIN_M   DQ -0.90
NEGATE      DQ 0x8000000000000000
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
;ASSUMING STRUCT IS VALID
    xorpd   xmm14, xmm14
    xorpd   xmm15, xmm15
    movlpd  xmm14, [STEP];[RDI+24] ;load Immaginary step
    movhpd  xmm15, [STEP];[RDI+16] ;load Real step
    movapd  xmm4, [CONST]
    xorpd   xmm13, xmm13
    movlpd  xmm13, [BEGIN];[RDI+40] ;load starting position
    movhpd  xmm13, [BEGIN_M];[RDI+32]
;THIS IS BEGIN OF
    mov     RCX, QWORD [RDI+8] ;load resolution on Y
loop_Y:
    mov     RBX, QWORD [RDI] ;load resolution on X
    movhpd  xmm13, [BEGIN_M];[RDI+32] ;load begin of the line
    cmp     RCX, 0
    je      fin
    addpd   xmm13, xmm14 ;move to the next line
    dec     RCX
loop_X:
    cmp     RBX, 0
    je      loop_Y
    addpd   xmm13, xmm15 ;move to next pixel in line
    dec     RBX
prepare:
    mov     R8W, 0
    movapd  xmm0, xmm13 ;load the pixel
    movapd  xmm1, xmm0
    mulpd   xmm1, xmm1 ;   Re^2  |  Im^2
compute:
    ;calc new Z
    movhlps xmm2, xmm0 ;  ?????  |   Re
    mulsd   xmm2, xmm0 ;  ?????  |  Re*Im
    movapd  xmm3, xmm1 ;   Re^2  |  Im^2
    movsd   xmm3, xmm2 ;   Re^2  |  Re*Im
    movlhps xmm2, xmm1 ;   Im^2  |  Re*Im
    xorps   xmm0, xmm0 ;
    movhpd  xmm0, [NEGATE] ;Is there a easier way to negate?
    xorpd   xmm2, xmm0 ;  -Im^2  |  Re*Im
    addpd   xmm2, xmm3 ;Re^2+Im^2| 2*Re*Im - aka New:Re|New:Im
    ;TODO: add CONST from register xmm4
    addpd   xmm2, xmm4
    movapd  xmm0, xmm2 ; save new computed Z !
    movapd  xmm1, xmm0 ;   Re    |   Im
    mulpd   xmm1, xmm1 ;   Re^2  |  Im^2

    movhlps xmm2, xmm1 ; ??????? |  Re^2
    addsd   xmm2, xmm1 ; ??????? |Re^2+Im^2
    add     R8W, 1
    cmp     R8, 550
    jge     save
    comisd  xmm2, [DOUBLE_RADIUS];[RDI+48]
    jb      compute

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
