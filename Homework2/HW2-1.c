/*    Intensity Matcher

This program finds the two closest colors in an array of packed RGB values,
based on the difference in their intensities.  Intensity is measured as mean
color component value: I = (R+G+B)/3).
It prints the difference in intensities of the two closest colors.

<2/5/16>	               <Darshan Patel>   */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   int	Nums[8];
   int	NumNums, MinDelta=-55;  // temporary initial value
   int  Load_Mem(char *, int *);

   if (argc != 2) {
     printf("usage: ./HW2-1 valuefile\n");
     exit(1);
   }
   NumNums = Load_Mem(argv[1], Nums);
   if (NumNums != 8) {
      printf("valuefiles must contain 8 entries\n");
      exit(1);
   }


   /* Your program goes here */
   MinDelta = 255; //intitate delta as maximum possible value
   for (int i = 0; i < 8; i++) { //loop through each in set
      int number1 = Nums[i]; //first color
      unsigned R1 = number1 >> 16; //parse first red value using left logical shift
      unsigned G1 = (number1 >> 8) & (0xFF); //parse first green value using left logical shift and bitwise 'and'
      unsigned B1 = number1 & (0xFF); //parse first blue value using bitwise and
      int intensity1 = (R1 + G1 + B1) / 3; //calculate first intensity
      for (int j = i + 1; j < 8; j++) { //for each in set, loop to check the others
         int number2 = Nums[j]; //second color

         unsigned R2 = number2 >> 16; //parse second red value
         unsigned G2 = (number2 >> 8) & (0xFF); //parse second green value
         unsigned B2 = number2 & (0xFF); //parse second blue value
         int intensity2 = (R2 + G2 + B2) / 3; //calculate second intensity
         int delta = abs(intensity1 - intensity2); //difference in intensities
         if (MinDelta > delta) {
            MinDelta = delta; //check if new delta is minimum, and if so, replace old minimum
         }
      }
   }

   printf("The 2 closest colors have an intensity difference of %d\n", MinDelta);
   exit(0);
}

/* This routine loads in up to 8 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
      printf("%s could not be opened; check the filename\n", InputFileName);
      return 0;
   } else {
      for (N=0; N < 8; N++) {
         NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
         if (NumVals == 2)
            IntArray[N] = Value;
         else
            break;
      }
      fclose(FP);
      return N;
   }
}