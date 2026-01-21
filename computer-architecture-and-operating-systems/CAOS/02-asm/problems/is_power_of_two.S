    .intel_syntax noprefix
    .global main

main:
    call    readi64
    mov     r12, rax

    test    r12, r12
    jz      not_power

loop:
    cmp     r12, 1
    je      power
    
    test    r12, 1
    jnz     not_power

    shr     r12, 1
    jmp     loop

power:
    mov     rdi, 1
    jmp     end

not_power:
    mov     rdi, 0

end:
    call    writei64
    call    finish
