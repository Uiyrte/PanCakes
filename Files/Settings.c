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





.end:
     ret
endp