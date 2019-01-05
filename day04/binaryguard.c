#include<stdbool.h>
#include<stdlib.h>

#include"binaryguard.h"


/*
 * Finds a guard with given id from the binary tree and returns it or inserts a
 * new one if one cannot be found.
 */
struct guard* find_or_insert(struct guard *bt, int id){
    while(true) {
        if (bt->id == id) {
            return bt;
        } else if (bt->id > id) {
            if (bt->left) {
                bt = bt->left;
            } else {
                struct guard *newguard = create_guard(id);
                bt->left = newguard;
                return newguard;
            }
        } else {
            if (bt->right) {
                bt = bt->right;
            } else {
                struct guard *newguard = create_guard(id);
                bt->right = newguard;
                return newguard;
            }
        }
    }
}

struct guard* create_guard(int id){
    struct guard *newguard = (struct guard*) malloc(sizeof(struct guard));
    newguard->id = id;
    for (int i=0; i<60; i++){
        newguard->minutes[i] = 0;
    }
    newguard->left = NULL;
    newguard->right = NULL;
    return newguard;
}

/*
 * Returns the total number of minutes the guard has been sleeping. If a null
 * pointer is given, returns -1.
 */
int totalminutes(struct guard *g) {
    if (!g) {
        return -1;
    } else {
        int minutes = 0;
        for (int i=0; i<60; i++){
            minutes += g->minutes[i];
        }
        return minutes;
    }
}

struct guard* find_sleepiest(struct guard* root){
    if ((!root->left) && (!root->right)) {
        return root;
    } else if (!root->left) {
        struct guard *sleepyright = find_sleepiest(root->right);
       if (totalminutes(sleepyright) > totalminutes(root)) {
            return sleepyright;
        } else {
            return root;
        }
    } else if (!root->right) {
        struct guard *sleepyleft = find_sleepiest(root->left);
        if (totalminutes(sleepyleft) > totalminutes(root)) {
            return sleepyleft;
        } else {
            return root;
        }
    } else {
        struct guard *sleepyright = find_sleepiest(root->right);
        int rightminutes = totalminutes(sleepyright);
        struct guard *sleepyleft = find_sleepiest(root->left);
        int leftminutes = totalminutes(sleepyleft);
        int rootminutes = totalminutes(root);

        if (rootminutes > leftminutes && rootminutes > rightminutes) {
            return root;
        } else if (leftminutes > rootminutes && leftminutes > rightminutes) {
            return sleepyleft;
        } else {
            return sleepyright;
        }
    }
}
