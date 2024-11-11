#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    printf("Ejecutando test de mprotect\n");
    char *addr = sbrk(0);  // Obtener la dirección actual del heap
    sbrk(4096);  // Reservar una página
    printf("Dirección de la página: %p\n", addr);
    // Intentar proteger la nueva página
    if (mprotect(addr, 1) == -1) {
        printf("mprotect falló\n");
    }
    printf("Protección exitosa\n");
    if (fork() == 0) {
        printf("-----Hijo-----\n");
        // Intentar escribir en la página protegida
        char *ptr = addr;
        *ptr = 'A';  // Esto debería fallar si la protección es exitosa
        printf("Valor en la dirección: %d\n", *ptr);  
        exit(0);
    }
    sleep(10);
    printf("-----Padre-----\n");
    printf("quitando protección\n");
    if (munprotect(addr, 1) == -1) {
        printf("munprotect falló\n");
    }
    printf("Protección quitada\n");
    // Intentar escribir en la página protegida
    char *ptr = addr;
    *ptr = 'A';  // A == 65 en ascii
    printf("Valor en la dirección: %d\n", *ptr);  
    exit(0);
}
