// Paola O'Rourke
// kata03
// make a 3D array

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strlen
#define MAX_DIGITS 10
#define SEGMENTS 7
#define ROWS 3
#define COLS 3

const char digits[10][ROWS][COLS] = {{// 0
                                      {' ', '_', ' '},
                                      {'|', ' ', '|'},
                                      {'|', '_', '|'}},
                                     {// 1
                                      {' ', ' ', ' '},
                                      {' ', ' ', '|'},
                                      {' ', ' ', '|'}},
                                     {// 2
                                      {' ', '_', ' '},
                                      {' ', '_', '|'},
                                      {'|', '_', ' '}},
                                     {// 3
                                      {' ', '_', ' '},
                                      {' ', '_', '|'},
                                      {' ', '_', '|'}},
                                     {// 4
                                      {' ', ' ', ' '},
                                      {'|', '_', '|'},
                                      {' ', ' ', '|'}},
                                     {// 5
                                      {' ', '_', ' '},
                                      {'|', '_', ' '},
                                      {' ', '_', '|'}},
                                     {// 6
                                      {' ', '_', ' '},
                                      {'|', '_', ' '},
                                      {'|', '_', '|'}},
                                     {// 7
                                      {' ', '_', ' '},
                                      {' ', ' ', '|'},
                                      {' ', ' ', '|'}},
                                     {// 8
                                      {' ', '_', ' '},
                                      {'|', '_', '|'},
                                      {'|', '_', '|'}},
                                     {// 9
                                      {' ', '_', ' '},
                                      {'|', '_', '|'},
                                      {' ', '_', '|'}}};

void print_digit(int digit) {
  if (digit < 0 || digit > 9) {
    printf("Invalid input, digits 1-9: %d\n", digit);
    return;
  }
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      printf("%c", digits[digit][i][j]); // i for rows, j= columns
    }
    printf("\n"); // prints each on new line
  }
}

int main() {
  char input[MAX_DIGITS + 1]; // +1 for the  null terminator
  int len;
  while (1) {
    printf("Enter an integer: ");
    if (!fgets(input, sizeof(input), stdin))
      break; // error
    len = strlen(input);
    if (len == 1)
      break;                    // user pressed enter without input
    if (len > MAX_DIGITS + 1) { // input too long
      printf("Must be less than 10 digits \n");
      continue;
    }
    for (int i = 0; i < len - 1; i++) { // convert input to digits
      if (input[i] < '0' || input[i] > '9') {
        printf("Invalid input: %c\n", input[i]);
        break;
      }
      print_digit(input[i] - '0'); // converts to a numeric val
    }
  }
  return 0; // every main in good practice
}
