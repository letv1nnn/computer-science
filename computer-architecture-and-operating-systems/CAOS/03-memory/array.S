/*
    reads two number for the input, index and some number,
    program refreshes the number by the given index with
    the given number in the array.
*/

    .intel_syntax noprefix
    .global main

main:
    call    readi64
    jc      fin
    // R12 - index
    mov     r12, rax
    
    call    readi64
    jc      fin
    // R13 - new value
    mov     r13, rax
    
    // BREG + IREG * SCALE + OFFSET
    // SCALE = 1, 2, 4, 8

    lea     r14, [rip + arr]        // absolute address of the array
    lea     r14, [r14 + r12 * 8]    // absolute address of the array cell

    mov     rdi, [r14]
    
    call    writei64

    mov     [r14], r13

    jmp     main

fin:
    call    finish

    .bss // uninitialized
arr:
    .skip 200 * 8 // 200 8-bytes numbers


