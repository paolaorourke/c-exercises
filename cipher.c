// Kata 02
// Paola O'Rourke
//
#include <ctype.h>
#include <printf.h> //
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1020 // max characters

int main(int argc, char *argv[]) {
  char substitution_table[26], ciphered[MAXLEN], c;
  int i, j, len, space;

  printf("Enter the substitution table: ");
  fgets(substitution_table, 27, stdin);

  // asks user for text, this variable = ciphered
  printf("Enter the text to encrypt: (control C to quit) ");
  fgets(ciphered, MAXLEN, stdin);
  len = strlen(ciphered);

  // Remove the newline character at the end of text variable
  if (ciphered[len - 1] == '\n')
    ciphered[len - 1] = '\0';

  // Encrypt each word in the input string
  space = 0;
  while (fgets(ciphered, MAXLEN, stdin)) { // stores stdin from user into
                                           // ciphered
    len = strlen(ciphered);
    if (ciphered[len - 1] == '\n')
      ciphered[len - 1] = '\0';
    for (i = 0; i < len; i++) {
      c = ciphered[i]; // c = character of text
      if (c >= 'a' && c <= 'z') {
        j = c - 'a'; // finds distance between table and text
        ciphered[i] = substitution_table[j];
      } // only worries about lowercase
    }
    if (space) // allocates the spaces
      printf(" ");
    printf("%s", ciphered);
    space = 1; // set space to one after word printed so next has space
  }
  printf("\n"); // new line

  return 0;
}
