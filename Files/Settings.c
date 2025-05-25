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




proc Settings.SetKeys, iKey
     cmp [iKey], 30
     je .IncSpeed
     cmp [iKey], 44
     je .DecSpeed
     cmp [iKey], 57
     je .GetPause
     cmp [iKey], 16
     je .AddBall
     cmp [iKey], 17
     je .DelBall

     ret
.IncSpeed:
     cmp [iPause], 0
     jne .end
     cmp [iStep], 15
     jge .end
     inc [iStep]
     ret
.DecSpeed:
     cmp [iPause], 0
     jne .end
     cmp [iStep], -15
     jle .end
     dec [iStep]
     ret
.GetPause:
     cmp [iPause], 0
     je .SaveStep
     mov ax, [iPause]
     mov [iStep], ax
     mov [iPause], 0
     ret
.SaveStep:
     mov ax, [iStep]
     mov [iPause], ax
     mov [iStep], 0
     ret
.AddBall:
     stdcall Settings.AddBall
     ret
.DelBall:
     cmp [iCounter], 0
     je .end
     dec [iCounter]
     ret

.end:
     ret
endp

proc Settings.Init uses es ax
        mov ax, cs
        add ax, 2000h
        mov es, ax
        mov bx, [iXCenter1]
        mov [es:$0000], bx
        mov bx, [iYCenter1]
        mov [es:$0002], bx
        mov bx, [iRadius1]
        mov [es:$0004],word  20
        mov bx, [iXStep1]
        mov [es:$0006], bx
        mov bx, [iYStep1]
        mov [es:$0008], bx
        mov bx, [iXCenter2]
        mov [es:$000A], bx
        mov bx, [iYCenter2]
        mov [es:$000C], bx
        mov bx, [iRadius2]
        mov [es:$000E], bx
        mov bx, [iXStep2]
        mov [es:$0010], bx
        mov bx, [iYStep2]
        mov [es:$0012], bx
        ret
endp




proc Settings.AddBall uses es ax dx bx
        mov ax, cs
        add ax, 2000h
        mov es, ax
        mov ax, [iCounter]
        mov bl, 10d
        mul bl
        mov bx, ax
        stdcall Random.GetNumber, 320d
        mov [es:bx], dx
        stdcall Random.GetNumber, 200d
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
