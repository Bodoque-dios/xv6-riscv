#include "kernel/types.h" // for basic types like int
#include "kernel/stat.h"  // for file stats, if needed
#include "user/user.h"

const char *spongebob_names[] = {
    "SpongeBob SquarePants", "Patrick Star", "Squidward Tentacles", 
    "Sandy Cheeks", "Mr. Krabs", "Plankton", 
    "Gary the Snail", "Mrs. Puff", "Larry the Lobster", 
    "Pearl Krabs", "Karen Plankton", "Mermaid Man", 
    "Barnacle Boy", "Bubble Bass", "Man Ray", 
    "Dirty Bubble", "Fishbowl Gary", "The Hash-Slinging Slasher", 
    "The Flying Dutchman", "DoodleBob"
};

int 
main()
{  
  int n = 20;
  printf("Creando %d procesos nuevos\n", n);
  for(int i = 0; i < n; i++) {
    int nuevo_proceso = fork();
    if(nuevo_proceso == 0) { //Child
      sleep(i);
      printf("Ejecutando [%s] (%d) con pid %d\n",spongebob_names[i] ,  i, getpid());
      exit(0);
    }
  }
  
  for(int i = 0; i < n; i++) {
    wait(0);
  }
  exit(0);
}
