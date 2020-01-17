.name 	"TEST"
.comment	"test test"

sti r1, %0, %1
live %0
ld %0, r2
zjmp %:blah

blah:

blah:
