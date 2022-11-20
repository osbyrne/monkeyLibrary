#include <stdio.h>
#include <time.h>
#include "parser.h"
// Sleep function (already included in <stdio.h> but we include the below library so it can also work on Linux platform)
#include <unistd.h>

// Global variables
p_base_node verb = NULL, noun = NULL, adjective = NULL, adverb = NULL;

// Reads from the file and parses it into base form ,flexed form,type(verb,adj,adv,noun)
int file_parser()
{
    FILE *dictionary;
    int c, end = 0, list = 0;
    dictionary = fopen("dictionnaire_non_accentue.txt", "r");

    if (dictionary == NULL)
    {
        perror("Error in opening file");
        return (-1);
    }

    // List creation for each kind of words (flexed, base and type (gender/number))
    t_ht_list *flexed = create_list();
    t_ht_list *base = create_list();
    t_ht_list *type = create_list();
    // Temporary pointer to know where to insert_base_tree the characters
    t_ht_list *temp = flexed;

    // the variable "end" acts a boolean. If it is equal to 1, then we reached the EOF
    while (end == 0)
    {
        do
        {
            c = fgetc(dictionary);
            if (feof(dictionary))
            {
                end = 1;
                break;
            }
            // printf("%c", c);
            if (c == 9 || c == 10)
                break;
            else
                add_tail_list(temp, c);
        } while (1);

        // Switch case to know the current stage of the word
        // Since the dictionary is written (0) flexed form (1)base form (2)type
        switch (list)
        {
        case 0:
            list = 1;
            temp = base;
            break;
        case 1:
            list = 2;
            temp = type;
            break;
        default:
            list = 0;
            // we are now case 2, so now we can populate the tree since we have got all the words in a line
            insert_all(base, flexed, type);
            // deletelist frees the linked lists since we are using dynamic arrays and we no longer need it
            delete_list(*flexed);
            delete_list(*base);
            delete_list(*type);
            flexed = create_list();
            base = create_list();
            type = create_list();
            temp = flexed;
            break;
        }
    }
    // finished reading the file close it
    fclose(dictionary);
    return (0);
}

// very key function that inserts values from lists into the correct type of trees
void insert_all(t_ht_list *baselist, t_ht_list *flexedlist, t_ht_list *typelist)
{
    p_base_node temp = NULL;
    switch (typelist->head->character)
    {
    case 'V':
        // we assume the word is a verb
        temp = insert_base_tree(&(verb), baselist->head);
        inserte_flexed_node_from_list(&(temp->pn_flexed), flexedlist->head, typelist);

        break;
    case 'N':
        // we assume the word is a noun
        temp = insert_base_tree(&(noun), baselist->head);
        inserte_flexed_node_from_list(&(temp->pn_flexed), flexedlist->head, typelist);
        break;
    case 'A':
        if (typelist->head->next->next->character && typelist->head->next->next->character == 'j')
        {
            // we assume the word is an adjective
            temp = insert_base_tree(&(adjective), baselist->head);
            inserte_flexed_node_from_list(&(temp->pn_flexed), flexedlist->head, typelist);
        }
        else
        {
            // we assume the word is an adverb
            temp = insert_base_tree(&(adverb), baselist->head);
            inserte_flexed_node_from_list(&(temp->pn_flexed), flexedlist->head, typelist);
        }
        break;
    }
}

t_ht_list *random_generator(p_base_node root)
{
    t_ht_list *word = create_list();
    // srand(time(0));
    int y, i, stop = 0, ismiddle = 0;
    p_base_node temp = root;

    while (!stop)
    {

        // srand(time(0));
        if (temp)
        {
            y = rand() % 26;
            for (int j = 0; temp->right && j < y; ++j)
            {
                temp = temp->right;
            }

            i = rand() % 3;
            // printf("temp->data--->%c\n",temp->data);
            switch (i)
            {
            case 0:
                if (temp->left)
                {
                    // printf("temp=temp->left no null\n");
                    temp = temp->left;
                }
                else
                {
                    if (temp->right && rand() % 3 != 0)
                    {
                        // printf("rand no--->0 left=null and temp=temp->right \n");
                        temp = temp->right;
                    }
                    else
                    {
                        // printf("rand no--->1or temp->right is null left=null and temp=temp->mid_eq/n");
                        ismiddle = 1;
                    }
                    // temp=temp->mid_eq;}
                }
                break;
            case 1:
                ismiddle = 1;
                break;
            case 2:
                if (temp->right)
                {

                    // printf("temp=temp->right no null\n");
                    temp = temp->right;
                }
                else
                {
                    if (temp->left && rand() % 2 == 0)
                    {
                        // printf("rand no--->0 right=null and temp=temp->left \n");
                        temp = temp->left;
                    }
                    else
                    {
                        // printf("rand no--->1 or templeft is null rigth=null and temp=temp->mid_eq\n");
                        ismiddle = 1;
                    }
                    // temp=temp->mid_eq;}
                }
                break;
            default:
                // printf("to be solved");
                stop = 1;
                break;
            }
            if (temp->flexed_word_cpt != 0 && ismiddle)
            {
                if (rand() % 3 == 0)
                {
                    // printf("**************rand =0 letter to be added--->%c\n",temp->data);
                    add_tail_list(word, temp->character);
                    stop = 1;
                }
                else
                { /*
                 printf("************rand=1 letter to be added--->%c\n",temp->data);*/
                    add_tail_list(word, temp->character);
                    // if(ismiddle){
                    ismiddle = 0;
                    temp = temp->mid; // }
                }
            }
            else if (ismiddle)
            { /*
printf("middle no null and temp=temp->mid_eq\n");
printf("************rand=1 letter to be added--->%c\n",temp->data);*/
                add_tail_list(word, temp->character);
                ismiddle = 0;
                temp = temp->mid;
            }
        }
        else
        {
            stop = 1;
        }
    }
    return word;
}

void modelling()
{
    int i = 0;
    printf("\nWhich model do you wish to display ?\n\n");
    printf(" \t1) First form\t\"nom – adjectif – verbe – nom\"\n"
           "\t2) Second form\t\"nom – ‘qui’ – verbe – verbe – nom – adjectif\n"
           "\t3) Third form\t\"nom - adverbe - adjectif - verbe\"\n"
           "\t4) Back\n");

    scanf("%d", &i);
    if (i == 1)
    {
        display_to_word_void(*random_generator(noun));
        display_to_word_void(*random_generator(adjective));
        display_to_word_void(*random_generator(verb));
        display_to_word_void(*random_generator(noun));
    }

    if (i == 2)
    {
        display_to_word_void(*random_generator(noun));
        printf(" qui ");
        display_to_word_void(*random_generator(verb));
        display_to_word_void(*random_generator(verb));
        display_to_word_void(*random_generator(noun));
        display_to_word_void(*random_generator(adjective));
    }

    if (i == 3)
    {
        display_to_word_void(*random_generator(noun));
        display_to_word_void(*random_generator(adverb));
        display_to_word_void(*random_generator(adjective));
        display_to_word_void(*random_generator(verb));
    }

    printf("\n\n");
}
int menu()
{
    int choice;

    while (1)
    {
        choice = 6;
        do
        { // SAISIE SECU
            printf("Thanks to this program, you're able to:\n");
            printf("\t1) Search words from the tree\n"
                   "\t2) Print all the base words in the tree\n"
                   "\t3) Generate Randoms Sentence\n"
                   "\t4)Quit\n\n");
            printf("What would you like to do ?\n");

            scanf("%d", &choice);
        } while (choice < 0 || choice > 4);
        switch (choice)
        {
        case 1:
            printf("This part is not developped yet...\n\n");
            // fonctions
            // return second_menu();
            break;
        case 2:
            print_tree();

            break; // return second_menu();
        case 3:
            modelling();
            return menu();
            break;
        case 4:
            printf("\n\nSee you next time !\n");
            return 0;
            break;
        default:
            printf("incorrect type of value given!!  Please enter numbers not characters\n");
            // menu();
            choice = 5;
            return -1;
            break;
        }
    }
}

void autocomplete(p_base_node root, p_cell word)
{
    if (!word)
        return;

    // Iterating over the characters
    // of the pattern and find it's
    // corresponding node in the tree

    while (root && word)
    {

        // If current character is smaller
        if (root->character > word->character)
            // Search the left subtree
            root = root->left;

        // current character is greater
        else if (root->character < word->character)
            // Search right subtree
            root = root->right;

        // If current character is mid_eq
        else if (root->character == word->character)
        {

            // Search mid subtree
            // since character is found, move to the next character in the pattern
            root = root->mid;
            word = word->next;
        }
        // If not found
        else
            return;
    }
    if (root)
        printf("kkkkkkkkkkkkkkkkkkkkkkk");

    printf("---------------");
    ternary_search_tree_traversal(root);
}

void print_tree()
{
    printf("\n");
    printf("Below is the display of the traversal of the noun ternary search tree\n");
    sleep(2);
    ternary_search_tree_traversal(noun);
    printf("\n");

    printf("Below is the display of the traversal of the adjective ternary search tree\n");
    sleep(3);
    ternary_search_tree_traversal(adjective);
    printf("\n");

    printf("Below is the display of the traversal of the adverb ternary search tree\n");
    sleep(3);
    ternary_search_tree_traversal(adverb);
    printf("\n");

    printf("Below is the display of the traversal of the verb ternary search tree\n");
    sleep(3);
    ternary_search_tree_traversal(verb);
    printf("\n\n");
}