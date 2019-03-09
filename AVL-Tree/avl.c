/**
 * @file avl.c
 * @author Brian Gillespie
 *
 * Implementation of a self-balanding AVL tree. This is a binary tree
 * that uses rotations to balance the height of subtrees. The height of
 * the left and right subtree of any given node can differ in height by
 * no more than one. This tree uses integer keys and void pointers for
 * values.
 */

#include "avl.h"
#include "bstnode.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/** Evaluates to the maximum of two values */
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/** Number of spaces to indent tree levels */
#define INDENT 5

/* Static function prototypes */
static int height(BSTNode *node);
static void freeNode(BSTNode *node);
static BSTNode *insert_node(int key, void *value, BSTNode *root);
static void *lookup(int key, BSTNode *tree);
static BSTNode *rotateRight(BSTNode *node);
static BSTNode *rotateLeft(BSTNode *node);
static void print_nodes(BSTNode *root, int indent);

/** Documented in avl.h */
AVLTree *createAVLTree() {
    AVLTree *tree = malloc(sizeof(AVLTree));
    if (tree) {
        tree->root = NULL;
    }
    return tree;
}

/** Documented in avl.h */
void freeTree(AVLTree *tree) {
    if (tree == NULL) {
        return;
    }
    freeNode(tree->root);
    free(tree);
}

/**
 * Performs a postorder traversal of the tree, freeing all nodes.
 *
 * @param node pointer to the root node of the subtree to free
 */
static void freeNode(BSTNode *node) {
    if (node == NULL) {
        return;
    }
    freeNode(node->left);
    freeNode(node->right);
    free(node);
}

/**
 * Returns the height field of the given node, or 0 if the node is NULL.
 *
 * @param *node
 *      the node to find the height of
 *
 * @return the height of node n
 */
static int height(BSTNode *node)
{
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

/** Documented in avl.h */
bool insert_avl(int key, void *value, AVLTree *tree) {
    if (tree) {
        tree->root = insert_node(key, value, tree->root);
        return true;
    }
    return false;
}

/**
 * Internal function for node insertion.
 *
 * @param *root root node of the subtree
 * @param key key to insert
 * @param value value to insert
 *
 * @return pointer to the root node of the tree after insertion
 */
static BSTNode *insert_node(int key, void *value, BSTNode *root) {
    if (root == NULL) {
        BSTNode *node = malloc(sizeof(BSTNode));
        /* A leaf node gets a height of 1 and a NULL node gets a height of 0,
            to ensure the treee remains balanced */
        *node = (BSTNode) { .height = 1, .key = key, .value = value,
                            .left = NULL, .right = NULL };
        return node;
    }

    if (key > root->key) {
        root->right = insert_node(key, value, root->right);
    } else if (key < root->key) {
        root->left = insert_node(key, value, root->left);
    } else {
        // update value in the existing node
        root->value = value;
    }

    // Update the height
    root->height = 1 + MAX(height(root->left), height(root->right));

    /* Rebalance the subtree. A negative balance indicates that the left
        subtree is higher */
    int balance = height(root->right) - height(root->left);

    // Left-left
    if (balance < -1 && key < root->left->key) {
        return rotateRight(root);
    }

    // Right-right
    if (balance > 1 && key > root->right->key) {
        return rotateLeft(root);
    }

    // Left-right
    if (balance < -1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right-left
    if (balance > 1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

/** Documented in avl.h */
void *delete_avl(int key, AVLTree *tree) {
    return NULL; //TODO
}

/** Documented in avl.h */
void *lookup_avl(int key, AVLTree *tree) {
    if (tree == NULL) {
        return NULL;
    }
    return lookup(key, tree->root);
}

/**
 * Internal function for looking up a value in the tree.
 *
 * @param key the key to search for
 * @param tree pointer to the root node of the subtree to search
 *
 * @return the value located at the given key or NULL if the key is not
 * found
 */
static void *lookup(int key, BSTNode *tree) {
    if (tree == NULL) {
        return NULL;
    }

    if (tree->key == key) {
        return tree->value;
    } else if (key < tree->key) {
        return lookup(key, tree->left);
    } else {
        return lookup(key, tree->right);
    }
}

/**
 * Performs a right rotation around node *node.
 *
 * Calling rotateRight on Node D in this tree:
 *                   D
 *                 /   \
 *               B       E
 *             /   \
 *            A     C
 *
 * Transforms the tree into:
 *                  B
 *                /   \
 *              A       D
 *                    /   \
 *                   C      E
 *
 * @param *node
 *      the node to rotate the tree around
 *
 * @return the new root of the subtree
 */
static BSTNode *rotateRight(BSTNode *node) {
    BSTNode *root = node->left;
    node->left = root->right;
    root->right = node;

    //update height fields
    node->height = 1 + MAX(height(node->left), height(node->right));
    root->height = 1 + MAX(height(root->left), height(root->right));

    return root;
}

/**
 * Performs a left rotation around node *node.
 *
 * Calling rotateLeft on Node B in this tree:
 *
 *                   B
 *                 /   \
 *               A       D
 *                     /   \
 *                    C      E
 *
 * Transforms the tree into:
 *                   D
 *                 /   \
 *               B       E
 *             /   \
 *            A     C
 *
 * @param *node
 *      the node to rotate the tree around
 *
 * @return the new root of the subtree
 */
static BSTNode *rotateLeft(BSTNode *node) {
    BSTNode *root = node->right;
    node->right = root->left;
    root->left = node;

    //update height fields
    node->height = 1 + MAX(height(node->left), height(node->right));
    root->height = 1 + MAX(height(root->left), height(root->right));

    return root;
}

/** Documented in avl.h */
void print_tree(AVLTree *tree) {
    print_nodes(tree->root, 0);
}

/**
 * Internal function for printing trees. Prints a preorder traversal of
 * the subtree rooted at the given node. Each level is indented INDENT
 * spaces under its parent.
 *
 * @param root the root of the subtree to print
 * @param indent number of spaces to indent this node.
 */
static void print_nodes(BSTNode *root, int indent) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < indent; i++) {
        putchar(' ');
    }
    printf("%4d\n", root->key);
    print_nodes(root->left, indent + INDENT);
    print_nodes(root->right, indent + INDENT);
}
