#include "ht_list.h"

p_cell create_cell(char c)
{
    p_cell new_cell = (p_cell)malloc(sizeof(t_cell));
    new_cell->character = c;
    new_cell->next = NULL;
}

p_ht_list create_list()
{
    p_ht_list ht_list = (p_ht_list)malloc(sizeof(t_ht_list));
    ht_list->head = ht_list->tail = NULL;

    return ht_list;
}

void add_tail_list(t_ht_list *list, char c)
{
    p_cell new_cell = create_cell(c);

    if (list->head == NULL || list->tail == NULL)
    {
        list->head = new_cell;
        list->tail = list->head;
        list->head->next = NULL;
    }
    else
    {
        list->tail->next = new_cell;
        list->tail = list->tail->next;
    }
    list->tail->next = NULL;
}

void display_std_list(t_ht_list ht_list)
{
    p_cell temp = ht_list.head;
    printf("list [head @-]");
    if (temp != NULL)
    {
        do
        {
            printf("-->[ %c | @-]", temp->character);
            temp = temp->next;
        } while (temp != NULL);
    }

    printf("-->NULL\n");
}

// Function that frees all the memory allocated to an ht_list
void delete_list(t_ht_list ht_list)
{
    p_cell current = ht_list.head;
    p_cell next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    // Now that all cells contained in the ht_list are freed, we set head and tail to NULL
    ht_list.head = ht_list.tail = NULL;
}

void display_to_word_void(t_ht_list ht_list)
{
    p_cell temp = ht_list.head;
    if (temp != NULL)
    {
        do
        {
            printf("%c", temp->character);
            temp = temp->next;
        } while (temp != NULL);
    }
    printf(" ");
}