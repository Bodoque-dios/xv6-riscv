
# Parte 1

## Llamada getppid()

```c
uint64
sys_getppid(void)
{
  return myproc()->parent->pid;
}
```

Esta llamada usa la función myproc para conseguir su propio proceso, luego consigue el padre y su id. Finalmente retorna este id.

## Modificaciones

Para crear este nuevo syscall, cree una nueva definicion en `syscall.h` y la agregue al array que mapea las llamadas en `syscall.c`. Luego cree la funcion en sí en `sysproc.c` y agregue la funcion en `user.h` y `usys.pl`. Finalmente cree un programa llamado `yosoytupapi.c` para probar la llamada. 

Este proceso ocurrio sin mayores dificultades, lo mas complicado fue encontrar el archivo `sysproc.c` para escribir la función.

# Parte 2

## Llamada getancestorpid()

```c
uint64
sys_getancestorpid(void)
{
  int n;
  argint(0, &n);
  struct proc *p = myproc();
  for(int i = 0; i < n; i++)
  {
    if(p->parent == 0)
    {
      return -1;
    } else {
      p = p->parent;
    }
  }
  return p->pid;
}
```

Esta funcion usa`argint()` para tomar el input del usuario. Luego hace un loop n cantidad de veces hasta llegar al ancestro deseado, si en algun momento no hay más ancestros, retorna -1 de lo contrario retorna el pid del ancestro deseado.
## Modificaciones 

La creación de esta llamada fue casi lo mismo que la anterior, siguiendo los mismos pasos. para probar esta llamada, cree el programa `yosoytuabuelo.c` 

A diferencia de la anterior, esta toma un valor de entrada pero el arreglo que mapea las syscall este espera que las funciones no tengan entrada por lo que tuve que encontrar otra forma para que la funcion tome lo que el usuario ingresa. 