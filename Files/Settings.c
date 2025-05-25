proc Settings.SetScreenMode uses bx,\
     wMode
        mov     ah, 0fh
        int     10h
        mov     bl, al

        movzx   ax, byte [wMode]
        int     10h
        mov     ah, 05h
        mov     al, byte [wMode + 1]
        int     10h
        xchg    ax, bx
        ret
endp




Settings.SetKeys:
     cmp ah, 30
     je .IncSpeed
     cmp ah, 44
     je .DecSpeed
     cmp ah, 45
     je .Color
     cmp ah, 46
     je .BaseColor
     cmp ah, 47
     je .Garl
     cmp ah, 57
     je .GetPause
     cmp ah, 16
     je .AddBall
     cmp ah, 17
     je .DelBall
     cmp ah, 18
     je .OnResize
     cmp ah, 75
     je .PrevBall
     cmp ah, 77
     je .NextBall
     cmp ah, 72
     je .Resize
     cmp ah, 80
     je .Resize



     jmp .end
.IncSpeed:
     cmp [iPause], 0
     jne .end
     cmp [iStep], 15
     jge .end
     inc [iStep]
     jmp .end
.DecSpeed:
     cmp [iPause], 0
     jne .end
     cmp [iStep], -15
     jle .end
     dec [iStep]
     jmp .end
.GetPause:
     cmp [iPause], 0
     je .SaveStep
     mov al, [iPause]
     mov [iStep], al
     and [iPause], 0
     jmp .end
.SaveStep:
     mov al, [iStep]
     mov [iPause], al
     and [iStep], 0
     jmp .end
.AddBall:
     stdcall Settings.AddBall
     jmp .end
.DelBall:
     cmp [iCounter], 0
     je .end
     mov ax, [iCurrentBall]
     inc ax
     cmp ax, [iCounter]
     jne .DelNotCurr
     cmp [iCurrentBall], 0
     je .DelNotCurr
     dec [iCurrentBall]
.DelNotCurr:
     dec [iCounter]
     jmp .end
.OnResize:
     xor [iResize], 1
     and [iCurrentBall], 0
     jmp .end
.PrevBall:
     cmp [iCurrentBall], 0
     je .FromZeroBall
     dec [iCurrentBall]
     jmp .end
.FromZeroBall:
     mov ax, [iCounter]
     dec ax
     mov [iCurrentBall], ax
     jmp .end
.NextBall:
     mov ax, [iCounter]
     dec ax
     cmp [iCurrentBall], ax
     je .ToZeroBall
     inc [iCurrentBall]
     jmp .end
.ToZeroBall:
     and [iCurrentBall], 0
     jmp .end
.Resize:
     cmp [iResize], 0
     je .end
     stdcall Balls.Resize, ax
     jmp .end
.Color:
     stdcall Settings.SetColor
     and [iColorMode], 0
     jmp .end
.BaseColor:
     mov [iColorBall], 64
     and [iColorMode], 0
     jmp .end
.Garl:
     xor [iColorMode], 1
.end:
     ret




proc Settings.AddBall
        mov ax, cs
        add ax, 2000h
        mov es, ax
        imul bx, [iCounter], 10d
        stdcall Random.GetNumber, 300d
        add dx, 10
        mov [es:bx], dx
        stdcall Random.GetNumber, 180d
        add dx, 10
        mov [es:bx+2], dx
        stdcall Random.GetNumber, 5d
        add dx, 5
        mov [es:bx+4], dx
        stdcall Random.GetNumber, 2d
        test dx, dx
        je .XStep
        mov [es:bx+6],word 1
        jmp .Step
.XStep:
        mov [es:bx+6], word  -1
.Step:
        stdcall Random.GetNumber, 2d
        test dx, dx
        je .YStep
        mov [es:bx+8],word 1
        jmp .End
.YStep:
        mov [es:bx+8], word  -1
.End:
        inc [iCounter]
        ret
endp





proc Settings.SetColor
        cmp [iColorBall], 104
        jne .end
        mov [iColorBall], 32

.end:
        inc [iColorBall]
        ret
endp
