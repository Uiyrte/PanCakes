proc Random.GetNumber uses ax bx, wMod
    cmp word [Random.wPrevValue], 0
    jne .Get
    mov ah, 2Ch
    int 21h
    mov [Random.wPrevValue], dx

.Get:
    mov ax, [Random.wPrevValue]
    mov bx, 25173
    mul bx
    add ax, 13849
    adc dx, 0
    mov [Random.wPrevValue], ax
    
    xor dx, dx
    div word [wMod]
    ret
endp

Random.wPrevValue dw 0
