# Producer-Consumer-Implementation
INCLUDED FILES

producer_consumer.h : Header file for the two processes, defines the table in shared memory, as well as the
semaphores that are used to ensure mutual exclusion.

producer.c : Source code for the Producer, generates items and puts them on the table in shared memory,
assuming there are fewer than 2 items on the table. If the table is full, this process waits until
the consumer has removed an item from the table, at which point production resumes.

consumer.c : Source code for the Consumer, takes in items from the table in shared memory, assuming
the table is not empty. If the table is empty, this process waits until there is something on the table,
at which point consumption is resumed.

mem_clean.sh : A bash script that cleans the shared memory after the processes have been terminated.

example1.png & example2.png : These are screenshots of the processes executing successfully on my machine.
The output in your environment should be similar.

README.md: This file, serves to describe each of the files in the repo and provide detailed instructions
for installing and using this project.

LICENSE: The GNU Public License, allows anyone who downloads this repo to modify and distribute the repo's
contents as they please.

Documentation.txt: Explains what the program does and what execution results to expect. Explains the project's
usage of semaphores, mutual exclusion, and shared memory.

Installation instruction for Linux/Unix users
1. Download "producer_consumer.h", "producer.c", "consumer.c", and "mem_clean.sh" to an empty directory on your machine
2. Open your terminal and navigate to the directory you saved the files to
3. To compile the project, input the following two commands:

      gcc producer.c -pthread -lrt -o producer
  
      gcc consumer.c -pthread -lrt -o consumer
   
5. To run the project input this command:
  ./producer & ./consumer &
   
The processes should now execute and behave as expected.

NOTE: The only easy way to end these processes is to close the terminal they're running in.

NOTE: After the project has been run for the first time, the shared memory needs to be removed
  every time before running it again. The bash script "mem_clean.sh" has been included for this purpose.
