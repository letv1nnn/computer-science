    .intel_syntax noprefix
    .global main
main:
    mov     rdi, [var + rip]
    call    writei64

    call    finish

var:
    .quad   42
