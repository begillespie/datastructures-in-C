/**
 * @file driver.c
 * @author Brian Gillespie
 *
 * Sample driver program for the AVL Tree module. Demonstrates the
 * functionality and use of the structure.
 */

#include "avl.h"
#include <stdio.h>

int main() {
    printf("AVL Driver\n");

    AVLTree *avl = createAVLTree();
    // Add 15 nodes in key order, printing the tree after each insertion.
    for(int i = 0; i < 15; i++) {
        insert_avl(i, NULL, avl);
        print_tree(avl);
        printf("======================================\n");
    }
    return 0;
}
