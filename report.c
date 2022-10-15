#define REPORT_SIZE 1000000

#include <stdlib.h>
#include <stdio.h>
#include "pthread.h"

typedef struct report_s {
    long int time;
    int philo;
    char * status;
} report_t;

int top;
pthread_mutex_t  report_m;
report_t *reports;

void report_init() {
    pthread_mutex_init(&report_m, NULL);
    top = 0;
    reports = (report_t *) malloc(sizeof(report_t) * REPORT_SIZE);
}


void report(long int time, int philo, char *status) {
    int current;
    pthread_mutex_lock(&report_m);
    current = top++;
    pthread_mutex_unlock(&report_m);
    reports[current].status = status;
    reports[current].time = time;
    reports[current].philo = philo;
}


void report_final() {
    int i;
    pthread_mutex_lock(&report_m);
    for (i = 0; i < top; i++)
        printf("%ld %d %s\n", (reports + i)->time, (reports + i)->philo, (reports + i)->status);
    free(reports);
    pthread_mutex_unlock(&report_m);
}