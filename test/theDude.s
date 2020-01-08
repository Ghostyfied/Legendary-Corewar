.name 	"Big Lebowski"

.comment	"I'm the Dude,



so that's what you call me."


		ld	%0, r2
		lldi %3, %3, r2 
		zjmp %:dit
dit:
		live %-1
		fork %2
		zjmp %:dit

kill:	ld 5, r8
		#ld 19, r9
		#ld 18, r10
		#ld 17, r11
		st r8, 5
		#st r9, 19
		#st r10, 18
		#st r11, 17
		#lldi
		
		#zjmp %:dit

#trashtalk:
		ld %85, r2
    	ld %32, r3
        ld %83, r4
        ld %85, r5
        ld %75, r6
		aff r2
		aff r3
		aff r4
		aff r5
		aff r6
