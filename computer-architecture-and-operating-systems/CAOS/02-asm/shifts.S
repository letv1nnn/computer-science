    .intel_syntax noprefix
    .global main

main:
    call    readi64
    mov     r12, rax

m_shl:
    shl     r12, 1
    jnz     m_shl

    mov     r12, rax

m_shr:
    shr     r12, 1
    jnz     m_shr

    mov     r12, rax

m_sal:
    sal     r12, 1
    jnz     m_sal

    mov     r12, rax

m_sar:
    sar     r12, 1
    jnz     m_sar

    mov     r12, rax

end:
    call    finish

