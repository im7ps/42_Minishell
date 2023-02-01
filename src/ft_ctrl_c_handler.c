#include "../inc/minishell.h"

#define PROMPT "myshell> "

void sigint_handler(int signum) {
  printf("\n%s", PROMPT);
  fflush(stdout);
}

int main(int argc, char *argv[]) {
  char line[1024];

  signal(SIGINT, sigint_handler);

  printf("%s", PROMPT);
  while (fgets(line, sizeof(line), stdin) != NULL) {
    // process the input
    printf("You entered: %s", line);
    printf("%s", PROMPT);
  }

  return 0;
}
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROMPT "myshell> "

void sigint_handler(int signum) {
  printf("\n%s", PROMPT);
  fflush(stdout);
}

int main(int argc, char *argv[]) {
  char line[1024];

  signal(SIGINT, sigint_handler);

  printf("%s", PROMPT);
  while (fgets(line, sizeof(line), stdin) != NULL) {
    // process the input
    printf("You entered: %s", line);
    printf("%s", PROMPT);
  }

  return 0;
}
