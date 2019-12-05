<<<<<<< HEAD
.name "bat"

.comment "man"
=======
.name "name"
.comment "comment"
>>>>>>> 78432c7c5b200e1e23ea32ce5a352a31ed0ef059

loop:
        sti r1, %:live, %1
live:
        live %0
        ld %0, r2
        zjmp %:loop
		sti r1, %:live, %1
