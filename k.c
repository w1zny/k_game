#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "k.h"
#include "ui.h"

void add_random_tile(struct game *game){
    int free = 0;
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        if (game->board[i][j] == ' ') {
          free++;
        }
      }
    }
    if (!free) {
      return; 
    }

    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (game.board[i][j] == 'K') {
        return true;
      }
    }
  }
  return false;
}

bool is_move_possible(const struct game game) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      char ch = game.board[i][j];
      if (ch == ' ') {
        return true;
      }
      bool r, l, u, d;
      r = (j == 3) ? false : true;
      l = (j == 0) ? false : true;
      u = (i == 0) ? false : true;
      d = (i == 3) ? false : true;
      if ((d && game.board[i+1][j] == ch) || (u && game.board[i-1][j] == ch) ||
          (r && game.board[i][j+1] == ch) || (l && game.board[i][j-1] == ch)) {
        return true;
      }
    }
  }
  return false;
}

void perform_hor_move(
  struct game *game, int ptr, int boundry, bool boundry_up, int d) {
  for (int i = 0; i < SIZE; i++) {
    int tmp = ptr;
    int start = ptr;
    while ((boundry_up && tmp <= boundry) || (!boundry_up && tmp >= boundry)) {
      char ch = game->board[i][tmp];
      if (ch == ' ') {
        tmp -= d;
        continue;
      }
      game->board[i][tmp] = ' ';
      game->board[i][start] = ch;
      if (start+d >= 0 && start+d < SIZE &&
          game->board[i][start+d] == ch) {
        game->board[i][start] = ' ';
        game->board[i][start+d] = (char)((int)game->board[i][start+d]+1);
        game->score += (int)pow(2, (int)game->board[i][start+d]-'A'+1);
        continue;
      }
      start -= d;
      tmp -= d;
    }
  }
}

void perform_ver_move(
  struct game *game, int ptr, int boundry, bool boundry_up, int d) {
  for (int i = 0; i < SIZE; i++) {
    int tmp = ptr;
    int start = ptr;
    while ((boundry_up && tmp <= boundry) || (!boundry_up && tmp >= boundry)) {
      char ch = game->board[tmp][i];
      if (ch == ' ') {
        tmp -= d;
        continue;
      }
      game->board[tmp][i] = ' ';
      game->board[start][i] = ch;
      if (start+d >= 0 && start+d < SIZE &&
          game->board[start+d][i] == ch) {
        game->board[start][i] = ' ';
        game->board[start+d][i] = (char)((int)game->board[start+d][i]+1);
        game->score += (int)pow(2, (int)game->board[start+d][i]-'A'+1);
        continue;
      }
      start -= d;
      tmp -= d;
    }
  }
}

void cpy_game(struct game *screen, struct game *game) {
	screen->score = game->score;
	for (int i = 0; i <SIZE; i++) {
		for (int j = 0; j <SIZE; j++) {
			screen->board[i][j] = game->board[i][j];
		}
	}
}

bool cmp_board(struct game *game, struct game *screen) {
	int diff = 0;
	for (int i = 0; i <SIZE; i++) {
		for (int j = 0; j <SIZE; j++) {
			if (game->board[i][j] != screen->board[i][j]) {
				diff++;
			}
		}
	}
	if (diff != 0) {
		return false;
	}
	return true;
}

bool update(struct game *game, int dy, int dx) {
  if ((!dy && !dx) || (dy && dx) || (dy && abs(dy) != 1) || (dx && abs(dx) != 1)) {
    return false;
  }
	struct game *screen = calloc(1, sizeof(struct game));
	cpy_game(screen, game);
  if (dx == 1) {
    perform_hor_move(game, SIZE-1, 0, false, dx);
  }
  else if (dx == -1) {
    perform_hor_move(game, 0, SIZE-1, true, dx);
  }
  else if (dy == 1) {
    perform_ver_move(game, SIZE-1, 0, false, dy);
  }
  else if (dy == -1) {
    perform_ver_move(game, 0, SIZE-1, true, dy);
  }
	bool is_moved = cmp_board(game, screen);	
	free(screen);
	return (is_moved) ? false : true;

}

