#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
  int solution[6];
  int guess[6];
  int input;
  int index[6];
  int seed = 0;
  int err = 0;
  int matches = 0;
  int partialMatches = 0;
  int i = 0;
  
  while (err != 1) {
    printf("Enter the integer value of the seed for the game: ");
    err = scanf("%d", &seed);

    if (err != 1) {
      printf("Try again you made an error\n");
    }
    while (getc(stdin) != *"\n");
  }

  

  printf("For each turn enter 6 digits 0 <= digit <= 9\n");
  printf("Spaces or tabs in your response will be ignored.\n");

  srand(seed);
  
  for (int i=0; i < 6; i++) {
    guess[i] = 0;
    index[i] = 0;
    solution[i] = rand() % 10;
  }

  
  while (matches != 6) {
    i = 0;
    input = 0;

    while (i < 6) {
      if (i == 0) {
        printf("Enter your guess, 6 digits\n");
      } else {
        printf("You need to enter %d more digits to complete your guess\n", 6-i);
      }
      if (input != 0) {
        while (input != *"\n") {
          input = getc(stdin);
        };
      }
      while ((input = getc(stdin)) != *"\n") {
        if (i < 6)
          if (input == *" ") {
            continue;
          } else if (isdigit(input) == 0) {
            printf("ERROR: A character in your guess was not a digit or a white space\n");
            i = 0;
            break;
          } else {
            guess[i] = input - *"0";
            i++;
          }
      }
    }

    printf("Your guess was\n");
    matches = 0;
    partialMatches = 0;

    for (int i = 0; i < 6; i++) {
      printf("%2d", guess[i]); 
      index[i] = 0;
      if (solution[i] == guess[i]) {
        index[i] = 1;
        matches += 1;
      }
    }
    if (matches == 6) {
      break;
    }

    for (int i = 0; i < 6; i++) {
      if (index[i] != 1) {
        for (int j = 0; j < 6; j++) {
          if (index[j] == 0) {
            if (solution[i] == guess[j]) {
              index[j] = 2;
              partialMatches += 1;
              break;
            }
          }
        }
      }
    }

    printf("\n");

    printf("My response was\n");
    printf("%d matches %d partial matches\n", matches, partialMatches);
  }

  printf("\nYOU DID IT!!\n");

  return 0;
}