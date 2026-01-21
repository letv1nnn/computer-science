# Assembly language. Shifts, GDB.

## GDB

Compile with ***-g*** flag.

>NOTE: To use Intel syntax, create a file `.gdbinit` and write the followint string: `set disassembly-flavor intel`.

```
list (l) – show code. `l 3` shows code starting from line 3  
break (b) – set a breakpoint. You need to specify a function name or a line. `b main`. Execution will reach this place and stop.  
run (r) – run the program  
info break (i b) – view breakpoints  
del <breakpoint num> – delete the breakpoint with number `breakpoint_num`  
layout next (la next) – enable the next layout  
layout regs (la reg) – enable register view  
step (s) – execute one instruction (stepping into functions)  
next (n) – execute one instruction (stepping over functions)  
continue (c) – continue execution until the next breakpoint  
refresh – refresh the display (if everything shifted or became misaligned)  
finish – exit the current function  
help <command> – help for a command  

p/t $rax – print the eax register in binary  
p/z $rax – print the eax register in hexadecimal  
set $rax=5 – set the value of $eax to 5  
jump main – continue execution from a different place (not necessarily `main`; you can specify any other place or a line number)  
p/t $rax^3 – print in binary the result of executing `$eax XOR 3` (other logical operations can also be used)  
ctrl+x o – switch between panels (so that the up arrow works)
```
