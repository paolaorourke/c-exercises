// Paola O'Rourke
// Worked w/ Kiera

#include "map.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE (1 << 14)
#define BUFFER_SIZE 2048

// Represents the sentiment value for a single word/term.
typedef struct sentiment_t {
  double pos; // mean positive sentiment for the term
  double neg; // mean negative sentiment for the term
  int count;  // number of times the term appears
} sentiment_t;

// Map from string words/terms to sentiment_t values.
map_t *sentiments = NULL;

// Convert a string to lower case and strip whitespace and punctuation.
//
// Resizes string by nulling the unused suffix.
void lower_and_strip(char *str) {
  char *t = str; // insert point
  char *c = str; // current char
  for (; *c; c++) {
    if (isalnum(*c)) {
      // convert to lowercase; append at insert point.
      *t = tolower(*c); // t <= c
      t++;
    }
  }
  // c is null terminator; cut end of string after alnum chars.
  while (t < c) {
    *(t++) = '\0';
  }
}

// Print a single entry in a map string -> sentiment_t.
void *print_map_entry(const char *key, void *value) {
  sentiment_t *v = value;
  printf("%s : +%f -%f (%d)\n", key, v->pos, v->neg, v->count);
  return value;
}

// Free a single value from a map.
void *free_map_value(const char *key, void *value) {
  free(value);
  return NULL;
}

// Free all values in a map.
void free_map_values() { map_apply(sentiments, free_map_value); }

// Print all sentiments in a map string -> sentiment_t.
void dump_sentiments() { map_apply(sentiments, print_map_entry); }

// Build a map string -> sentiment_t by parsing input file.
//
// Modifies sentiments map.
void build_sentiment_map(FILE *f) {
  if (sentiments) {
    free_map_values();
    map_free(&sentiments);
  }
  sentiments = map_create(MAP_SIZE);

  char buff[BUFFER_SIZE];
  int line_no = -1;
  while (fgets(buff, BUFFER_SIZE, f) != NULL) {
    line_no++;

    if (buff[0] == '#') {
      continue;
    }

    char *pos = strtok(buff, "\t");
    char *id = strtok(NULL, "\t");
    char *pos_score = strtok(NULL, "\t");
    char *neg_score = strtok(NULL, "\t");
    // char *words = strtok(NULL, "\t"); //dictionary for all words
    char words[14];                 // size of the array
    char *word = strtok(buff, " "); // token for each word
    words[0] = *word;               // no star bc already address/ pointer
    char *definition = strtok(NULL, "\t");
    // use STRTOK on while loop
    while (word != NULL) {
      char *word = strtok(buff, " "); // splitting up buff = "I hate mondays" on
                                      // the space
      char *pound_index = strchr(buff, '#');
      if (pound_index != NULL) {
        *pound_index = '\0';
      }
    }
    // fix this maybe within while of next line
    // index = variable that holds index
    while (word) {
      double *tempScore = malloc(sizeof(double));
      *tempScore = atof(pos_score) - atof(neg_score);

      // Add the word and its sentiment score to the map
      map_put(sentiments, word, tempScore);
      // printf("%s", word);
      // look at word as a string pointer
      // debug thing-  printf("%s", word); //

      // Get the next word from the list
      word = strtok(NULL, " ");
    }
  }
}
// POS<TAB>ID<TAB>PosScore<TAB>NegScore<TAB>Word#n Word#n Word#n
// ...<TAB>Definition OR # this line is a comment since it starts with #

void sentiment_stdin() {
  char buffer[BUFFER_SIZE];
  char input[BUFFER_SIZE];
  char *space = " ";
  int mean;
  int new_value = 0;
  char *token;
  int count = 0;
  float sum = 0;

  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
    strncpy(input, buffer, BUFFER_SIZE);
    input[strlen(input) - 1] = '\0';

    token = strtok(input, space); // each word
    printf("%s /n", token);       //
    while (token) {
      count += 1;
      lower_and_strip(token);
      sentiment_t *senti;
      int in_map = map_get(sentiments, token, (void **)&senti);

      if (in_map) {
        new_value = senti->pos + senti->neg;
        mean = mean + (new_value - mean) / count;

        // printf("%s: %c", buffer, mean);
      }
      token = strtok(NULL, space);
    }
    printf("%s: %c \n", buffer, mean);
    // else {
    //  printf("%s: %f\n", buffer, 0.0);
  }
  count = 0;
  sum = 0.0;
}
//}

// lower_and_strip - use to tokenize word when it has the value
// new_mean = old_mean + (new_value - old_mean) / count    
// lower_and_strip - use to tokenize word when it has the value
// new_mean = old_mean + (new_value - old_mean) / count

// Clean up - dump sentiments?

// stop here

void usage(char *name) {
  printf("Usage: %s <sentiment_file.txt>\n", name);
  exit(1);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Must supply filename.\n");
    usage(argv[0]);
  }

  FILE *f = fopen(argv[1], "r");
  if (!f) {
    perror("fopen");
    exit(1);
  }
  fprintf(stderr, "loading sentiment map...");
  // Build the map of sentiments...
  build_sentiment_map(f);
  fprintf(stderr, "loaded.\n");
  // if you want to get sentiments out of your map in order to debug:
  dump_sentiments();
  // Read sentiments from standard in...
  sentiment_stdin();
}
