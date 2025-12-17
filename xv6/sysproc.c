#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

//
extern int trace_syscalls;

extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

extern int ncontext;

extern int syscall_count[];

//

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


//Entregable 1
int
sys_trace(void)
{
  int enable;

  if(argint(0, &enable) < 0)
    return -1;

  trace_syscalls = enable;

  return 0;
}
//
//Entregable 2
int
sys_getuptimeinfo(void)
{
  int *addr;

  if(argptr(0, (char**)&addr, sizeof(int) * 5) < 0)
    return -1;

  addr[0] = ticks;

  int running = 0;
  int runnable = 0;
  int sleeping = 0;

  struct proc *p;

  acquire(&ptable.lock);  // ← IMPORTANTE para sincronización

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    switch(p->state){

      case RUNNING:
        running++;
        break;

      case RUNNABLE:
        runnable++;
        break;

      case SLEEPING:
        sleeping++;
        break;

      default:
        // UNUSED, EMBRYO, ZOMBIE → ignorados
        break;
    }
  }

  release(&ptable.lock);

  addr[1] = running;
  addr[2] = runnable;
  addr[3] = sleeping;
  addr[4] = ncontext;

  return 0;
}

int sys_getps(void)
{
  struct uproc *up;
  int max;

  if(argptr(0, (char**)&up, sizeof(struct uproc)*64) < 0)
    return -1;
  if(argint(1, &max) < 0)
    return -1;

  int count = 0;
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC] && count < max; p++){
    if(p->state == UNUSED) continue;

    up[count].pid = p->pid;
    up[count].state = p->state;
    up[count].sz = p->sz;
    safestrcpy(up[count].name, p->name, 16);

    count++;
  }

  return count;
}

int
sys_getsyscount(void)
{
    int *buf;
    int size;

    if(argptr(0, (char**)&buf, sizeof(int) * 64) < 0)
        return -1;

    if(argint(1, &size) < 0)
        return -1;

    for(int i = 0; i < size; i++)
        buf[i] = syscall_count[i];

    return 0;
}
