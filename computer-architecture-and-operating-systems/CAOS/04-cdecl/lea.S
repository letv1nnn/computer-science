    .intel_syntax noprefix
    .global main

main:
    call    readi64
    
    // mul     rax, 2
    // sal     rax, 2
    lea     rbx, [0 + rax * 2] // lea is faster in such operations
    
    mov     rdi, rbx
    call    writei64

mul7:
    call    readi64
    mov     r12, rax

    lea     r13, [0 + r12 * 8] // scale can olny be 1, 2, 4, 8
    sub     r13, r12

    mov     rdi, r13
    call    writei64

fin:
    call    finish
