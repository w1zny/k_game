#include <stdio.h>
#include <string.h>
#include "k.h"

void render(struct game *game) {
  for (int i = 0; i < SIZE; i++) {
    for (int h = 0; h < SIZE; h++) {
      printf("+---");
    }
    printf("+\n");
    for (int j = 0; j < SIZE; j++) {
      printf("| %c ", game->board[i][j]);
    }
    printf("|\n");
  }
  for (int h = 0; h < SIZE; h++) {
    printf("+---");
  }
  printf("+\nscore: %d\n\n", game->score);
}

