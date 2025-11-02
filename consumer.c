// consumer.c
#include "producer_consumer.h"
#include <ctype.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
  // open shared memory
  int fd = shm_open("/my_shared_mem", O_RDWR, 0);
  if (fd == -1) errExit("shm_open");
  // Map the shared memory
  struct shmbuf *shmbuf_ptr = mmap(NULL, sizeof(struct shmbuf),
                                   PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (shmbuf_ptr == MAP_FAILED) errExit("mmap");
  // Give producer time to initialize semaphores
  sleep(1);
  // consumer loop
  while (1) {
    sem_wait(&shmbuf_ptr->full);   // wait for filled slot
    sem_wait(&shmbuf_ptr->mutex);  // lock the table
    // get item from table
    int item = shmbuf_ptr->tab[shmbuf_ptr->out];
    printf("Consumer: got item %d from index %d\n", item, shmbuf_ptr->out);
    shmbuf_ptr->out = (shmbuf_ptr->out + 1) % BUF_SIZE;  // circular buffer
    sem_post(&shmbuf_ptr->mutex);                        // unlock the table
    sem_post(&shmbuf_ptr->empty);  // signal that table has empty slot
    // consume the item
    printf("Consumer: consumed item %d\n", item);
    sleep(2);  // consume slower than production to see blocking
  }
}