proc Balls.SetPosition uses ax cx bx
        mov cx, [iCounter]
        mov ax, cs
        add ax, 2000h
        mov es, ax
        mov bx, 0
.TestXCenter11:
        cmp [es:bx], word 0
        jge .TestXCenter12
        neg word [es:bx + 6]
        mov [es:bx],word 0
.TestXCenter12:
        cmp [es:bx], word 320
        jle .TestYCenter11
        neg word [es:bx + 6]
        mov [es:bx], word 320
.TestYCenter11:
        cmp [es:bx + 2], word 0
        jge .TestYCenter12
        neg word [es:bx + 8]
        mov [es:bx + 2], word 0
.TestYCenter12:
        cmp [es:bx + 2], word 200
        jle .Change
        neg word [es:bx + 8]
        mov [es:bx + 2], word 200
.Change:

        mov ax, [es:bx + 6]
         imul ax, [iStep]
        add [es:bx], ax
        mov ax, [es:bx + 8]
         imul ax, [iStep]
        add [es:bx+2], ax
        add bx,10
        loop .TestXCenter11
        stdcall Screen.DrawBalls
        ret
endp



proc Balls.CalcPixelColor uses cx es bp bx,\
     iY, iX
     cmp [iCounter], 0
     jne .Calc
     mov ax, [iColorBackground]
     ret
.Calc:
     mov cx, [iCounter]
     mov [fResult],0
     mov ax, cs
     add ax, 2000h
     mov es, ax
     mov bx, 0
lg:
     finit
     fild word [iX]
     fisub word [es:bx]
     fmul st0, st0
     fild word [iY]
     fisub word [es:bx+2]
     fmul st0, st0
     fadd st0, st1
     fsqrt
     fild word [es:bx+4]
     add bx, 10
     fdiv st0, st1
     fld dword [fResult]
     fadd st0, st1
     fstp dword [fResult]
     loop lg
     fld dword [fResult]
     fld1
     fxch st1
     fcomip st1
     jbe  .BackgroundPixel
     mov ax, [iColorBall]
     ret

.BackgroundPixel:
     mov ax, [iColorBackground]
     ret

     fResult dd ?
endp