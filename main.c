#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct BinTree
{
  char letter;
  struct bTree *left;
  struct bTree *right;
} btree;

typedef struct Word
{
  char *content;
  struct Word *next;
} word;

typedef struct CharList
{
  struct NaryTree *descend;
  struct CharList *peer;
} charList;

typedef struct NaryTree
{
  char letter;
  charList childrenPointers;
  int charListLength;
} ntree;

int randIntRange(int min, int max)
{
  srand(time(0));
  return (rand() % (max - min + 1)) + min;
}

char phraseModels[3][6][8] = {
    {"nom", "adjectif", "verbe", "nom"},
    {"nom", "qui", "verbe", "verbe", "nom", "adjectif"},
    {"adjectif", "nom", "verbe", "adverbe", "adjectif", "nom"}};

int main()
{
  printf("Welcome; let's generate some random phrases!\n");
  printf("here is our set of phrase structures:\n");
  int nPhraseModel = randIntRange(0, 2);
  printf("%d is the number of the chosen phrase structure\n", nPhraseModel);

  return 0;
}