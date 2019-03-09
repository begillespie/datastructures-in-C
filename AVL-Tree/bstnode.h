/**
 * @file bstnode.h
 * @author Brian Giillespie
 *
 * Defines a struct for a node in a binary tree
 */

#ifndef BSTNODE_H
#define BSTNODE_H

/**
 * Defines a node in a binary tree.
 */
typedef struct BSTNode {
    /** Key for this node */
    int key;
    /** Value stored in this node */
    void *value;
    /** Height of this node */
    int height;
    /** Pointer to the left subtree */
    struct BSTNode *left;
    /** Pointer to the right subtree */
    struct BSTNode *right;
} BSTNode;

#endif
