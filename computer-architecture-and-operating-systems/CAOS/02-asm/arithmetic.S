// All library functions do not change the values of  rsp, rbp, rbx, r12, r13, r14, r15.
    .intel_syntax noprefix
    .global main

// add     DST, SRC   /* DST += SRC */
// sub     DST, SRC   /* DST -= SRC */
// inc     DST        /* ++DST */
// dec     DST        /* --DST */
// neg     DST        /* DST = -DST */
// mov     DST, SRC   /* DST = SRC */
// imul    SRC        /* (eax,edx) = eax * SRC - signed */
// mul     SRC        /* (eax,edx) = eax * SRC - unsigned */
// and     DST, SRC   /* DST &= SRC */
// or      DST, SRC   /* DST |= SRC */
// xor     DST, SRC   /* DST ^= SRC */
// not     DST        /* DST = ~DST */
// cmp     DST, SRC   /* DST - SRC, result does not save, */
// test    DST, SRC   /* DST & SRC, result does not save  */
// adc     DST, SRC   /* DST += SRC + CF */
// sbb     DST, SRC   /* DST -= SRC - CF */

main:
    call    readi64
    mov     r12, rax
    
    call    readi64
    mov     r13, rax

    imul    r12, r13
    inc     r12
    neg     r12

    mov     rdi, r12
    call    writei64

    call finish


