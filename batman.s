.name "Batman"
.comment "I like Robin"

loop: sti r1,              %:live,%1
live:
        live		 %20000000
        ld %0, r2
        zjmp %:loop
