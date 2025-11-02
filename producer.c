// producer.c
#include "producer_consumer.h"
#include <ctype.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
  // open shared memory
  int fd = shm_open("/my_shared_mem", O_CREAT | O_RDWR, S_IRWXU);
  if (fd == -1) errExit("shm_open");
  // Set the size of shared memory
  if (ftruncate(fd, sizeof(struct shmbuf)) == -1) errExit("ftruncate");
  // Map the shared memory
  struct shmbuf *shmbuf_ptr = mmap(NULL, sizeof(struct shmbuf),
                                   PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (shmbuf_ptr == MAP_FAILED) errExit("mmap");
  // initialize sempahores
  sem_init(&shmbuf_ptr->empty, 1,
           2);  // 1 = shared between processes, 2 = initial value
  sem_init(&shmbuf_ptr->full, 1, 0);
  sem_init(&shmbuf_ptr->mutex, 1, 1);
  // initialize semaphore indices
  shmbuf_ptr->in = 0;
  shmbuf_ptr->out = 0;
  // initialize item
  int item = 0;
  // producer loop
  while (1) {
    // produce an item
    item++;
    printf("Producer: ready to produce item %d\n", item);
    sem_wait(&shmbuf_ptr->empty);  // wait for empty slot
    sem_wait(&shmbuf_ptr->mutex);  // lock the table
    // put item on table
    shmbuf_ptr->tab[shmbuf_ptr->in] = item;
    printf("Producer: produced item %d at index %d\n", item, shmbuf_ptr->in);
    shmbuf_ptr->in = (shmbuf_ptr->in + 1) % BUF_SIZE;  // circular buffer
    sem_post(&shmbuf_ptr->mutex);                      // unlock the table
    sem_post(&shmbuf_ptr->full);  // signal that table has item
    sleep(1);                     // slow down production
  }
}