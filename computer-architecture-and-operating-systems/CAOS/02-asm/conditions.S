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

// jz       label   /* jump if equal (zero), ZF == 1 */
// jnz      label   /* jump if not equal (non-zero), ZF == 0 */
// jc       label   /* jump if CF == 1 */
// jnc      label   /* jump if CF == 0 */
// jo       label   /* jump if OF == 1 */
// jno      label   /* jump if OF == 0 */
// jg       label   /* jump if greater (signed) */
// jge      label   /* jump if >= (signed) */
// jl       label   /* jump if < (signed) */
// jle      label   /* jump if <= (signed) */
// ja       label   /* jump if > (unsigned) */
// jae      label   /* jump if >= (unsigned) */
// jb       label   /* jump if < (unsigned) */
// jbe      label   /* jump if <= (unsigned) */

// CF (Carry Flag)     /* set if there is a carry out of the most significant bit (unsigned overflow) */
// PF (Parity Flag)    /* set if the number of set bits in the lowest byte is even */
// AF (Auxiliary Flag) /* set if there is a carry from bit 3 to bit 4 (used in BCD arithmetic) */
// ZF (Zero Flag)      /* set if the result of an operation is zero */
// SF (Sign Flag)      /* set if the result is negative (most significant bit is 1) */
// OF (Overflow Flag)  /* set if signed overflow occurs */

main:
    call    readi64
    mov     r12, rax    

    test    r12, r12
    
    jz      end
    
    mov     rdi, r12
    call    writei64

    jmp     main    

end:
    call    finish

