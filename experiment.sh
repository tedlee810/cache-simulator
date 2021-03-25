for EVICTION in "lru" "fifo"
do
	for ALLOCATION in "write-allocate" "write-back"
	do
		for WRITE in "write-through" "write-back"
		do
			for FILE in "gcc.trace" "swim.trace"
			do
				for SETS in 1 128 8192
				do
					for ASSOCIATIVITY in 1 128
					do
						for BLOCKSIZE in 4 256
						do
							echo $SETS $ASSOCIATIVITY $BLOCKSIZE $ALLOCATION $WRITE $EVICTION $FILE >> output.txt
							./csim $SETS $ASSOCIATIVITY $BLOCKSIZE $ALLOCATION $WRITE $EVICTION < $FILE >> output.txt
							echo "." >> output.txt
						done
					done
				done
			done
		done
	done
done
