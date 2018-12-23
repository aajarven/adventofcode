#include <stdio.h>
#include <stdlib.h>

#define SHEETSIZE 1000
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

    // initialize the sheet array
    int sheet[SHEETSIZE][SHEETSIZE];
    for (int i=0; i<SHEETSIZE; i++){
        for (int j=0; j<SHEETSIZE; j++){
            sheet[i][j] = EMPTY;
        }
    }

    int overlaps = 0;

    // read claims and count overlaps
    int id = 0;
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    while(fscanf(fp, "#%d @ %d %*c %d: %dx%d\n", &id, &x, &y, &width, &height) > 0){
        printf("#%d @ %d,%d: %dx%d\n", id, x, y, width, height);

        for (int dy = 0; dy < height; dy++) {
            for (int dx=0; dx < width; dx++) {
                int value = sheet[x + dx][y + dy];
                if (value == EMPTY){
                    sheet[x + dx][y + dy] = id;
                } else if (value != OVERLAP){
                    overlaps++;
                    sheet[x + dx][y + dy] = OVERLAP;
                }
            }
        }
    }

    printf("Overlaps: %d\n", overlaps);
    exit(0);
}

