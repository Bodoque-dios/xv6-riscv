### Funcionamiento y lógica

La implementación de permisos básicos en xv6 permite definir permisos de lectura, escritura y un permiso especial de inmutabilidad para los archivos. Los permisos se gestionan a nivel de inode y se respetan durante las operaciones de apertura, lectura y escritura de archivos. El permiso de inmutabilidad asegura que un archivo no pueda ser modificado ni sus permisos cambiados una vez establecido.

### Explicación de las modificaciones realizadas

1. **Modificación de la estructura de inode:**
   - Se añadió el campo `permissions` en el inode para almacenar los permisos del archivo. Este campo es un `int` donde 0 significa sin permisos, 1 significa solo lectura, 2 significa solo escritura, y 3 significa lectura/escritura.  Adicionalmente el valor 5 significa que el archivo es inmutable. El valor inicial al crear un inode es 3.

2. **Modificación de las operaciones de apertura, lectura y escritura:**
   - Se modificaron las funciones `sys_open`,  y `create` en `kernel/sysfile.c` para que respeten los permisos definidos en el inode. Si un archivo está marcado como solo lectura, no se permite abrirlo en modo escritura y viceversa. Además, si el archivo es inmutable, no se permite modificar su contenido. También se hizo tal que al crear un inode, su permiso inicial fuera 3
   -  `sys_open`: Luego de que la función hace sus validaciones, esta compara las distintas  combinaciones y retorna error en caso de ser necesario
   - `create`: Antes de devolver el inode se le agregó el permiso default de creación 3.

3. **Implementación de la llamada al sistema `chmod`:**
   - Se creó la llamada al sistema `chmod` que permite cambiar los permisos de un archivo. Esta función verifica si el archivo es inmutable antes de permitir cualquier cambio de permisos.

4. **Pruebas:**
   - Se creó un programa de prueba en `user/test.c` que verifica la correcta implementación de los permisos. El programa realiza las siguientes acciones:
     - Crea un archivo con permisos de lectura/escritura.
     - Escribe en el archivo para asegurar que la creación y escritura funcionan.
     - Cambia los permisos a solo lectura y verifica que no se puede escribir en el archivo.
     - Cambia los permisos a inmutable y verifica que no se puede modificar el archivo ni cambiar sus permisos.

### Dificultades encontradas y soluciones implementadas

Las principales dificultades fueron como verificar que el modo de abrir el archivo y el permiso del archivo sean compatibles, ya que podían haber muchas combinaciones compatibles/incompatibles.
Se solucionó al revisar el código existente de xv6 y generar condicionales similares para validar todas las combinaciones deseadas.