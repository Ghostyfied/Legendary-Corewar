.name "The dude"



.comment "hey dude check hoe laat het is"



start:
live:
	live %1
    ld %20, r16
	fork %500
    sti r1, %:live, %1
    ld %0, r16
    zjmp %:live
