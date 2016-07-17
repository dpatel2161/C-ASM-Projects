#     T o p  o f  P i l e
#
#
# This routine finds the color of the part on top of a pile.
#
# <3/4/16>                               <Darshan Patel>

.data
Array:  .alloc	1024
Colors: .word 	50462976, 117835012
.text
TopOfPile:	addi	$1, $0, Array	# point to array base
			swi	545		# generate pile


			#$1: 64 + Array (loop counter)
			#$2: i
			#$5: 4032 + Array (loop exit condition)
			#$7-9: behind, current, agead
			#$6, $11: up and down
			#$15: how many colors are left -1 

			#start indexing at about 33% 
			addi $1, $1, 5310 # start at 1344 + 3969 + Array
			addi $5, $0, Array 
			addi $5, $5, 6720 #end 4032 + 2688 + Array
			addi $15, $0, 6 #intialize colors remaining

			#Second Half changes index
SecondHalf: addi	$1, $1, -3968	#$1(4032) - 3969 = 63 
			addi	$5, $5, -2688	#4032-x = 1344 => x=2688

TripleInc:	addi	$1, $1, 1 		#increment index by 1 (3 total)
DoubleInc:	addi	$1, $1, 1 		#increment index by 1 (2 total)
MainLoop:	addi	$1, $1, 1 		#increment index by 1

			slt 	$2, $5, $1 		#if (4032 < i) => secondHalf
			bne		$2, $0, SecondHalf		

			lbu		$9, 1($1) 		  #colors[i+1]
			beq		$9, $0, TripleInc #if colors[i+1] = 0 => i+3
			lbu		$8, 0($1) 		  #colors[i]
			beq		$8, $0, DoubleInc #if colors[i] = 0 => i+2
			lbu		$7, -1($1) 		  #colors[i-1]
			bne		$7, $9, MainLoop  #if colors[i-1] = 0 => i+1

			lbu		$11, 64($1) 	  #up colors[i + 64]
			beq		$11, $0, MainLoop #if up = 0 => i+1
			lbu		$6, -64($1) 	  #down colors[i - 64]
			bne		$6, $11, MainLoop #if down = 0 => i+1

			beq		$8, $6, CheckNext #if (colors[i] = up) => go to check colors[i+1]
			beq		$8, $9, DeleteUp  #if (colors[i] = colors[i+1] && colors[i] != up) => deleteUp
			J MainLoop	#next iteration

CheckNext:	beq		$8, $9, MainLoop #if (colors[i] = colors[i+1)) => no overlap => increment i
			addi	$6, $9, 0 		 #if (colors[i] != colors[i+1]) -> set delete register ($6) to current
DeleteUp:	lbu 	$8, Colors($6)	 #load whether color is removed from memory
			beq		$8, $0, MainLoop #if already removed => increment
			sb		$0, Colors($6)   #if not removed => remove color
			addi 	$15, $15, -1 	 #decrement colors remaining counter
			beq		$15, $0, End 	 #if only one color remaining => go to end		
			J MainLoop

End:    addi $2, $0, 8 				 #intialize i to 8
Loop:	addi $2, $2, -1 			 #decrement i 
		lbu $6, Colors($2)			 #load Colors[i]
		beq	$6, $0, Loop 			 #if Colors[i] = 0 => Loop

		swi	546						# submit answer and check
		
		jr	$31						# return to caller
