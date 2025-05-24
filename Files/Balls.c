proc Balls.SetPosition uses ax
.TestXCenter11:
        cmp [iXCenter1], 0
        jge .TestXCenter12
        neg [iXStep1]
        mov [iXCenter1], 0
.TestXCenter12:
        cmp [iXCenter1], 320
        jle .TestYCenter11
        neg [iXStep1]
        mov [iXCenter1], 320
.TestYCenter11:
        cmp [iYCenter1], 0
        jge .TestYCenter12
        neg [iYStep1]
        mov [iYCenter1], 0
.TestYCenter12:
        cmp [iYCenter1], 200
        jle .TestXCenter21
        neg [iYStep1]
        mov [iYCenter1], 200
.TestXCenter21:
        cmp [iXCenter2], 0
        jge .TestXCenter22
        neg [iXStep2]
        mov [iXCenter2], 0
.TestXCenter22:
        cmp [iXCenter2], 320
        jle .TestYCenter21
        neg [iXStep2]
        mov [iXCenter2], 320
.TestYCenter21:
        cmp [iYCenter2], 0
        jge .TestYCenter22
        neg [iYStep2]
        mov [iYCenter2], 0
.TestYCenter22:
        cmp [iYCenter2], 200
        jle .Change
        neg [iYStep2]
        mov [iYCenter2], 200
.Change:
        mov ax, [iXStep1]
         imul ax, [iStep]
        add [iXCenter1], ax
        mov ax, [iXStep2]
         imul ax, [iStep]
        add [iXCenter2], ax
        mov ax, [iYStep1]
         imul ax, [iStep]
        add [iYCenter1], ax
        mov ax, [iYStep2]
         imul ax, [iStep]
        add [iYCenter2], ax
        stdcall Screen.DrawBalls
        ret
endp



