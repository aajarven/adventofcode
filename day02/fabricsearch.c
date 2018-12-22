#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

#define IDLENGTH 26

int main(int argc, char **argv){

    FILE *fp;
    if (argc >= 2){
        fp = fopen(argv[1], "r");
    } else {
        fprintf(stderr, "You must give an input file as a command line argument.\n");
        exit(EXIT_FAILURE);
    }

    // count the IDs
    char id[IDLENGTH + 1];
    int idcount = 0;
    while (fscanf(fp, "%s", id) == 1){
        idcount++;
    }
    
    // read the IDs
    char ids[idcount][IDLENGTH];
    rewind(fp);
    int i = 0;
    while(fscanf(fp, "%s", id) == 1){
        strcpy(ids[i], id);
    }

    exit(0);
}
