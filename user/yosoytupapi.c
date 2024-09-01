#include "kernel/types.h" // for basic types like int
#include "user/user.h"


int
main(int argc, char *argv[])
{
  int ppid = getppid();
  printf("PID del proceso padre: %d\n", ppid);
  exit(0);
}
