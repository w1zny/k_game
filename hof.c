#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "hof.h"

#define BUFFER 50

int str_to_int(char str[]) {
  int result = 0;
  for (int i = 0; i < strlen(str); i++) {
    result *= 10;
    result += str[i]-'0';
  }
  return result;
}

int cmp(const void* p1, const void* p2) {
  struct player* player1 = (struct player*)p1;
  struct player* player2 = (struct player*)p2;

  return player2->score - player1->score;
}

int load(struct player list[]) {
  FILE *fp = fopen(HOF_FILE, "r");
  if (!fp) {
    return -1;
  }

  char buffer[BUFFER];
  size_t size = 0;
  while (!feof(fp)) {
    fgets(buffer, BUFFER, fp);
    size++;
  }
  size--;
  rewind(fp);

  struct player tmp_list[size];

  for (int i = 0; i < size; i++) {
    fgets(buffer, BUFFER, fp);
    char* token = strtok(buffer, DELIMITER);
    char* name = calloc(strlen(token)+1, sizeof(char));
    strcpy(name, token);
    token = strtok(NULL, "\n");
    char str_score[6];
    strcpy(str_score, token);
    int score = str_to_int(str_score);

    struct player p;
    strcpy(p.name, name);
    p.score = score;
    tmp_list[i] = p;
    free(name);
  }
  if (sizeof(tmp_list)/sizeof(struct player) == 0) {
    return 0;
  }

  qsort(tmp_list, size, sizeof(struct player), cmp);
  size_t boundry = ((size_t)10 > size) ? size : 10;
  int i;
  for (i = 0; i < boundry; i++) {
    list[i] = tmp_list[i];
  }

  fclose(fp);
  return (int)boundry;
}

void switch_equal_players(struct player list[], int *size, struct player player) {
  for (int i = 1; i < *size; i++) {
    if (strcmp(list[i].name, player.name) == 0 &&
        list[i].score == player.score &&
				list[i-1].score == list[i].score) {
      struct player tmp = list[i-1];
      list[i-1] = list[i];
      list[i] = tmp;
    }
  }
}

bool add_player(struct player list[], int* size, const struct player player) {
  if (*size < 10) {
    list[*size] = player;
    *size += 1;
    qsort(list, (size_t)*size, sizeof(struct player), cmp);
    switch_equal_players(list, size, player);
    return true;
  }
  if (list[*size-1].score <= player.score) {
    list[*size-1] = player;
    qsort(list, (size_t)*size, sizeof(struct player), cmp);
    switch_equal_players(list, size, player);
    return true;
  }
  return false;
}

bool save(const struct player list[], const int size) {
  if (!list) {
    return false;
  }
  FILE *fp = fopen(HOF_FILE, "w");
  for (int i = 0; i < size; i++) {
    fprintf(fp, "%s %d\n", list[i].name, list[i].score);
  }
  fclose(fp);
  return true;
}

