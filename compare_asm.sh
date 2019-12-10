#!/bin/bash

rm -rf Compare
mkdir -p Compare

filename="${1%.*}"

./vm_champs/asm $1
xxd -p $filename.cor > Compare/$filename.diff1
rm -f $filename.cor

./asm $1
xxd -p $filename.cor > Compare/$filename.diff2
rm -f $filename.cor

diff Compare/$filename.diff1 Compare/$filename.diff2 > Compare/$filename.result
