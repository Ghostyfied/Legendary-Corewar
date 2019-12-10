.name "Buttman"
.comment "I like butts"

loop:
        sti r1,%:live,%1    #segfault?
live:
        live %0
        ld %0, r2
        zjmp %:loop
