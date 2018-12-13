#include<stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    
    FILE *fp;
    if (argc >= 2){
        fp = fopen(argv[1], "r");
    } else {
        fprintf(stderr, "No input file. Give the file as a command line argument");
        exit(EXIT_FAILURE);
    }

    int freq_change = 0;
    int frequency = 0;
    fscanf(fp, "%d", &freq_change);
    while(!feof(fp)){
        frequency += freq_change;
        fscanf(fp, "%d", &freq_change);
    }
    printf("Total frequency drift: %d\n", frequency);
}
