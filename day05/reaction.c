#include<stdio.h>
#include<stdlib.h>

#include"stack.h"


int main(int argc, char **argv){
    FILE *fp;
    if (argc >= 2) {
        fp = fopen(argv[1], "r");
    } else {
        fprintf(stderr, "You must give an input file as a command line argument.\n");
        exit(1);
    }

    char c;
    struct stacknode *top = malloc(sizeof(struct stacknode));
    top->unit = '\0'; // botton node that cannot be removed even if the real stack is empty
    top->length = 0;
    top->previous = NULL;

    while((c = fgetc(fp)) != '\n') {
        if (abs(top->unit - c) == AADIFF) {
            struct stacknode *oldtop = top;
            top = oldtop->previous;
            free(oldtop);
        } else { 
            struct stacknode *new = malloc(sizeof(struct stacknode));
            new->unit = c;
            new->length = top->length + 1;
            new->previous = top;
            top = new;
        }
    }

    printf("Resulting length: %d\n", top->length);
    exit(0);
}
