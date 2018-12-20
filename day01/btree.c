#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include"btree.h"

struct Node* createNode(int value){
    struct Node *n = (struct Node*) malloc(sizeof(struct Node));
    n->value = value;
    n->left = NULL;
    n->right = NULL;

    return n;
}

/*
 * Traverses the binary tree starting from the given root node, searching
 * for the given value. If the value is found, returns true. Otherwise
 * inserts a new node with the value and returns false.
 */
bool find_or_insert(struct Node *root, int value){
    struct Node *n = root;
    
    while(n->value != value) {
        if (n->value < value){
            if (n->right){ 
                n = n->right;
            } else {
                struct Node *newnode = createNode(value); 
                n->right = newnode;
                return false;
            }
        } else {
            if (n->left) {
                n = n->left;
            } else {
                struct Node *newnode = createNode(value); 
                n->left = newnode;
                return false;
            }
        }
    }

    return true;
}
