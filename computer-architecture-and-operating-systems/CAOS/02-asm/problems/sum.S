    .intel_syntax noprefix
    .global main

main:
    call    readi32
    mov     r12, rax 

    xor     r13, r13

loop:
    test    r12, r12
    jz      end
    
    call    readi32  
    add     r13, rax    

    dec     r12
    jmp     loop

end:
    mov     rdi, r13
    call    writei32

    call    finish
