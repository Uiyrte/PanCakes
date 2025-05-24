        include 'macro/proc16.inc'

        org 100h

Start:
        stdcall Settings.SetScreenMode, $0013

        push ax

        cli
        push    0
        pop     es
        mov     ax, [es:20h]
        push    ax
        mov     ax, [es:22h]
        push    ax
        mov     [es:22h], cs
        mov     word [es:20h], lbl
        sti




lp:
        mov     ah, 00h
        int     16h
        movzx bx, ah
        stdcall Settings.SetKeys, bx
        cmp     ah, 1
        jne     lp



        cli
        push    0
        pop     es
        pop     ax
        mov     [es:22h], ax
        pop     ax
        mov     [es:20h], ax
        sti

        stdcall Settings.SetScreenMode
        ret





 lbl:
     pusha
     push ds
     mov ax, cs
     mov ds, ax
     stdcall Balls.SetPosition
     pop ds
     popa
     mov al, 20h
     out 20h, al
     iret



        include 'Files/Screen.c'
        include 'Files/Settings.c'

        include 'Files/Screen.di'
        include 'Files/Balls.c'




