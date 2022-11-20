#ifndef PARSER_H
#define PARSER_H

#include "node.h"

int file_parser();
void insert_all(t_ht_list *, t_ht_list *, t_ht_list *);
t_ht_list *random_generator(p_base_node);
int menu();
void autocomplete(p_base_node, p_cell);
void print_tree();
void modelling();

#endif