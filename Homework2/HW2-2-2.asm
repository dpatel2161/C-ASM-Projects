#     Intensity Matcher
#
#
# This program finds the two colors with the closest intensity
# in an eight color palette.
#
#  required output register usage:
#  $10: MinDelta, $11: Color A address, $12: Color B address
#
# <2/5/16>					<Darshan Patel>

.data
Array:  .alloc  8               # allocate static space for packed color data

.text
		#$1: counter1
		#$2: counter2
		#$3: 4 (memory location size)
		#$4: limit of memory
		#$5: red
		#$6: green
		#$7: blue
		#$8: intensity1
		#$9: intensity2
		#$10: MinDelta
		#$11: address1
		#$12: address2
		#$13: correct MinDelta
		#$14: correct address1
		#$15: correct address2
		#$16: delta
		#$17: stores logic
IntensityMatch: addi  $1, $0, Array     # set memory base
            swi   589               # create color palette and update memory
			addi  $10, $0, 255	# TEMP: guess MinDelta
			addi  $11, $1, 4	# TEMP: guess an address
			addi  $12, $1, 12	# TEMP: guess another address
			addi $1, $0, Array #initialize counter1
			addi $2, $0, 0 #initialize counter2
			addi $3, $0, 3 #initialize to 3 
			addi $4, $0, 32 #ititilize exit condition
			addi $4, $4, Array #limit of looping
			addi $1, $1, -4 #increment counter1
OuterLoop:  addi $1, $1, 4 #increment counter1
			beq $1, $4, Done #if counter1 = (Array1 + 32) => Done
			addi $2, $1, 4 #intialize counter2 to (counter1 + 4)
			lbu $5, 2($1) #load red1
			lbu $6, 1($1) #load green1
			lbu $7, 0($1) #load blue1
			add $8, $5, $6 #find intensity and store in $8
			add $8, $8, $7
			div $8, $3
			mflo $8
InnerLoop:  beq $2, $4, OuterLoop
			lbu $5, 2($2) #load red2
			lbu $6, 1($2) #load green2
			lbu $7, 0($2) #load blue2
			add $9, $5, $6 #find intensity and store in $9
			add $9, $9, $7
			div $9, $3
			mflo $9
			sub $16, $8, $9 #difference in intensities
			slti $17, $16, 0 #absolute value if delta < 0
			beq $17, $0, Skipabs
			sub $16, $0, $16
Skipabs:	slt $17, $16, $10 #Delta < MinDelta?
			beq $17, $0, ReLoop #if, so replace MinDelta and addresses for 2 colors
			add $10, $0, $16
			add $11, $0, $1
			add $12, $0, $2
ReLoop:		addi $2, $2, 4 #increment counter2
			J InnerLoop 

Done:		swi     581 #call oracle
			jr      $31             # return to caller
 

                
