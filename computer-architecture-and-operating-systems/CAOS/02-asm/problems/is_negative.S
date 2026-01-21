    .intel_syntax noprefix
    .global main

main:
    call    readi64
    mov     r12, rax

    test    r12, r12

    jz      zero
    jg      positive
    jmp     negative

positive:
    mov     rdi, 1
    jmp     end

negative:
    mov     rdi, -1
    jmp     end

zero:
    mov     rdi, 0

end:
    call    writei64
    call    finish

