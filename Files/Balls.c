proc Balls.SetPosition
        mov cx, [iCounter]
        mov ax, cs
        add ax, 2000h
        mov es, ax
        xor bx, bx
.TestXCenter11:
        mov ax, [es:bx+4]
        cmp [es:bx], word ax
        jge .TestXCenter12
        neg word [es:bx + 6]
        mov [es:bx],word ax
.TestXCenter12:
        mov dx, 319
        sub dx, ax
        cmp [es:bx], word dx
        jle .TestYCenter11
        neg word [es:bx + 6]
        mov [es:bx], word dx
.TestYCenter11:
        cmp [es:bx + 2], word ax
        jge .TestYCenter12
        neg word [es:bx + 8]
        mov [es:bx + 2], word ax
.TestYCenter12:
        mov dx, 200
        sub dx, ax
        cmp [es:bx + 2], word dx
        jle .Change
        neg word [es:bx + 8]
        mov [es:bx + 2], word dx
.Change:

        mov ax, [es:bx + 6]
        imul byte [iStep]
        add [es:bx], ax
        mov ax, [es:bx + 8]
        imul byte [iStep]
        add [es:bx+2], ax
        add bx,10
        loop .TestXCenter11

        stdcall Screen.DrawBalls
        ret
endp



proc Balls.CalcPixelColor uses cx es,\
     iY, iX
     cmp [iCounter], 0
     jne .Calc
     mov ax, 0 ; Цвет фона, убрал константу для уменьшения занимаемой памяти
     ret
.Calc:
     mov cx, [iCounter]
     and [fResult],0
     mov ax, cs
     add ax, 2000h
     mov es, ax
     xor bx, bx
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
     fcomip st1
     jae  .BackgroundPixel
     mov ax, [iColorBall]
     jmp .end

.BackgroundPixel:
     mov ax, 0 ; Цвет фона, убрал константу для уменьшения занимаемой памяти
.end:
     ret

     fResult dd ?
endp


proc Balls.CalcCurrentPixel uses es
        mov ax, cs
        add ax, 2000h
        mov es, ax
        imul bx, [iCurrentBall], 10d
        mov ax, [es:bx+2]
        mov bx, [es:bx]
        dec ax
        imul ax, ax, 20
        add ax, 1000h
        mov cx, cs
        add ax, cx
        mov es, ax
        mov [es:bx], byte 28h
        add ax, 20
        mov es, ax
        mov [es:bx-1], byte 28h
        mov [es:bx], byte 28h
        mov [es:bx+1], byte 28h
        add ax, 20
        mov es, ax
        mov [es:bx], byte 28h
        ret
endp





proc    Balls.Resize,\
        iKey
        mov ax, cs
        add ax, 2000h
        mov es, ax
        imul bx, [iCurrentBall], 10d
        cmp byte [iKey+1], 80
        je .Rem

.Add:
        inc word [es:bx+4]
        jmp .end
.Rem:
        cmp word [es:bx+4], 2
        je .end
        dec word [es:bx+4]
.end:
        ret
endp


























