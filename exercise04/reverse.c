// Paola O'Rourke
//
#include <stdio.h> //printf and scanf
#include <stdlib.h>
#include <string.h>

// for strleni
// char number_array[365];
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

int main() {
  int numbers[MAX];   // numbers= array
  int num, count = 0; // count = how many in array; num = placeholder

  while (scanf("%d", &num) != EOF && count < MAX) {
    numbers[count++] = num; // continues adding to count and num being put in
                            // numbers
  }

  for (int i = count - 1; i >= 0; i--) { // starts from back and creates
    printf("%d ", numbers[i]);           // d can take any size decimal
  }
  printf("\n");

  return 0;
}
