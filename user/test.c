#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"

int main(int argc, char *argv[])
{
    char *path = "/archivo";
    int fd;

    printf("------------Paso 1------------\n");
    printf("-----Creacion del archivo-----\n");
    fd = open(path, O_CREATE | O_RDWR);
    if (fd < 0)
    {
        printf("Error al crear el archivo\n");
        exit(1);
    }
    else
    {
        printf("-          Correcto          -\n");
    }

    printf("------------Paso 2------------\n");
    printf("-----Escritura inicial--------\n");
    fd = open(path, O_RDWR);
    if (write(fd, "Esto es una prueba\n", 18) != 18)
    {
        printf("Error al escribir en el archivo\n");
        close(fd);
        exit(1);
    }
    close(fd);
    printf("-          Correcto          -\n");

    printf("------------Paso 3------------\n");
    printf("---------Solo Lectura---------\n");
    if (chmod(path, 1) < 0)
    {
        printf("Error al cambiar permisos a solo lectura\n");
        exit(1);
    }
    else
    {
        printf("-          Correcto          -\n");
    }

    printf("------------Paso 4------------\n");
    printf("--Escritura con Solo Lectura--\n");
    fd = open(path, O_WRONLY);
    if (fd < 0)
    {
        printf("-          Correcto          -\n");
    }
    else
    {
        printf("-          Error             -\n");
        close(fd);
    }

    printf("------------Paso 5------------\n");
    printf("----Permisos de read/write----\n");
    if (chmod(path, 3) < 0)
    {
        printf("-          Error             -\n");
        exit(1);
    }
    else
    {
        printf("-          Correcto          -\n");
    }

    printf("------------Paso 6------------\n");
    printf("------validar read/write------\n");
    fd = open(path, O_WRONLY);
    if (fd < 0)
    {
        printf("Error al abrir el archivo en modo escritura\n");
        exit(1);
    }
    if (write(fd, "Texto final\n", 12) != 12)
    {
        printf("-          Error             -\n");
    }
    else
    {
        printf("-          Correcto          -\n");
    }
    close(fd);

    printf("------------Paso 7------------\n");
    printf("-cambiar permiso a inmutable--\n");
    if (chmod(path, 5) < 0)
    {
        printf("-          Error             -\n");
        exit(1);
    }
    else
    {
        printf("-          Correcto          -\n");
    }
    printf("------------Paso 8------------\n");
    printf("----Intentar abrir archivo----\n");
    fd = open(path, O_WRONLY);
    if (fd < 0)
    {
        printf("-          Correcto          -\n");
    }
    else
    {
        printf("Error: Se pudo abrir en modo escritura con permisos de inmutable\n");
        close(fd);
    }

    printf("------------Paso 9------------\n");
    printf("-----probar inmutabilidad-----\n");
    if (chmod(path, 3) < 0)
    {
        printf("-          Correcto          -\n");
    }
    else
    {
        printf("-          Error             -\n");
    }
    printf("------------------------------\n");

    printf("Prueba completada\n");
    exit(0);
}
