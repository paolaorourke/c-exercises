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

#include <stdio.h>
#include <stdlib.h>

int main() {
  int max = 10; // buffer array of 10
  int size = 0;
  int *arr = malloc(max * sizeof(int));
  char buffer_array[100];

  while (fgets(buffer_array, 100, stdin) != NULL) { // fills array
    int num = atoi(buffer_array);
    arr[size] = num;
    size++; // keeps track of how big array is while also filling

    if (size == max) {                       // knows whether to add space
      max *= 2;                              // if array is full it doubles
      arr = realloc(arr, max * sizeof(int)); // reallocates space, multiplies
                                             // max times size of int to get
                                             // bytes required
    }
  }
  // prints reversed array
  for (int i = size - 1; i >= 0; i--) {
    printf("%d ", arr[i]);
  }
  printf("\n"); // so that command prompt not on same line

  free(arr); // frees space after
  return 0;
}
