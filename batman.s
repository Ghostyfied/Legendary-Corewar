.name  "Buttman"
.comment "I like butts"

loop: sti r1, %:live, %1
live:
life:
       live %20000000
        ld %1, r2
        zjmp %:loop
