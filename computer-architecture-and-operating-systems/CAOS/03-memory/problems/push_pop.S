    .intel_syntax noprefix
    .global main

main:
    call    readi64
    push    rax
    
    mov     rdi, [rsp]
    call    writei64

    pop     rdi
    call    writei64

fin:
    call    finish

