.name "Buttman"
.comment "I like butts"

loop: sti r1, %:live, %1     #robin
live:     #WAAROM WERKT DIT??

life:     #comment
        live %0
        ld %0, r2
        zjmp %:loop
