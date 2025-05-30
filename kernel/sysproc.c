#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  char msg[32];

  argint(0, &n);

  // Try to get second argument (exit message)
  argstr(1, msg, sizeof(msg));

  exit(n, msg);  // Call updated exit() with message
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_forkn(void)
{
  int n;
  uint64 pids_addr;

  argint(0, &n);
  argaddr(1, &pids_addr);

  return forkn(n, pids_addr);
}


uint64
sys_wait(void)
{
  uint64 p;         // status pointer (int*)
  uint64 msgaddr;   // message pointer (char*)

  argaddr(0, &p);

  // Try to get second argument (message buffer)
  argaddr(1, &msgaddr);

  return wait(p, msgaddr);  // Call updated wait()
}

uint64
sys_waitall(void)
{
  uint64 n_addr;
  uint64 statuses_addr;

  argaddr(0, &n_addr);
  argaddr(1, &statuses_addr);

  return waitall(n_addr, statuses_addr);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid; //the arg pid

  argint(0, &pid); //get arg value
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_memsize(void) 
{
  return myproc()->sz;
}
