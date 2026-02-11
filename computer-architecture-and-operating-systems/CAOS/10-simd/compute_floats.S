// ┌──────────────────────────────┐
// │             ZMM              │   512 bits  / 16 floats  /  8 doubles
// └───────────────┬──────────────┤
//                 │      YMM     │   256 bits  /  8 floats  /  4 doubles
//                 └───────┬──────┤
//                         │ XMM  │   128 bits  /  4 floats  /  2 doubles
//                         └──────┘
    .intel_syntax noprefix
    .global process

// function that computes the following expression:
// (a + b) / ((float)c + d)
process:
    push        rbp
    mov         rbp, rsp
    
    // xmm0 = a, xmm1 = b, rdi = c, xmm2 = d (ret in xmm0)

    // add s - scalar s - single (float)
    addss       xmm0, xmm1              // xmm0 = a + b

    cvtsi2ss    xmm3, rdi               // xmm3 = (float)c
    addss       xmm2, xmm3              // xmm2 = c + d

    // divission, (a + b) / ((float)c + d)
    divss       xmm0, xmm2

    mov         rsp, rbp
    pop         rbp
    ret

printf_format:
    .string     "%d\n"
