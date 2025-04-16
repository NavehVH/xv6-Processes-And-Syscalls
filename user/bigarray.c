#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

#define SIZE (1 << 16)
#define PARTS 4

int arr[SIZE];
int pids[PARTS];

int main() {
  // Initialize array
  for (int i = 0; i < SIZE; i++)
    arr[i] = i;

  int which = forkn(PARTS, pids);
  if (which < 0) {
    fprintf(2, "forkn failed\n");
    exit(1, "");
  }

  if (which > 0) {
    // Child process
    int start = (which - 1) * (SIZE / PARTS);
    int end = which * (SIZE / PARTS);
    int sum = 0;
    for (int i = start; i < end; i++)
      sum += arr[i];

    printf("Child %d (pid=%d) computed sum = %d\n", which, getpid(), sum);
    exit(sum, "");
  }

  // Parent process
  printf("Created children with PIDs: ");
  for (int i = 0; i < PARTS; i++) {
    printf("%d ", pids[i]);
  }
  printf("\n");

  int count;
  int statuses[NPROC];

  if (waitall(&count, statuses) < 0) {
    fprintf(2, "waitall failed\n");
    exit(1, "");
  }

  int total = 0;
  for (int i = 0; i < count; i++)
    total += statuses[i];

  printf("Final total = %d\n", total);
  exit(0, "");
}
