proc Screen.DrawBalls
        mov ax, cs
        add ax, 1000h
        mov es, ax
        mov cx, 64000
        push cx
        xor bx, bx
.DrawLoop:
        mov ax, bx
        xor dx, dx
        push bx
        mov bx, 320
        div bx
        stdcall Balls.CalcPixelColor, ax, dx
        pop bx
        mov [es:bx], al
        inc bx
        loop .DrawLoop
        cmp [iResize], 0
        je .Resize
        cmp [iCounter], 0
        je .Resize
        stdcall Balls.CalcCurrentPixel

.Resize:
        cmp [iColorMode], 0
        je .Res
        stdcall Settings.SetColor
.Res:
        pop cx
        push es
        pop ds
        push $a000
        pop es
        xor di, di
        xor si, si
        rep movsb
        ret
endp











