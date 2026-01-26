    .intel_syntax noprefix
    .global main

main:
    
    ret

var:
    .quad   0xBADC0FFEE0DDF00D

/*
little endian representation (objdump):
0000000000000001 <var>:
   1:	0d f0 dd e0 fe       	or     $0xfee0ddf0,%eax
   6:	0f                   	.byte 0xf
   7:	dc                   	.byte 0xdc
   8:	ba                   	.byte 0xba
*/
