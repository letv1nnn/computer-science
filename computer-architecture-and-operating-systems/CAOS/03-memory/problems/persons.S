// ** Условие **
// Завести массив из 3х человек с разным ростом и весом
// По считаному индесу выводить рост и вес человека под этим индексом

    .intel_syntax noprefix
    .text
    .global main
main:
    call    readi32
    mov     ebx, eax  // EBX stores the index
    
    shl    ebx, 1

    lea     esi, persons

    mov     edi, [esi + ebx * 4]
    call    writei32

    mov     edi, [esi + ebx * 4 + 4]
    call    writei32

fin: 
    call    finish

    .data
persons:
    .int    80
    .int    180
    .int    76
    .int    177
    .int    50
    .int    164


