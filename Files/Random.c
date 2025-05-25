proc Random.GetNumber, wMod
    cmp word [Random.wPrevValue], 0
    jne .Get
    mov ah, 2Ch
    int 21h
    mov [Random.wPrevValue], dx

.Get:
    mov ax, [Random.wPrevValue]
    imul cx, cx, 25173
    add ax, 13849
    adc dx, 0
    mov [Random.wPrevValue], ax
    
    xor dx, dx
    div word [wMod]
    ret
endp

Random.wPrevValue dw 0
