#include<stdbool.h>
#include<stdio.h>
#include <stdlib.h>
#include"btree.h"

#define MAXINPUT 1000


int main(int argc, char **argv){
    
    FILE *fp;
    if (argc >= 2){
        fp = fopen(argv[1], "r");
    } else {
        fprintf(stderr, "No input file. Give the file as a command line argument.\n");
        exit(EXIT_FAILURE);
    }

    int changes[MAXINPUT];
    int last_change;
    int i = 0;
    do {
        fscanf(fp, "%d", &changes[i++]);
        if (i >= MAXINPUT) {
            fprintf(stderr, "Too long input array.\n");
            exit(EXIT_FAILURE);
        }
    } while(!feof(fp));
    last_change = i - 1;


    int frequency = 0;
    struct Node btree;
    btree.value =frequency;
    while (true) {
        i = 0;
        while (i < last_change){
            frequency += changes[i];
            i++;
            if (find_or_insert(&btree, frequency)) {
                printf("First repeated: %d\n", frequency);
                exit(0);
            }
        }
    }

    return false;
}
