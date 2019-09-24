code segment
    assume cs: code
start:
    mov ax, 3508h
    int 21h
    mov ah, 4ch
    int 21h
code ends
end start
