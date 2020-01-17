.name "Flintinator"



.comment "first I ping pong the ball, then I bing bong your mom"



start:
live: 
	live %1
    sti r1, %:live, %1
    ld %0, r16
    zjmp %:live
bomb:
    live %1
    fork %:live
    live %1
    fork %:bomb
    live %1
