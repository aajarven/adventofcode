#define BEGIN 1
#define SLEEP 2
#define WAKEUP 3

struct event {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    char *eventtext;
};

int compare_events(struct event*, struct event*);
void sort_events(struct event**, int);
void quicksort(struct event**, int, int);
int partition(struct event**, int, int);
void swap(struct event**, int, int);
void eventstr(struct event*, char*);
