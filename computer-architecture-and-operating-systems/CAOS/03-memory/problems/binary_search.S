    .intel_syntax noprefix
    .global main
    
main:
    call    readi64   // target value
    jc      fin
    mov     r12, rax  // stored in R12

    // initial range
    mov     r13, 0    // lower bound
    mov     r14, 100  // upper bound

loop:
    cmp     r13, r14
    jg      fin
    
    // mid value
    mov     rbx, r13
    add     rbx, r14
    shr     rbx, 1

    call    readi64 // user guess
    jc      fin
    mov     r15, rax
    
    cmp     r15, r12
    jz      fin
    jl      greater
    jmp     lower

greater:
    mov     rdi, 1
    call    writei64

    lea     r13, [rbx + 1]
    jmp     loop

lower:
    mov     rdi, 0
    call    writei64

    lea     r14, [rbx - 1]
    jmp     loop

fin:
    mov     rdi, r12
    call    writei64
    call    finish

