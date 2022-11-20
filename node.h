#ifndef NODE_H
#define NODE_H

#include "ht_list.h"

#define MAX 50

typedef struct s_gender_number
{
    // Gender based on character. 'M' for "Masculin", 'F' for "Féminin", 'B' for both
    char gender;

    // Number based on gender.'S' for "Singulier "P' for "Pluriel"
    char PL_SG;
} t_gender_number, *p_gender_number;

// Structure of a flexed (= fléchi) word node
typedef struct s_flexed_node
{
    char character;

    // Equals to 1 if the current character is the last one of the word, equals to 0 else
    int end_of_word;

    // Structure that will point to t_gender_number structures to know if the gender and number (Singulier/Pluriel) of the words
    p_gender_number p_gn;

    struct s_flexed_node *left, *mid, *right;
} t_flexed_node, *p_flexed_node;

// Structure of a base word node
typedef struct s_base_node
{
    char character;

    //   True (>= 1 and =/= 0) if this character is the last character of one of the word, also acts as a count of the
    // number of inflicted words in the inflicted tree
    int flexed_word_cpt;

    // Pointer that points towards flexed word structures
    p_flexed_node pn_flexed;
    struct s_base_node *left, *mid, *right;
} t_base_node, *p_base_node;

p_base_node create_base_node(char);
p_base_node insert_base_tree(p_base_node *root, p_cell ptr_word);
void ternary_search_tree_node_traversal(p_base_node, char *, int);
void traverse_flexed_node_ternary_search_tree(p_flexed_node, char *, int);
void ternary_search_tree_traversal(p_base_node);
void flexed_tree_traversal(p_flexed_node);
int ternary_search_tree_search(p_base_node, p_cell);
p_gender_number create_p_gender_number(t_ht_list *);
p_flexed_node *insert_to_inflicted_tree(p_flexed_node *root, p_cell word);
p_flexed_node create_inflicted_tst(char);
p_flexed_node inserte_flexed_node_from_list(p_flexed_node *, p_cell, t_ht_list *);

#endif