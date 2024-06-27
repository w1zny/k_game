#include "k.h"
#include "hof.h"
#include "ui.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
  /*
  struct game game = {
    .board = {
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    .score = 0
  };
  struct game game = {
    .board = {
      {'A', ' ', 'H', 'C'},
      {' ', ' ', ' ', ' '},
      {' ', 'C', ' ', 'J'},
      {' ', 'F', 'F', 'C'}
    },
    .score = 90
  };
  struct game game = {
    .board = {
      {'G', 'J', ' ', 'J'},
      {'E', 'G', ' ', 'H'},
      {'H', 'E', ' ', ' '},
      {'J', ' ', ' ', 'H'}
    },
    .score = 8527
  };
	*/
  struct game game = {
    .board = {
        {'A', ' ', ' ', ' '},
        {'B', 'A', ' ', ' '},
        {'A', 'F', ' ', ' '},
        {'C', ' ', ' ', ' '}
    },
    .score = 0
  };

  
  

  while (!is_game_won(game) && is_move_possible(game)) {
    render(game);
    int dy, dx;
    printf("dy dx: ");
    scanf("%d %d", &dy, &dx);
    printf("%d\n", update(&game, dy, dx));

  }
  render(game);
  add_random_tile(&game);
  if (is_game_won(game)) {
    printf("YOU WON!\n");
  }
  else {
    printf("YOU LOST!\n");
  }
  
  struct player list[10];
  int size = load(list);
  for (int i = 0; i < size; i++) {
    printf("%s %d\n", list[i].name, list[i].score);
  }
  printf("\n");
  struct player player = {
    .name = "John",
    .score = 950
  };

  add_player(list, &size, player);
  for (int i = 0; i < size; i++) {
    printf("%s %d\n", list[i].name, list[i].score);
  } 
  save(list, size);
  return 0;
}
