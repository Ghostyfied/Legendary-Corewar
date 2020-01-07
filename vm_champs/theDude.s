.name		"Big 

Lebowski"

.comment	"I'm the Dude, 

so that's what you call me."








loop:


fk:		
		ld 0, r6
		ld %6, r7
		fork %:hier
		zjmp %:fk
hier:
		st r6, 4
		st r7, 4
	