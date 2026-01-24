    .intel_syntax noprefix
    .text
    .global main

main:
    mov     qword ptr [var + rip], 500
    
    mov     rdi, [var + rip]
    call    writei64

    call    finish

    .data
var:
    .quad    12
