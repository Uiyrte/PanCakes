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











