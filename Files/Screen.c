proc Screen.DrawBalls uses es di bp cx bx ds
        mov ax, cs
        add ax, 1000h
        mov es, ax
        mov cx, 64000
        mov bx, 0
.DrawLoop:
        mov ax, bx
        mov dx, 0
        push bx
        mov bx, 320
        div bx
        stdcall Balls.CalcPixelColor, ax, dx
        pop bx
        mov [es:bx], al
        inc bx
        loop .DrawLoop
        mov cx, 64000
        push es
        pop ds
        push $a000
        pop es
        mov di, 0
        mov si, 0
        rep movsb
        ret
endp




proc Balls.CalcPixelColor\
     iY, iX
     finit
     fild word [iX]
     fisub word  [iXCenter1]
     fmul st0, st0
     fild word [iY]
     fisub word [iYCenter1]
     fmul st0, st0
     fadd st0, st1
     fsqrt
     fild word [iRadius1]
     fdiv st0, st1
     fstp dword [fTempResult]
     fild word [iX]
     fisub word [iXCenter2]
     fmul st0, st0
     fild word [iY]
     fisub word [iYCenter2]
     fmul st0, st0
     fadd st0, st1
     fsqrt
     fild word [iRadius2]
     fdiv st0, st1
     fld dword [fTempResult]
     fadd st0, st1
     fld1
     fxch st1
     fcomip st1
     jbe  .BackgroundPixel
     mov ax, [iColorBall]
     ret

.BackgroundPixel:
     mov ax, [iColorBackground]
     ret

     fTempResult dd ?
endp





