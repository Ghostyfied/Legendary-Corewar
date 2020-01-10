if [ $# -lt 2 ] || [ $1 == "-help" ] ; then
    echo "usage: sh vm_tester.sh <filename1.cor> <filename2.cor> <filename.etc.cor> <cycles>" ; exit 1
fi
CYCLES=${@: -1}
n=$(($# - 1))
for arg do
  [ "$n" -gt 0 ] && set -- "$@" "$arg"
  shift
  n=$((n - 1))
done
for arg do
	if [ ! -f $arg ]; then
		echo "error: file $arg does not exist" ; exit 1
	fi
done
re='^[0-9]+$'
if ! [[ $CYCLES =~ $re ]]; then
	echo "error: $CYCLES is not a number" >&2 ; exit 1
fi
for (( i=0; i <= $CYCLES; i+=1))
do
	./corewar -d $i $@ | sed -n -e '/^0x/p' > temp_output1
	./vm_champs/corewar $@ -d $i | sed -n -e'/^0x/p' > temp_output2
	if ! cmp -s "temp_output1" "temp_output2"; then
		printf '\033[0;31mmemory is NOT the same at cycle %s\n\033[0m' "$i" ; exit 1
	fi
done
printf '\033[0;32mperfect! memory is the same at all cycles until %s\n\033[0m' "$CYCLES"