#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include"event.h"

/*
 * Compares the timestamps of two events. Returns -1 if e1 happens before e2,
 * 0 if the timestamps are equal and 1 if s1 happens after s1.
 */
int compare_events(struct event *e1, struct event *e2){
    if (e1->year < e2->year) {
        return -1;
    } else if (e2->year < e1->year) {
        return 1;
    } else if (e1->month < e2->month) {
        return -1;
    } else if (e2->month < e1->month) {
        return 1;
    } else if (e1->day < e2->day) {
        return -1;
    } else if (e2->day < e1->day) {
        return 1;
    } else if (e1->hour < e2->hour) {
        return -1;
    } else if (e2->hour < e1->hour) {
        return 1;
    } else if (e1->minute < e2->minute) {
        return -1;
    } else if (e2->minute < e1->minute) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * Sorts the given list of n pointers to events.
 */
void sort_events(struct event **events, int n){
    quicksort(events, 0, n-1);
}

/*
 * Quicksort with Lomuto partition scheme.
 */
void quicksort(struct event **events, int low, int high){
    if (low < high){
        int p = partition(events, low, high);
        quicksort(events, low, p-1);
        quicksort(events, p+1, high);
    }
}

/*
 * Partitioning function for quicksort
 */
int partition(struct event **events, int low, int high){
    struct event *pivot = events[high];
    int i = low;
    for (int j=low; j <= high-1; j++){
        if (compare_events(events[j], pivot) < 0) {
            if (i != j) {
                swap(events, i, j);
            }
            i++;
        }
    }
    swap(events, i, high);
    return i;
}

/*
 * Swaps event pointers in indices s1 and s2 with each other.
 */
void swap(struct event **events, int s1, int s2){
    struct event *tmp = events[s1];
    events[s1] = events[s2];
    events[s2] = tmp;
}

/*
 * Writes the string representation of the event to the given string
 */
void eventstr(struct event *e, char *str) {
    sprintf(str, "%d-%d-%d %d:%d %s", e->year, e->month, e->day, e->hour, e->minute, e->eventtext);
}

