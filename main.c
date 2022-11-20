#include "parser.h"
#include <time.h>

int main()
{
    int a = file_parser();

    // Initializing seed for random generation.
    // Using current time as seed will almost guaranty that we'll never have the same seed
    srand(time(0));

    printf("\n\t\t\t\tWelcome to our Random Sentence Generator !\n\n\n");

    menu();

    return 0;
}
