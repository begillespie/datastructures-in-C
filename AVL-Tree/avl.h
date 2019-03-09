/**
 * @file avl.h
 * @author Brian Giillespie
 *
 * Prototypes and structs for public AVL Tree functions
 */

/**
 * Defines a node in a binary tree.
 */

#ifndef AVL_H
#define AVL_H

#include "bstnode.h"
#include <stdbool.h>

/**
 * Struct to hold an AVL tree. Because the root could change when
 * manipulating the tree, this allows the calling code to use a constant
 * pointer to refer to the tree, as opposed to keeping track of the
 * root node.
 */
typedef struct AVLTree {
    /** Root note of the tree */
    BSTNode *root;
} AVLTree;

/**
 * Creates a new, empty tree
 *
 * @return pointer to a new tree
 */
AVLTree *createAVLTree();

/**
 * Frees all memory associated with the given tree
 *
 * @param *tree the tree to free
 */
void freeTree(AVLTree *tree);

/**
 * Inserts a new node into the tree
 *
 * @param key the key of this node
 * @param *value pointer to the value to store
 * @param *tree pointer to the tree to insert into
 *
 * @return true if the insertion is successful
 */
bool insert_avl(int key, void *value, AVLTree *tree);

/**
 * Removes a node from the tree based on its key and returns its value.
 *
 * @param key the key of the tree to remove
 * @param *tree the tree to delete from
 *
 * @return pointer to the value of the deleted node, or NULL if the key
 * was not found.
 */
void *delete_avl(int key, AVLTree *tree);

/**
 * Locates the key in the tree and returns a pointer to the value. THe
 * node is not removed.
 *
 * @param key the key of the tree to remove
 * @param *tree the tree to delete from
 *
 * @return pointer to the value of the deleted node, or NULL if the key
 * was not found.
 */
void *lookup_avl(int key, AVLTree *tree);

/**
 * Prints the tree.
 *
 * @param *tree the tree to print
 */
void print_tree(AVLTree *tree);

#endif
