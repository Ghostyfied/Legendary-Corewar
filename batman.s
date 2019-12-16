<<<<<<< HEAD
.name  "Buttman"
.comment "I like butts"

loop: sti r1, %:live, %1   #robin
live:     #WAAROM WERKT DIT??
#dit mag?

          

life:     #comment
       live %20000000
=======
.name "Batman"
.comment "I like Robin"

loop: sti r1,              %:live,%1
live:
        live		 %20000000
>>>>>>> 6ee5af4ff8a973b43ecf5e32792526e94856fbac
        ld %0, r2
        zjmp %:loop
