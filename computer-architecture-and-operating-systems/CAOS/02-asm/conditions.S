// All library functions do not change the values of registers rsp, rbp, rbx, r12, r13, r14, r15.
    .intel_syntax noprefix
    .global main

// Two's complement
// u s
// 000 0 0
// 001 1 1
// 010 2 2
// 011 3 3
// 100 4 −4
// 101 5 −3
// 110 6 −2
// 111 7 −1

// jz label /* jump if equal (zero), ZF == 1 /
// jnz label / jump if not equal (non-zero), ZF == 0 /
// jc label / jump if CF == 1 /
// jnc label / jump if CF == 0 /
// jo label / jump if OF == 1 /
// jno label / jump if OF == 0 /
// jg label / jump if greater (signed) /
// jge label / jump if >= (signed) /
// jl label / jump if < (signed) /
// jle label / jump if <= (signed) /
// ja label / jump if > (unsigned) /
// jae label / jump if >= (unsigned) /
// jb label / jump if < (unsigned) /
// jbe label / jump if <= (unsigned) */

main:
    call    readi64
    mov     rdi, rax

    call    writei64

    jmp     main

    call    finish

