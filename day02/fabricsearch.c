#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"fabricsearch.h"

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
    char *ids[idcount];
    rewind(fp);
    int i = 0;
    while(fscanf(fp, "%s", id) == 1){
        ids[i] = malloc( (IDLENGTH+1) * sizeof(char) );
        strcpy(ids[i], id);
        i++;
    }

    // test all possible characters to differ
    for(i=0; i<IDLENGTH; i++){
        char *match = merge_search(ids, idcount, i);
        if (match) {
            printf("found match: ");
            int j=0;
            while(*match != '\0'){
                if (j != i) { 
                    printf("%c", *match);
                }
                j++;
                match++;
            }
            printf("\n");
            exit(0);
        }
    }

    exit(1);
}

/*
 * Merge sorts the given IDs, ignoring the char in the i_ignore index of each ID.
 * If two identical strings (apart from the ignored character) are encountered,
 * returns one of those. Otherwise returns a null pointer when the array has
 * been sorted.
 */
char* merge_search(char **ids, int n, int i_ignore){
    char *wrk[n];
    for (int width = 1; width < n; width *= 2){
        for (int i=0; i<n; i += 2*width){
            char *match = merge(ids, wrk, i, min(i+width, n), min(i+2*width, n),
                    i_ignore);
            if (match) {
                return match;
            }
        }
        arraycopy(ids, wrk, n);
    }
    
    return NULL;
}

/*
 * Merges slices [left, mid-1] and [mid, right-1], ignoring the char at index
 * i_ignore when comparing two strings.
 */
char* merge(char **data, char **wrk, int left, int mid, int right, int i_ignore){
    int i_left = left;
    int i_right = mid;
    int k = i_left;
    while (k < right) {
        if (i_left >= mid) { // easy cases with no real choice first
            wrk[k++] = data[i_right++];
        } else if (i_right >= right) {
            wrk[k++] = data[i_left++];
        } else { //  then commparisons if needed
            int c = ignore_compare(data[i_left], data[i_right], i_ignore);
            if (c < 0) {
                wrk[k++] = data[i_left++];
            } else if (c > 0){
                wrk[k++] = data[i_right++];
            } else {
                return data[i_left];
            }
        }
    }
    return NULL;
}

/*
 * Compares strings s1 and s2 lexicographically ignoring the character in index i_ignore. Returns -1 if s1<s2, 0 if they are equal and 1 if s2>s1.
 */
int ignore_compare(char *s1, char*s2, int i_ignore){
    int i=0;
    while(s1[i] != '\0' && s2[i] != '\0'){
        if (i != i_ignore){
            if (s1[i] < s2[i]){
                return -1;
            } else if (s1[i] > s2[i]){
                return 1;
            }
        } else {
        }
        i++;
    }
    return 0;
}

/*
 * Returns the minimum of two integers.
 */
int min(int i1, int i2){
    return i1 < i2 ? i1 : i2;
}

/*
 * Copies contents of first n indices of a2 to a1. Both have to be long enough.
 */
void arraycopy(char **a1, char** a2, int n){
    for(int i=0; i<n; i++){
        a1[i] = a2[i];
    }
}
