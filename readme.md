# Informe: Protección de Memoria en xv6

## Funcionamiento y Lógica de la Protección de Memoria

El sistema de protección de memoria en xv6 permite a un proceso establecer ciertas páginas de memoria como de solo lectura, de manera que la escritura en esas páginas esté restringida. Esto se implementa modificando las entradas de tabla de páginas (PTE) correspondientes, específicamente el bit de escritura (PTE_W) de cada página.

En xv6, que utiliza el estándar de direcciones virtuales Sv39, los bits más bajos de cada PTE incluyen las flags, con el último bit representando si la entrada es válida (PTE_V) y el penúltimo si la página permite escritura. Con esta estructura en mente, `mprotect` y `munprotect` recorren las páginas, validan que las direcciones y longitudes sean válidas y utilizan la función `walk` para obtener el puntero a cada PTE y modificar su bit de escritura.

## Explicación de las Modificaciones Realizadas

Se añadieron dos nuevas llamadas de sistema: `mprotect` y `munprotect`. Ambas permiten cambiar los permisos de escritura de páginas específicas:

- **`mprotect`**: Marca las páginas como de solo lectura al poner en 0 el bit de escritura (PTE_W).
- **`munprotect`**: Restaura el permiso de escritura para esas páginas al poner el bit de escritura en 1.

### Funcionamiento de `mprotect`

La función `mprotect` toma dos argumentos: `addr` (la dirección inicial de la región de memoria a proteger) y `len` (el número de páginas a proteger). 
```c
int mprotect(void *addr, int len)
{
    if (!addr || len <= 0)
        return -1;
```

1. **Verificación de Parámetros**: Primero, se verifica que `addr` no sea `NULL` y que `len` sea un valor positivo. Si alguno de estos parámetros es inválido, la función retorna `-1`, indicando un error.

```c
    struct proc *p = myproc();
```

2. **Obtener el Proceso Actual**: La función utiliza `myproc()` para acceder al proceso actual,  para acceder a la tabla de páginas.

```c
    uint64 total_len = len * PGSIZE;

    if ((uint64)addr >= MAXVA || (uint64)addr + total_len > MAXVA)
        return -1;
```

3. **Verificación de Límites de Dirección**: `total_len` representa el tamaño total de la región de memoria a proteger en bytes. La función verifica que `addr` y `addr + total_len` estén dentro del espacio de usuario permitido. 
```c
    for (int i = 0; i < len; i++)
    {
        uint64 va = (uint64)addr + i * PGSIZE;
```

4. **Recorrido de Páginas**: La función recorre las `len` páginas especificadas, calculando la dirección virtual de cada página a proteger.

```c
        pte_t *pte = walk(p->pagetable, va, 0);
        if (pte == 0) return -1;
```

5. **Obtener el PTE de cada página**: `walk` busca la PTE correspondiente. Si el resultado es -1 no la encontró

```c
        if ((*pte & PTE_V) == 0) return -1;
```

6. **Validación de Página**: La función verifica que la página esté mapeada en la memoria.

```c
        *pte &= ~PTE_W;
    }
    return 0;
}
```

7. **Modificación del bit de Escritura**: Con `*pte &= ~PTE_W`  se deja bit de escritura en la PTE en 0, estableciendo la página como de solo lectura, haciendo un AND NOT . Finalmente, la función retorna `0` si todas las páginas fueron protegidas con éxito.

### Explicación de `munprotect`

`munprotect` hace casi lo mismo que `mprotect`, pero en lugar de dejar el bit de escritura en 0, lo deja en 1, permitiendo que las páginas sean escribibles.

## Dificultades Encontradas y Soluciones Implementadas

- Se tuvo que investigar como XV6 manejaba la memoria y como se accedian a las PTE en el archivo vm.c.
- No sabía como modificar la PTE: al aprender sobre el estandar sv39 se pudo encontrar  que se debía cambiar para actualizar los permisos
- No se sabia si las modificaciones funcionaban: Se creo un programa de usuario `test` que prueba las funciones implementadas para validar que estas funcionen correctamente.



Nota: no se explico la creación de las llamadas del sistema sino que en la lógica de estas ya que esto fue visto en otras tareas anteriores.