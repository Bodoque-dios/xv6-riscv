# Informe

## Instalación

Como utilizo Linux, todo fue ejecutado directamente en mi máquina y no en una VM. Los pasos que seguí para instalar xv6, QEMU y la toolchain fueron los siguientes:

1. El primer paso fue actualizar mi sistema con `sudo pacman -Syu`.
2. Luego, instalé QEMU siguiendo las instrucciones de este [enlace](https://wiki.archlinux.org/title/QEMU) usando `sudo pacman -S qemu-full`.
3. Después, instalé la toolchain desde el AUR siguiendo este [enlace](https://aur.archlinux.org/packages/riscv-gnu-toolchain-bin) usando `yay -S riscv-gnu-toolchain-bin`.
4. Luego, cloné xv6 desde el repositorio del profesor.
5. Realicé una pequeña modificación al Makefile de xv6 para que reconozca la toolchain que instalé.
6. Finalmente, ejecuté `make qemu` y obtuve las siguientes imágenes.

## Capturas

![](image.png)
![](image2.png)
