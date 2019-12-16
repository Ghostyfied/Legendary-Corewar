.name 	"Big 

Lebowski"

.comment	"I'm the Dude, 

so that's what you call me."
loop:
        sti r1, %:live, %1
live:
     s   live %0
     s   ld %0, r2
    s    zjmp %:loop
		sti r1, %:live, %1