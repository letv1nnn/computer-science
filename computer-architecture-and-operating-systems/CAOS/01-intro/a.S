// readi64 and writei64 defined in ../02-asm/simpleio_x86_64.S, so make sure you've included it

    .intel_syntax noprefix  // assembler directive
    .global main            // allow external access

main:
    call    readi64         // reads from I/O and puts to RAX
    mov     rdi, rax

    add     rdi, 1

    call    writei64        // writes to I/O content from RDI

    call    finish
