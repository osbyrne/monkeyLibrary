#include <stdio.h>
#include <stdio.h>
#include <time.h>

typedef struct list {
  char* word;
  struct listNode *next;
}t_list  ;

typedef struct bTree {
  char letter;
  struct bTreeNode *left;
  struct bTreeNode *right;
}t_tree;

char phraseModels[7][5][7] = {
  {"nom", "adjectif", "verbe", "nom"},
  {"foo", "qui", "verbe", "verbe", "nom", "adjectif"},
  {"adjectif", "nom", "verbe", "adverbe", "adjectif", "nom"}
};

int randIntRange(int min, int max) {
  srand(time(0));
  return (rand() % (max - min + 1)) + min;
}

void main() {
  printf("Welcome; let's generate some random phrases!\n");
  printf("To do so, we need to choose a phrase structure:\n");
  printf("\n");
  int randModel = randIntRange(0, 2);
  printf("First let's randomly choose a phrase structure,\nfrom the three we have:\nChosen number: %d\n", randModel);
  printf("\n");
  printf("let's see our model:\n");
  
  phraseModels[randModel]
}