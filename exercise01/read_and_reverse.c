#include <stdio.h>  //printf and scanf
#include <string.h> //for strlen
void reverse_function(char givenString[]) {
  int len = strlen(givenString);
  for (int i = len - 1; i >= 0; i--) {
    char value = givenString[i];
    printf("%c", value);
  }
}

int main(int argc, char *arg[]) {
  char givenString[50];
  printf("Enter a word: ");
  scanf("%s", givenString);
  printf("%s", givenString);
  printf("--->");
  // int len = strlen(given_string);
  reverse_function(givenString);
  printf("\n");
}

// in the future navigate to home directory and ls -a you should see .vimswp and
// then delete files in there rm <filename>
