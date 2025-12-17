#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc < 2){
    printf(1, "Uso: trace <0|1>\n");
    exit();
  }

  int enable = atoi(argv[1]);
  trace(enable);

  exit();
}
