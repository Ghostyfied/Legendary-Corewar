.name       "Batman"
.comment    "This city needs me"


live:
        live %-1
		ld 0, r2
		ld 2, r3
		add r1, r2, r4
		sub r2, r3, r5
		or r4, r5, r6
		and r4, r6, r8
		xor r6, r4, r7
		st r4, 0
		st r3, -4
		st r5, 0
		st r6, 0
		st r7, 0
		st r8, 0
		add r10, r10, r10
		zjmp %:live
		#st r2, 0
