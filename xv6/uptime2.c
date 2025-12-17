#include "types.h"
#include "user.h"
#include "stat.h"

int main(){
  int info[5];

  if(getuptimeinfo(info) < 0){
    printf(1, "Error: getuptimeinfo\n");
    exit();
  }

  int ticks = info[0];
  int running = info[1];
  int runnable = info[2];
  int sleeping = info[3];
  int ctx = info[4];

  printf(1, "Tiempo desde arranque: %d ticks (%d segundos)\n",
        ticks, ticks / 100);
  printf(1, "Procesos RUNNING : %d\n", running);
  printf(1, "Procesos RUNNABLE: %d\n", runnable);
  printf(1, "Procesos SLEEPING: %d\n", sleeping);
  printf(1, "Cambios de contexto: %d\n", ctx);

  exit();
}
