.name       "Batman"
.comment    "This city needs me"

loop:
        sti r1, %:live, %1
live:
        live %2146428
        ld %0, r2
        zjmp %:loop
