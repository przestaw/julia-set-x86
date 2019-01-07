global  gen_Julia

section .data

color_B: equ     3
color_G: equ     8
color_R: equ     4

align 32
NEGATE      DQ 0x8000000000000000
ZERO    DQ 0.0
section	.text

gen_Julia:
	push    EBP
	mov	    EBP, ESP
    ;EAX -> mul
    ;EBX = width counter
    ;ECX = height counter
    ;EDX =
    ;EDI = struct
    ;ESI = array
    ;EDXW -> tmp counter
    ;R9W -> deepnes
    mov     EDI, DWORD [EBP+8]
    mov     ESI, DWORD [EBP+12]
    cmp     EDI, 0              ;check if struct is null
    je      error
    cmp     ESI, 0              ;check if array is null
    je      error
;ASSUMING STRUCT IS VALID
    xorpd   xmm6, xmm6
    xorpd   xmm7, xmm7
    movapd  xmm7, [EDI+16]
    movsd   xmm6, xmm7        ;load Immaginary step
    movlps  xmm7, [ZERO]       ;load Real step
    movapd  xmm4 , [EDI+48]     ;load Const
    xorpd   xmm5, xmm5
    movapd  xmm5, [EDI+32]
    ;movsd   xmm12, [EDI+64]
    ;mov     R9   , [EDI+72]
;THIS IS BEGIN OF
    mov     ECX, DWORD [EDI+8]  ;load resolution on Y
loop_Y:
    mov     EBX, DWORD [EDI]    ;load resolution on X
    movsd   xmm0, xmm5
    movapd  xmm5, [EDI+32]
    movsd   xmm5, xmm0
    cmp     ECX, 0
    je      fin
    addpd   xmm5, xmm6        ;move to the next line
    dec     ECX
loop_X:
    cmp     EBX, 0
    je      loop_Y
    addpd   xmm5, xmm7        ;move to next pixel in line
    dec     EBX
prepare:
    mov     EDX, 0
    movapd  xmm0, xmm5         ;load the pixel
    movapd  xmm1, xmm0
    mulpd   xmm1, xmm1          ;   Re^2  |  Im^2
compute:
    ;calc new Z
    movhlps xmm2, xmm0          ;  ?????  |   Re
    mulsd   xmm2, xmm0          ;  ?????  |  Re*Im
    movapd  xmm3, xmm1          ;   Re^2  |  Im^2
    movsd   xmm3, xmm2          ;   Re^2  |  Re*Im
    movlhps xmm2, xmm1          ;   Im^2  |  Re*Im
    xorps   xmm0, xmm0          ;
    movhpd  xmm0, [NEGATE]      ;Is there a easier way to negate?
    xorpd   xmm2, xmm0          ;  -Im^2  |  Re*Im
    addpd   xmm2, xmm3          ;Re^2+Im^2| 2*Re*Im - aka New:Re|New:Im
    addpd   xmm2, xmm4          ; constant
    movapd  xmm0, xmm2          ; save new computed Z !
    movapd  xmm1, xmm0          ;   Re    |   Im
    mulpd   xmm1, xmm1          ;   Re^2  |  Im^2

    movhlps xmm2, xmm1          ; ??????? |  Re^2
    addsd   xmm2, xmm1          ; ??????? |Re^2+Im^2
    add     EDX, 1
    cmp     EDX, [EDI+72]
    jge     save
    comisd  xmm2, [EDI+64]      ; RADIUS
    jb      compute
save:
    push    ECX                 ;TMEP STORE
    mov     ECX, EDX
    mov     EAX, 0
    mov     AL, CL
    mov     DL, color_B
    mul     DL
    mov     [ESI], AL
    inc     ESI
    mov     EAX, 0
    mov     AL, CL
    mov     DL, color_G
    mul     DL
    mov     [ESI], AL
    inc     ESI
    mov     EAX, 0
    mov     AL, CL
    mov     DL, color_R
    mul     DL
    mov     [ESI], AL
    inc     ESI
    mov     AL, 255
    mov     [ESI], AL           ;alpha
    inc     ESI
    pop     ECX                 ;END TMP STORE
    jmp     loop_X
;THIS IS END OF
fin:
	mov     eax, 0
	pop	    ebp
	ret
error:
    mov     eax, 1
    pop     ebp
    ret
