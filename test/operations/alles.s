.name "marin is de best"
.comment "veel beter dan robbe"
trap:





fork %:bomb
st		r2, -4
ld %0, r16
zjmp %:trap
ld %0, r16
live: live %1
        sti r1, %:live, %1
        ld %0, r16
        zjmp %:live
bom?b:
    live %1
    fork %:live
    live %1
    fork %:bomb
    live %1
