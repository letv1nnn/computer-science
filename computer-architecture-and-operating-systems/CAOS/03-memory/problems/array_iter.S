    .intel_syntax noprefix
    .global main

main:
    mov     r12, 0
    lea     r13, [rip + arr]

loop:
    cmp     r12, 8
    jge     end

    mov     rdi, [r13 + r12*8]
    call    writei64

    add     r12, 1
    jmp     loop

end:
    call    finish

arr:
    .quad    12
    .quad    23
    .quad    34
    .quad    45
    .quad    56
    .quad    67
    .quad    78
    .quad    89

