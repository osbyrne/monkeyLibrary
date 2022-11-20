#ifndef HT_LIST_H
#define HT_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_cell
{
    char character;
    struct s_cell *next;
} t_cell, *p_cell;

typedef struct s_std_list
{
    p_cell head, tail;
} t_ht_list, *p_ht_list;

p_cell create_cell(char);
p_ht_list create_list();
void add_tail_list(t_ht_list *, char);
void display_std_list(t_ht_list);
void display_to_word_void(t_ht_list);
void delete_list(t_ht_list);

#endif