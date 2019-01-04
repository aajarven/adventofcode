#include<stdbool.h>
#include<stdio.h>
#include <stdlib.h>

#define SHEETSIZE 1000
#define MAX_CLAIMS 2000
#define EMPTY 0
#define OVERLAP -1

int main(int argc, char **argv){
    FILE *fp;
    if (argc >= 2){
        fp = fopen(argv[1], "r");
    } else {
        fprintf(stderr, "You must give an input file as a command line argument.\n");
        exit(1);
    }

    // initialize the array used to store overlapping status of claims
    bool overlaps[MAX_CLAIMS];
    overlaps[0] = true; // index 0 not used
    for (int i=1; i<MAX_CLAIMS; i++){
        overlaps[i] = false;
    }

    // initialize the sheet array
    int sheet[SHEETSIZE][SHEETSIZE];
    for (int i=0; i<SHEETSIZE; i++){
        for (int j=0; j<SHEETSIZE; j++){
            sheet[i][j] = EMPTY;
        }
    }

    int overlap_count = 0;

    // read claims and count overlaps
    int id = 0;
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    while(fscanf(fp, "#%d @ %d %*c %d: %dx%d\n", &id, &x, &y, &width, &height) > 0){
        for (int dy = 0; dy < height; dy++) {
            for (int dx=0; dx < width; dx++) {
                int value = sheet[x + dx][y + dy];
                if (value == EMPTY){
                    sheet[x + dx][y + dy] = id;
                } else if (value != OVERLAP){
                    overlap_count++;
                    overlaps[id] = true;
                    overlaps[sheet[x + dx][y + dy]] = true;
                    sheet[x + dx][y + dy] = OVERLAP;
                }
            }
        }
    }
    printf("Overlaps: %d\n", overlap_count);

    // find the first non-overlapping claims within the range really used by IDs
    for (int i=0; i<=id; i++) {
        if (!overlaps[i]){
            printf("Non-overlapping id: %d\n", i);
            exit(0);
        }
    }

    exit(1);
}

