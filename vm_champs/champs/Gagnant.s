.name		"Celebration Funebre v0.99pl42"
.comment	"Jour J"

		ld   %0,r3		
label:		zjmp %:avantdebut
		zjmp %0				# pour eviter ecrasement
						# de l'instruction suivante
code:		live %42			# 5
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		live %42			# 5
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		live %42			# 5
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		live %42			# 5
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		sti  r15,%0,r14			# 6
		zjmp %-200
	
avantdebut:	sti   r1,%:code,%1  # 		#7	
		sti   r1,%:code,%15 # 		#7	
		sti   r1,%:code,%29 # 		#7	
		sti   r1,%:code,%43 # 		#7	
		sti   r1,%:code,%57 # 		#7	
		sti   r1,%:code,%71 # 		#7	

level111:	live %42	
		ldi  %12, %:code, r15		#set des octets 13-16
		ld   %-182, r14			# $A -6 -12
		ld   %0,r2
		zjmp %:label
