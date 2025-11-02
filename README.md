# Producer-Consumer-Implementation
Installation instruction for Linux/Unix users
1. Download "producer_consumer.h", "producer.c", "consumer.c", and "mem_clean.sh" to an empty directory on your machine
2. Open your terminal and navigate to the directory you saved the files to
3. To compile the project, input the following two commands:
  gcc producer.c -pthread -lrt -o producer
  gcc consumer.c -pthread -lrt -o consumer
4. To run the project input this command:
  ./producer & ./consumer &
The processes should now execute and behave as expected.
NOTE: The only easy way to end these processes is to close the terminal they're running in.
NOTE: After the project has been run for the first time, the shared memory needs to be removed
  every time before running it again. The bash script "mem_clean.sh" has been included for this purpose.
