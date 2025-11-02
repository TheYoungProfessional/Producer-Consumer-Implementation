// producer_consumer.h
#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H

#include <semaphore.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define errExit(msg)    \
  do {                  \
    perror(msg);        \
    exit(EXIT_FAILURE); \
  } while (0)
#define BUF_SIZE 2 /* Maximum size for exchanged string */

/* Define a structure that will be imposed on the shared
   memory object */

struct shmbuf {
  sem_t empty; /* POSIX unnamed semaphore */
  sem_t full;  /* POSIX unnamed semaphore */
  sem_t mutex;
  int in;            // index where producer puts next item
  int out;           // index where consumer gets next item
  int tab[BUF_SIZE]; /* (Table) Data being transferred */
};

#endif  // include guard