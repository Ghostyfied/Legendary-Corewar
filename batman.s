<<<<<<< HEAD
.name "name"
.comment "comment"
=======
.name "Buttman"
.comment "I like butts"
>>>>>>> 054c61ad1ca183114bbbbbe63a6a8da04fea40b0

loop:
        sti r1, %:live, %1
live:
        live %0
        ld %0, r2
        zjmp %:loop
		sti r1, %:live, %1
