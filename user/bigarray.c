#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

#define SIZE (1 << 16)

int arr[SIZE];
int pids[NPROC];

int main()
{
  int PARTS = 4;

  // Initialize array
  for (int i = 0; i < SIZE; i++)
    arr[i] = i;

  //edge case 0 forking
  if (PARTS == 0)
  {
    printf("0 forks, exiting cleanly.\n");
    printf("Final total = 0\n");
    exit(0, "");
  }

  int who_am_i = forkn(PARTS, pids);
  // unsuccessful fork
  if (who_am_i < 0)
  {
    fprintf(2, "forkn failed\n");
    exit(1, "");
  }

  int workpart = SIZE / PARTS; // depends on how many children were created 

  //child process
  if (who_am_i > 0)
  {
    int start = (who_am_i - 1) * workpart;
    int end = who_am_i * workpart;
    int sum = 0;

    for (int i = start; i < end; i++)
      sum += arr[i];

    printf("Child num %d : pid %d , sum = %d\n", who_am_i, getpid(), sum);
    exit(sum, "");
  }

  // Parent process
  int count;
  int statuses[NPROC];

  if (waitall(&count, statuses) < 0)
  {
    fprintf(2, "waitall failed\n"); // error msg
    exit(1, "");
  }
  // children done so the parent shows final sum 
  int total = 0;
  for (int i = 0; i < count; i++)
    total += statuses[i];
  printf("All children done\n");
  printf("Final total = %d\n", total);
  exit(0, "");
}
