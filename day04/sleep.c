#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"event.h"
#include"binaryguard.h"

int main(int argc, char **argv){
    FILE *fp;
    if (argc >= 2){
        fp = fopen(argv[1], "r");
    } else {
        fprintf(stderr, "You must give an input file as a command line argument.\n");
        exit(1);
    }

    // count events
    int eventcount = 0;
    int tmp;
    while(fscanf(fp, "[%d-%*d-%*d %*d:%*d] %*[^\n]\n", &tmp) > 0){
        eventcount++;
    }

    // read all events
    rewind(fp);
    struct event **events = malloc(eventcount * (sizeof(struct event*)));
    int year, month, day, hour, minute;
    char *str = (char *) malloc(25*sizeof(char));
    int i=0;
    while(fscanf(fp, "[%d-%d-%d %d:%d] %[^\n]\n", &year, &month, &day, &hour, &minute, str) > 0){
        struct event *e = (struct event*) malloc(sizeof(struct event));
        e->year = year;
        e->month = month;
        e->day = day;
        e->hour = hour;
        e->minute = minute;
        e->eventtext = strcpy((char*) malloc(25*sizeof(char)), str);

        events[i++] = e;
    }

    sort_events(events, eventcount);
    
    // read the first guard to act as a root for the binary tree
    struct guard *root;
    int id;
    sscanf(events[0]->eventtext, "Guard #%d begins shift", &id);
    root = create_guard(id);
    
    // add sleeped minutes to each guard
    struct guard *g = root;
    int sleep_start, sleep_end;
    for(int i=1; i<eventcount; i++){
        struct event *e = events[i];
        if (e->eventtext[0] == 'G'){
            sscanf(events[i]->eventtext, "Guard #%d begins shift", &id);
            g = find_or_insert(root, id);
        } else if (e->eventtext[0] == 'f'){
            sleep_start = e->minute;
        } else if (e->eventtext[0] == 'w'){
            sleep_end = e->minute;
            for(int j=sleep_start; j<sleep_end; j++) {
                g->minutes[j] += 1;
            }
        }
    }

    struct guard *sleepiest = find_sleepiest(root);
    int bestminute = 0;
    int sleeps = 0;
    for(int i=0; i<60; i++){
        if (sleepiest->minutes[i] > sleeps) {
            bestminute = i;
            sleeps = sleepiest->minutes[i];
        }
    }
    printf("Part 1: (Sleepiest guard ID) * (their most sleeped minute) = %d\n", sleepiest->id * bestminute);

    sleepiest = find_sleepiest_minute(root);
    sleeps = 0;
    bestminute = 0;
    for(int i=0; i<60; i++){
        if (sleepiest->minutes[i] > sleeps) {
            sleeps = sleepiest->minutes[i];
            bestminute = i;
        }
    }
    
    printf("Part 2: (Sleepiest guard ID) * (their most sleeped minute) = %d\n", sleepiest->id * bestminute);

    exit(0);
}
