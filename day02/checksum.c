#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

#define IDLENGTH 26

int main(int argc, char **argv){
    int alphabet_length = 'z' - 'a';

    FILE *fp;
    if (argc >= 2){
        fp = fopen(argv[1], "r");
    } else {
        fprintf(stderr, "You must give an input file as a command line argument.\n");
        exit(EXIT_FAILURE);
    }

    int charcount[alphabet_length+1];
    char id[IDLENGTH + 1];
    int doubles = 0;
    int triples = 0;
    while (fscanf(fp, "%s", id) == 1){
        // zero all characters out
        for (int i=0; i <= alphabet_length; i++){
            charcount[i] = 0;
        }

        // count characters
        char *c = id;
        while(*c != '\0') {
            if (*c <= 'z' && *c >= 'a'){
                charcount[*c-'a']++;
            }
            c++;
        }

        // check doubles and triples
        bool double_found = false;
        bool triple_found = false;
        for (int i = 0; i <= alphabet_length; i++){
            if (!double_found && charcount[i] == 2){
                doubles++;
                double_found = true;
            } else if (!triple_found && charcount[i] == 3){
                triples++;
                triple_found = true;
            }
        }
    }

    printf("Checksum: %d\n", doubles*triples);

    exit(0);
}
