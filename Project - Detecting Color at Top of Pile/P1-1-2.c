/* <2/24/16>	               <Darshan Patel>

This program loads a pile and finds the topmost piece. */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   int	             PileInts[1024];
   int	             NumInts, TopColor=0;
   int  Load_Mem(char *, int *);

   if (argc != 2) {
     printf("usage: ./P1-1 valuefile\n");
     exit(1);
   }
   NumInts = Load_Mem(argv[1], PileInts);
   if (NumInts != 1024) {
      printf("valuefiles must contain 1024 entries\n");
      exit(1);
   }
   int result[7] = {1, 1, 1, 1, 1, 1, 1};
   for (int i = 16; i < 1016; i++) {
      if (PileInts[i] != 0) {
         //unpacking into char arrays
         char color4 = PileInts[i] >> 24;
         char color3 = PileInts[i] >> 16 & (0xFF);
         char color2 = PileInts[i] >> 8 & (0xFF);
         char color1 = PileInts[i] & (0xFF);
         char colors[4] = {color1, color2, color3, color4};

         //check each individual color
         for (int j = 0; j < 3; j++) {
            //if current color doesn't equal next color
            if (colors[j] != colors[j+1]) {

               //find the bottom color
               char down = PileInts[i+16] >> (j*8) & (0xFF);
               //finds if bottom color is not the same as current color
               if (colors[j] != 0 && down != 0 && colors[j] != down) {
                  //finds the 2nd bottom color to find out whether or not it is under the current color
                  char down2 = PileInts[i+32] >> (j*8) & (0xFF);
                  if (down2 != 0 && colors[j] == down2) {
                     result[colors[j]-1] = 0; //rule the current color out
                  }
               }
               //find above color
               char up = PileInts[i-16] >> (j*8) & (0xFF);
               //finds if above color is not the same as current color
               if (colors[j] != 0 && up != 0 && colors[j] != up) {
                  //finds the 2nd above color to find out whether or not it is under the current color
                  char up2 = PileInts[i-32] >> (j*8) & (0xFF);
                  if (up2 != 0 && colors[j] == up2) {

                     result[colors[j]-1] = 0; //rule the current color out
                  }
               }

               //if one of the colors is black continue to next iteration
               if (colors[j] == 0 || colors[j+1] == 0) {
                  continue;
               }

               //if this isn't the first color in the pack of 4
               if (j > 0) {
                  //check to see if there is a color over it
                  if (colors[j] == colors[j-1] && colors[j+2] != 0) {
                     result[colors[j]-1] = 0; //rule the current color out



                  }
               } else {
                  if (colors[j] == colors[j+2]) {
                     if (colors[j+1] != colors[j+3]) {
                        result[colors[j]-1] = 0; //rule the current color out

                     }
                  } else if (colors[j+2] != 0) {
                     //look at one ahead and behind colors of the 4 pack 
                     char behind = PileInts[i-1] >> 24;
                     char ahead = PileInts[i+1] & (0xFF);
                     //if the color is equal to the ahead or behind color
                     if ((colors[j] == behind && behind != 0) || (colors[j] == ahead && ahead!= 0)) {
                        result[colors[j]-1] = 0; //rule the current color out
                     } else {
                        //result[colors[j+1]-1] = 0; //rule the previous color out

                     }
                  }
               }

               //see if there is only one color remaining
               int sum = 0;
               for (int k = 0; k < 7; k++) {
                  sum += result[k];
               }
               if (sum == 1) {
                  break; //if only one color left, break out of loop
               }

            }

         }
         
      }
   }

   //report the color that hasn't been ruled out
   for (int i = 0; i < 7; i++) {
      if (result[i]) {
         TopColor = i + 1;
         break; //break once color is found
      }
   }

   printf("The topmost part color is: %d\n", TopColor);
   exit(0);
}



/* This routine loads in up to 1024 newline delimited integers from
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
      for (N=0; N < 1024; N++) {
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