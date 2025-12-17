#include "types.h"
#include "stat.h"
#include "user.h"

struct uproc {
  int pid;
  int state;
  int sz;
  char name[16];
};

char *states[] = {
 [0] "UNUSED",
 [1] "EMBRYO",
 [2] "SLEEPING",
 [3] "RUNNABLE",
 [4] "RUNNING",
 [5] "ZOMBIE"
};

int
main(void)
{
  struct uproc ps[64];
  int n = getps(ps, 64);

  printf(1, "PID   Estado      Mem(Bytes)   Nombre\n");

  for(int i=0; i<n; i++){
    printf(1, "%d    %s     %d       %s\n",
      ps[i].pid,
      states[ps[i].state],
      ps[i].sz,
      ps[i].name
    );
  }

  exit();
}
