#include "node.h"

// Global Variable t_ht_list pointer variables
t_ht_list *typelistt = NULL;

// Creation of Ternary Search Tree from base form
p_base_node create_base_tst(char data)
{
    p_base_node temp = (p_base_node)malloc(sizeof(t_base_node));
    temp->character = data;
    temp->flexed_word_cpt = 0;
    temp->pn_flexed = NULL;
    temp->left = temp->mid = temp->right = NULL;

    return temp;
}

// Recursive Function to insert to baseTree a new ptr_word in a Ternary Search Tree
p_base_node insert_base_tree(p_base_node *root, p_cell ptr_word)
{
    // Base Case: Tree is empty
    if (!(*root))
        *root = create_base_tst(ptr_word->character);
    else if (!(*root)->character)
        (*root)->character = ptr_word->character;

    // Insert left if character of node to insert is lesser than current node
    if ((ptr_word->character) < (*root)->character)
        insert_base_tree(&((*root)->left), ptr_word);

    // Insert right if character of node to insert is greater than current node
    else if ((ptr_word->character) > (*root)->character)
        insert_base_tree(&((*root)->right), ptr_word);

    // If characters are the same
    else
    {
        if (ptr_word->next)
            insert_base_tree(&((*root)->mid), ptr_word->next);

        // If it become the last character (ptr_word->next == NULL)
        else
        {
            (*root)->flexed_word_cpt++;

            // since all base forms has inflicted forms in the dictionary check if the inflicted tree pointer is not null
            // else create new inf_tree with no values(to be determined in the other function)
            if (!(*root)->pn_flexed)
            {
                (*root)->pn_flexed = (p_flexed_node)malloc(sizeof(t_flexed_node));
                (*root)->pn_flexed->end_of_word = 0;
                (*root)->pn_flexed->left = (*root)->pn_flexed->mid = (*root)->pn_flexed->right = NULL;
                (*root)->pn_flexed->p_gn = NULL;
            }
            return (*root);
        }
    }
}

// A recursive function to traverse Ternary Search Tree
void ternary_search_tree_node_traversal(p_base_node root, char *buffer, int depth)
{
    if (root)
    {
        // First traverse the left subtree
        ternary_search_tree_node_traversal(root->left, buffer, depth);

        // Store the character of this node
        buffer[depth] = root->character;
        if (root->flexed_word_cpt)
        {
            buffer[depth + 1] = '\0';
            printf("%s\n", buffer);
        }

        // Traverse the subtree using mid_eq pointer (middle subtree)
        ternary_search_tree_node_traversal(root->mid, buffer, depth + 1);

        // Finally Traverse the right subtree
        ternary_search_tree_node_traversal(root->right, buffer, depth);
    }
}

// The main function to traverse a Ternary Search Tree.
// It mainly uses ternary_search_tree_node_traversal()
void ternary_search_tree_traversal(p_base_node root)
{
    char buffer[MAX];
    if (root != NULL)
        ternary_search_tree_node_traversal(root, buffer, 0);
}

// A recursive function to traverse Ternary Search Tree
void traverse_flexed_node_ternary_search_tree(p_flexed_node root, char *buffer, int depth)
{
    if (root)
    {
        // First traverse the left subtree
        traverse_flexed_node_ternary_search_tree(root->left, buffer, depth);

        // Store the character of this node
        buffer[depth] = root->character;
        if (root->end_of_word)
        {
            buffer[depth + 1] = '\0';
            printf("%s\n", buffer);
        }

        // Traverse the subtree using mid_eq pointer (middle subtree)
        traverse_flexed_node_ternary_search_tree(root->mid, buffer, depth + 1);

        // Finally Traverse the right subtree
        traverse_flexed_node_ternary_search_tree(root->right, buffer, depth);
    }
}

// The main function to traverse a Ternary Search Tree.
// It mainly uses ternary_search_tree_node_traversal()
void flexed_tree_traversal(p_flexed_node root)
{
    char buffer[MAX];
    if (root != NULL)
        traverse_flexed_node_ternary_search_tree(root, buffer, 0);
}

// Function to search a given word in TST
int ternary_search_tree_search(p_base_node root, p_cell word)
{
    if (!root)
        return 0;

    if (word->character < (root)->character)
        return ternary_search_tree_search(root->left, word);

    else if (word->character > (root)->character)
        return ternary_search_tree_search(root->right, word);

    else
    {
        if (!(word->next))
        {

            return root->flexed_word_cpt;
        }

        return ternary_search_tree_search(root->mid, word->next);
    }
}

// Creation of the flexed form node tree
p_flexed_node create_inflicted_tst(char c)
{
    p_flexed_node temp = (p_flexed_node)malloc(sizeof(t_flexed_node));
    temp->character = c;
    temp->end_of_word = 0;
    temp->left = temp->mid = temp->right = NULL;
    temp->p_gn = NULL;
    return temp;
}

p_flexed_node inserte_flexed_node_from_list(p_flexed_node *root, p_cell word, t_ht_list *typelist)
{
    typelistt = typelist;
    return (*insert_to_inflicted_tree(root, word));
}

p_flexed_node *insert_to_inflicted_tree(p_flexed_node *root, p_cell word)
{
    // Base Case: Tree is empty
    if (!(*root))
        *root = create_inflicted_tst(word->character);
    else if (!(*root)->character)
        (*root)->character = word->character;
    // If current character of word is smaller than root's character,
    // then insert_base_tree this word in left subtree of root
    if ((word->character) < (*root)->character)
        insert_to_inflicted_tree(&((*root)->left), word);

    // If current character of word is greater than root's character,
    // then insert_base_tree this word in right subtree of root
    else if ((word->character) > (*root)->character)
        insert_to_inflicted_tree(&((*root)->right), word);

    // If current character of word is same as root's character,
    else
    {
        if (word->next)
            insert_to_inflicted_tree(&((*root)->mid), word->next);

        // If it is the last character of the word
        else
        {
            (*root)->end_of_word++;
            if (!(*root)->p_gn)
            {
                ((*root)->p_gn) = create_p_gender_number(typelistt);
            }

            return root;
        }
    }
}
// Creation of p_gender_number type
p_gender_number create_p_gender_number(t_ht_list *typelist)
{
    p_gender_number temp = (p_gender_number)malloc(sizeof(t_gender_number));
    p_cell temp_2 = typelist->head;
    while (temp_2 && !(temp->PL_SG && temp->gender))
    {
        switch (temp_2->character)
        {
        case 'P':
            if (temp_2->next && temp_2->next->character == 'L')
                temp->PL_SG = 'P';
            break;
        case 'S':
            if (temp_2->next && temp_2->next->character == 'G')
                temp->PL_SG = 'S';
            break;
        case 'M':
            temp->gender = 'M';
            break;
        case 'F':
            if (temp_2->next && temp_2->next->character == 'e')
                temp->gender = 'F';
            break;
        default:
            break;
        }
        temp_2 = temp_2->next;
    }

    if (!temp->PL_SG)
        temp->PL_SG = 'B';

    if (!temp->gender)
        temp->gender = 'B';

    return temp;
}
