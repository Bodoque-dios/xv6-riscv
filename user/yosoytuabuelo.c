#include "kernel/types.h" // for basic types like int
#include "user/user.h"


int
main(int argc, char *argv[])
{
    int ancestornumber;
    if (argc != 2)
    {
        fprintf(2, "Usage: yosoytuabuelo <ancestornumber>\n");
        exit(1);
    }
    ancestornumber = atoi(argv[1]);
    int ancestorpid = getancestorpid(ancestornumber);
    printf("PID del ancestro de nivel %d: %d\n", ancestornumber, ancestorpid);
    exit(0);
}