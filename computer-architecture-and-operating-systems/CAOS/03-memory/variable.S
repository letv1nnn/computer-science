    // Simple variable usage
    .intel_syntax noprefix
    .text
    .global main
main:
    // 0x123456
    lea     rax, rip
    mov     qword ptr [var + rip], 500

    mov     rdi, [var + rip] // [] - dereferencing, since var is just an address (register instruction pointer),
    call    writei64         // addressing is working relatively to rip.

    call    finish

// In this code, we won’t be able to change the value of var. Since var is located in the .text section,
// we cannot modify the .text section. To be able to assign a value to var, it needs to be moved
// to the .data section.

    .data
var: // all mentions of var will be replaced to the actual address 
    .quad    42

// .byte - 1 byte
// .word - 2 bytes
// .int  - 4 bytes
// .quad - 8 bytes

// byte  1 when accessing memory  (mov)
// word
// dword
// qword
