# EmbeddedSystems

### Instalar avg-gcc:

Abre una terminal y ejecuta el siguiente comando:

```
sudo apt-get update
sudo apt-get install gcc-avr binutils-avr gdb-avr avr-libc avrdude
```

### Compilación

Abre una terminal en el directorio donde guardaste tu archivo main.c. El proceso de compilación se realiza en dos pasos: primero, compilas tu código C a un archivo objeto, y luego enlazas ese archivo objeto para crear el archivo ejecutable en formato .hex.

a. Compilar el código fuente a un archivo objeto:
```
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c main.cpp -o main.o
```

En este comando:

- -Os optimiza el código para tamaño.
- -DF_CPU=16000000UL define la frecuencia del reloj del microcontrolador, necesario para las funciones de tiempo. Ajusta este valor según tu hardware.
- -mmcu=atmega328p especifica el tipo de microcontrolador objetivo. Cambia atmega328p por tu modelo específico si es necesario.
- -c le dice a avr-gcc que solo compile o ensamble el código, pero no lo enlace.
main.c es el nombre de tu archivo fuente.
- -o main.o especifica el nombre del archivo de salida.

b. Enlazar el archivo objeto para crear un archivo ejecutable .hex:

```
avr-gcc -mmcu=atmega328p main.o -o main.elf
avr-objcopy -O ihex -R .eeprom main.elf main.hex
```

El primer comando enlaza el archivo objeto main.o en un archivo ejecutable ELF `main.elf`.
El segundo comando convierte el archivo ELF main.elf en un archivo HEX `main.hex`, que es el que se cargará en el microcontrolador. La opción `-R` .eeprom evita incluir la sección EEPROM en el archivo `.hex`, ya que esta se maneja generalmente de manera separada.


## Instalar AVR_GCC en Windows

Descargar el instalador de [WinAVR](https://sourceforge.net/projects/winavr/)

`<install>` = El directorio donde instaló WinAVR. (Usualmente en `C:/WinAVR-20100110/`)

`<install>\bin`
Los programas de desarrollo de software AVR. Este directorio debe estar en su variable de entorno PATH. Esto incluye:
- GNU Binutils
- CCG
- avrdude
- Depurador GNU (GDB)
- Conocimiento
- SimulAVR
- Registro
- Varias DLL necesarias

`<instalar>\utils\bin`
Una colección de programas Unix creados para la plataforma Windows. Los programas make y sh (bash) residen aquí. Este directorio debe estar en su variable de entorno PATH.

`<instalar>\avr\lib`
Bibliotecas avr-libc, archivos de inicio, scripts de vinculación y demás.

Una vez añadido el diectorio su variable de entorno PATH, Ud podra usar el comando `avr-gcc`, de lo contrario debera usar la dirección completa, ej. `C:\WinAVR-20100110\bin\avr-gcc`
