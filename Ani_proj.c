#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include<sys/types.h>
#include<unistd.h>
#define MIN_PID 100
#define MAX_PID 1000
//Execute the prrogram ussisng gcc -pthread PROGRAM_NAME
// Declare our Bitmap
int bit_map[MAX_PID-MIN_PID];
int allocate_map() {
	for(int i = 0; i < MAX_PID-MIN_PID; i++)
{
		bit_map[i] = 0; // Making every pid available by allocating 0 to all bitmaps
}
printf("Process Bitmap initialized... \n");
return 1;
}
int allocate_pid() {
	for(int i = 0; i < MAX_PID-MIN_PID; i++) {
		if(bit_map[i] == 0) //Making Sure if a pid is available - A pid is available only if its bitmap is 0
              {

			bit_map[i] = 1; // Assigning bitmap to 1 as pid is no longer available
printf("\033[1;33m");
      printf("New Process Allocated with PID : %d \n",(i+MIN_PID));
printf("\033[0m");
int r = 1+rand()%30;
printf("The thread will take atleast %d seconds to expire\n",r);
sleep(r);
			return i + MIN_PID;
		}
	}
	return 1;
}
void release_pid(int pid) {
    if(MIN_PID<=pid && pid<MAX_PID) {
      bit_map[pid-MIN_PID] = 0;
printf("\033[1;31m");
      printf("Process Released with PID : %d \n",pid);
printf("\033[0m");
}
}

void *myThreadFun(void *vargp) {
    int pid = allocate_pid(); // Allocate a PID to each thread
    release_pid(pid); // Finally Release PID to simulate releasing
    return NULL;
}

int main() {
    allocate_map();
    int no;
    printf("Enter no of Threads\n");
    scanf("%d",&no);
    pthread_t tid;
    printf("Let's start creating Thread...\n");
    for (int i = 0; i < no; i++)  // Creating 100 Threads for testing
    {
    pthread_create(&tid, NULL, myThreadFun, NULL);
sleep(1);
    }
printf("Successfully Allocated Processes");
    return 0;
}

