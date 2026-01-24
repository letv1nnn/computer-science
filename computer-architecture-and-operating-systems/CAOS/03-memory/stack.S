// ** Task **
// Scan two numbers and put them onto the stack and print them


//    Stack content     Memory address
//
//  .                .
//  .                .
//  .                .
//  +----------------+ 0x0000F040
//  |                |
//  +----------------+ 0x0000F044 <-- top of the stack (rsp pointing to it)
//  |      data      |
//  +----------------+ 0x0000F048
//  |      data      |
//  +----------------+ 0x0000F04C
//  .                .
//  .                .
//  .                .
//  +----------------+ 0x0000FFF8
//  |      data      |
//  +----------------+ 0x0000FFFC
//  |      data      |
//  +----------------+ 0x00010000 <-- bottom of the stack

    .intel_syntax noprefix
    .global main

main:
    // [ return   xxxxx ]
    //   ^rsp
    call    readi64
    push    rax
    // [ rax1, return   xxxxx ]
    //   ^rsp

    call    readi64
    push    rax
    // [ rax2, rax1, return   xxxxx ]
    //   ^rsp

    // // Printing the value under the rsp (last entered number)
    // mov     rdi, [rsp]
    // call    writei64

    // int64_t arr[100], on the stack
    sub     rsp, 100 * 8 

    mov     rdi, [rsp + 8]
    call    writei64

    pop     rdi
    call    writei64
    // [ rax1, return   xxxxx ]
    //   ^rsp

    pop     rdi
    call    writei64
    // [ return   xxxxx ]
    //   ^rsp

    call    finish
