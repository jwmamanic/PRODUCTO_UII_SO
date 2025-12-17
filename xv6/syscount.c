#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    int buf[64];

    getsyscount(buf, 64);

    if(argc == 2) {
        int id = atoi(argv[1]);
        printf(1, "Syscall %d fue invocada %d veces\n", id, buf[id]);
        exit();
    }

    printf(1, "Listado de invocaciones:\n");
    for(int i = 0; i < 64; i++){
        if(buf[i] > 0)
            printf(1, "Syscall %d: %d veces\n", i, buf[i]);
    }

    exit();
}
