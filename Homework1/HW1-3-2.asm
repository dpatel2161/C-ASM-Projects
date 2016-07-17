# HW1-3
# Student Name: Darshan Patel
# Date: 2/1/16
#
# This program determines whether SetA (always of size 8) is a subset of SetB
# (always of size 10) and if so, stores 1 (otherwise 0) in the memory location
# labelled Result.

# This program computes the number of elements that are in both
# SetA and SetB and stores it in the memory location labelled Result.
# SetA always contains 8 integers and SetB always contains 10.

# NOTE:
# The program should work on multiple test cases, not just the one provided.
# For full credit, be sure to document your code.

.data
SetA:  .word 8, 3, -27, -60, 25, 17, 26, 9
SetB:  .word 5, 17, -7, 3, -25, 27, 42, 26, 8, -60
Result: .alloc 1

.text		
		# write your code here...
		#$1: loading current SetA
		#$2: loading current SetB
		#$3: address of SetA index
		#$4: address of SetB index
		#$5: counter for SetA
		#$6: counter for SetB
		#$7: 8
		#$8: 10
		#$9: number of matches

		addi $3, $0, -4
		addi $7, $0, 8		
		addi $8, $0, 10	
		addi $9, $0, -1

NextA:	addi $9, $9, 1

false:	beq $5, $7, done #if all of SetA is done, return true
		addi $3, $3, 4 #get address of next SetA
		addi $5, $5, 1 #increment SetA counter
		addi $6, $0, 1 #reset SetB counter
		addi $4, $0, 0
		lw $1 SetA($3) #load SetA number
loop:	lw $2 SetB($4) #load SetB number
		beq $1, $2, NextA # if SetA number = SetB number => get new SetA number
		beq $6, $8, false #if SetB numbers are done, return false

NextB:	addi $4, $4, 4 #put next address of SetB in $4
		addi $6, $6, 1 #increment SetB Counter
		J loop

done:	sw $9 Result($0) #store number of matches in memory location called Result
		jr $31	     			# return to OS


