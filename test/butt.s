.name "Butt"
.comment "I like banana"

loop:
live:
        sti r1, %:live, %1
live:
        live %0
        ld %0, r2
        zjmp %:loop
end:

eof:
