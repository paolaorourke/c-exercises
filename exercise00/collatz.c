#include <stdio.h>  //printf and scanf
#include <string.h> //for strlen

int main(int argc, char *arg[]) {
  int number;
  int iterations = 0;
  printf("Enter a number: ");
  scanf("%d", &number);

  while (number > 1) {
    if (number % 2 == 0) { // even
      number = number / 2;
      iterations += 1;
    }

    else {
      number = 3 * number + 1;
      iterations += 1;
    }
  }
  printf("[% d] \n", iterations); // new line
}
