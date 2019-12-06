.name		"Big 

Lebowski"

.comment	"I'm the Dude, 

so that's what you call me."
loop:
        sti r1, %:live, %1
live:
        live %0
        ld %0, r2
        zjmp %:loop
		sti r1, %:live, %1