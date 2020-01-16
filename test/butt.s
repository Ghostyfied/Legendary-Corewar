.name "Butt"
.comment "I like banana"

loop:
        sti r1, %:eof, %1
live:
        live %0
        ld %0, r2
        zjmp %:loop
end:

eof:


