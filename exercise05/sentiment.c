// Paola O'Rourke
// Worked w/ Kiera

// I can conclude that the program never reaches the 2nd function or around this
// area since it never printed here or broke in gdb. The bug must be in the
// first function causing it to be stuck in a loop or it does not properly take
// in input.--> fixed, never checked for if word existed before.
//
// Current problem: returns 0.000, I deduce that this error is in an improperly
// contructed first function. It is also notable that dump sentiments does not
// affect running it. With this I know that it's the first function.

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
  if (!f) {
    fprintf(stderr, "Invalid pointer\n");
    exit(1);
  }
  if (sentiments) {
    free_map_values();
    map_free(&sentiments);
  }
  sentiments = map_create(MAP_SIZE);

  char buff[BUFFER_SIZE];
  int line_no = -1;
  while (fgets(buff, BUFFER_SIZE, f) != NULL) {
    line_no++;
    // allocates for comments
    if (buff[0] == '#') {
      continue;
    }

    char *pos = strtok(buff, "\t"); // the \t splits on tab
    char *id = strtok(NULL, "\t");
    char *pos_score = strtok(NULL, "\t");
    char *neg_score = strtok(NULL, "\t");
    char *word = strtok(buff, " "); // token for each word
    char *definition = strtok(NULL, "\t");

    // for scores later
    double positive_score = atof(pos_score);
    double negative_score = atof(neg_score);
    char *buff = word;
    while (buff != NULL && *buff != '\0') {
      char *word = strtok(buff, " "); // splitting up buff = "I hate mondays" on
                                      // the space
      char *pound_index = strchr(buff, '#');
      if (pound_index != NULL) {
        snprintf(word, pound_index - buff + 1, "%s", buff);
      } else {
        break; // for those without #
      }
      lower_and_strip(word);
      sentiment_t *senti;

      int inMap = map_get(sentiments, word, (void **)&senti);
      // inmap returns non zero if found
      if (inMap) { // if inmap found it
        senti->count++;
        senti->pos += (positive_score - senti->pos) / senti->count;
        senti->neg += (negative_score - senti->neg) / senti->count;
      } else {
        senti = (sentiment_t *)malloc(sizeof(sentiment_t));
        senti->pos = positive_score;
        senti->neg = negative_score;
        senti->count = 1;
        map_put(sentiments, word, senti);
      }

      // Get the next word from the list
      word = NULL;
      buff += strspn(buff, "\t");
      buff += strspn(buff, "\t");
    }
  }
}

void sentiment_stdin() {
  char buffer[BUFFER_SIZE]; // initial user input
  char input[BUFFER_SIZE];
  char *space = " "; // to split on space
  int mean;
  int new_value; // for the mean calculation
  char *token;
  double count; // number of words-- not sure this works/ reaches point where
                // can be utilized
  double the_mean = 0.0;

  // checks buffer is not null
  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
    input[strlen(input) - 1] = '\0'; // this part could not be needed-- but
                                     // takes off Null terminator of input
    size_t buffer_len = strlen(buffer);
    if (buffer[buffer_len - 1] == '\n') { // single quotes bc string literal

      buffer[buffer_len - 1] = '\0';
    }
    strncpy(input, buffer, BUFFER_SIZE);
    double the_mean = 0;
    char *token = strtok(input, space); // splits input based on space
    // token not null                              //
    while (token) {           // while token, element in buffer, is not null
      count += 1;             // used for mean later
      lower_and_strip(token); // lowercases all characters of token
      sentiment_t *senti;

      int in_map = map_get(sentiments, token, (void **)&senti);
      if (in_map) {
        new_value = senti->pos + senti->neg;
        the_mean = the_mean + (new_value - mean) /
                                  count; // count;- checking whether better
      }

      token = strtok(NULL, space); // goes to next one regardless
    }
    printf("%s: %f \n", buffer, the_mean); // should print
  }
  count = 0; // resets count to see how many words are in the buffer for mean
}

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
