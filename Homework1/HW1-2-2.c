#include <stdio.h>
#include <stdlib.h>

/* 
 Student Name: Darshan Patel
 Date: 2/1/2016

ECE 2035 Homework 1-2

This is the only file that should be modified for the C implementation
of Homework 1.

This program computes and prints the number of elements that are in both
SetA and SetB.  SetA always contains 8 integers and SetB always contains 10.
*/

// FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

int SetA[] = {8, 3, -27, -60, 25, 17, 26, 9}; 
int SetB[] = {5, 17, -7, 3, -25, 27, 42, 26, 8, -60};

int main() {
  int IntersectionSize = 0;

  // insert your code here
  for (int i = 0; i < 10; i++) { //loop through SetB
  	int b = SetB[i];
  	for (int j = 0; j< 8; j++) { //loop through SetA
  		if (b == SetA[j]) {
  			IntersectionSize++; 
  			//if the item in SetB = item in SetA, increment intersection size
  		}
  	}
  }
  printf("Size of intersection: %d\n", IntersectionSize);
  return 0;
}

