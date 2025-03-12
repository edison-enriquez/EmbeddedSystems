Una `union` permite almacenar diferentes tipos de datos en el mismo espacio de memoria, aunque sólo puede contener un valor válido a la vez. Es decir, todos sus miembros comparten la misma ubicación de memoria.

### Concepto básico de `union`
```cpp
union MiUnion {
    uint8_t valor8;     // 1 byte
    uint16_t valor16;   // 2 bytes
    uint32_t valor32;   // 4 bytes
};  // Esta unión ocupará 4 bytes (el tamaño del miembro más grande)
```

Al modificar cualquiera de estos miembros, se está escribiendo en la misma posición de memoria, por lo que se afecta a los otros miembros.
### Ejemplo

```c++
#include <iostream>

using namespace std;

// Definición de una union
union Datos {
    int entero;
    float decimal;
    char caracter;
};

int main() {
    Datos dato;

    dato.entero = 10;
    cout << "Dato entero: " << dato.entero << endl;

    dato.decimal = 3.14;
    cout << "Dato decimal: " << dato.decimal << endl;

    dato.caracter = 'A';
    cout << "Dato caracter: " << dato.caracter << endl;

    return 0;
}
```

## Aplicación en sistemas embebidos con ATmega328P

En microcontroladores como el ATmega328P, las uniones son extremadamente útiles para manipular registros de hardware a diferentes niveles de granularidad (bit a bit o en bloque).
### Ejemplo 1: Control del Timer1 del ATmega328P

El Timer1 del ATmega328P tiene varios registros de control, incluyendo `TCCR1A` y `TCCR1B`. Usando uniones, podemos acceder a bits individuales o al registro completo:

```c
// Definiciones del registro TCCR1A (Timer/Counter Control Register 1A)
union TCCR1A_Register {
    uint8_t value;      // Valor completo del registro
    struct {
        uint8_t WGM10 : 1;    // Bit 0: Waveform Generation Mode bit 0
        uint8_t WGM11 : 1;    // Bit 1: Waveform Generation Mode bit 1
        uint8_t FOC1B : 1;    // Bit 2: Force Output Compare for Channel B
        uint8_t FOC1A : 1;    // Bit 3: Force Output Compare for Channel A
        uint8_t COM1B0 : 1;   // Bit 4: Compare Output Mode for Channel B bit 0
        uint8_t COM1B1 : 1;   // Bit 5: Compare Output Mode for Channel B bit 1
        uint8_t COM1A0 : 1;   // Bit 6: Compare Output Mode for Channel A bit 0
        uint8_t COM1A1 : 1;   // Bit 7: Compare Output Mode for Channel A bit 1
    } bits;
};

// Puntero al registro real en memoria
volatile TCCR1A_Register* tccr1a = (volatile TCCR1A_Register*)0x80;  // Dirección de TCCR1A
```

### Uso práctico: Configuración de PWM

```c
void configurarPWM() {
    // Usando bits individuales
    tccr1a->bits.WGM10 = 1;    // Configura Fast PWM de 8 bits
    tccr1a->bits.WGM11 = 0;
    tccr1a->bits.COM1A1 = 1;   // Clear OC1A on compare match, set at BOTTOM
    tccr1a->bits.COM1A0 = 0;
    
    // Alternativamente, usando el valor completo
    // tccr1a->value = 0b10000001;  // Equivalente al código anterior
}
```

### Ejemplo 2: Manipulación del ADC

El ADC del ATmega328P tiene un registro de control (ADCSRA) con varios bits de configuración. Usando una unión, podemos acceder a cada bit o al registro completo:

```c
union ADCSRA_Register {
    uint8_t value;
    struct {
        uint8_t ADPS0 : 1;   // Bit 0: Prescaler Select Bit 0
        uint8_t ADPS1 : 1;   // Bit 1: Prescaler Select Bit 1
        uint8_t ADPS2 : 1;   // Bit 2: Prescaler Select Bit 2
        uint8_t ADIE  : 1;   // Bit 3: ADC Interrupt Enable
        uint8_t ADIF  : 1;   // Bit 4: ADC Interrupt Flag
        uint8_t ADATE : 1;   // Bit 5: ADC Auto Trigger Enable
        uint8_t ADSC  : 1;   // Bit 6: ADC Start Conversion
        uint8_t ADEN  : 1;   // Bit 7: ADC Enable
    } bits;
};

volatile ADCSRA_Register* adcsra = (volatile ADCSRA_Register*)0x7A;  // Dirección de ADCSRA
```
### Código funcional para leer el ADC

```c
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// Definición de unión para ADCSRA
union ADCSRA_Register {
    uint8_t value;
    struct {
        uint8_t ADPS0 : 1;
        uint8_t ADPS1 : 1;
        uint8_t ADPS2 : 1;
        uint8_t ADIE  : 1;
        uint8_t ADIF  : 1;
        uint8_t ADATE : 1;
        uint8_t ADSC  : 1;
        uint8_t ADEN  : 1;
    } bits;
};

// Definición de unión para ADMUX
union ADMUX_Register {
    uint8_t value;
    struct {
        uint8_t MUX0  : 1;   // Multiplexer bit 0
        uint8_t MUX1  : 1;   // Multiplexer bit 1
        uint8_t MUX2  : 1;   // Multiplexer bit 2
        uint8_t MUX3  : 1;   // Multiplexer bit 3
        uint8_t ADLAR : 1;   // ADC Left Adjust Result
        uint8_t REFS0 : 1;   // Reference Selection bit 0
        uint8_t REFS1 : 1;   // Reference Selection bit 1
        uint8_t RESERVED : 1;
    } bits;
};

// Definición para acceso al resultado del ADC
union ADCResult {
    uint16_t value;
    struct {
        uint8_t ADCL;
        uint8_t ADCH;
    } bytes;
};

int main(void) {
    // Configurar punteros a los registros
    volatile ADCSRA_Register* adcsra = (volatile ADCSRA_Register*)0x7A;
    volatile ADMUX_Register* admux = (volatile ADMUX_Register*)0x7C;
    volatile ADCResult* adcResult = (volatile ADCResult*)0x78;  // ADCL está en 0x78, ADCH en 0x79
    
    // Configurar ADC
    admux->bits.REFS0 = 1;    // Referencia = AVCC
    admux->bits.REFS1 = 0;
    admux->bits.MUX0 = 0;     // Canal ADC0 (PC0)
    admux->bits.MUX1 = 0;
    admux->bits.MUX2 = 0;
    admux->bits.MUX3 = 0;
    
    adcsra->bits.ADEN = 1;    // Habilitar ADC
    adcsra->bits.ADPS0 = 1;   // Prescaler = 128
    adcsra->bits.ADPS1 = 1;   // para un reloj de 16MHz
    adcsra->bits.ADPS2 = 1;   // frecuencia ADC = 125kHz
    
    // Configurar PORTB para salida (para mostrar el resultado)
    DDRB = 0xFF;
    
    while(1) {
        // Iniciar conversión
        adcsra->bits.ADSC = 1;
        
        // Esperar a que termine
        while(adcsra->bits.ADSC);
        
        // Mostrar el byte alto del resultado en PORTB (simplificación)
        PORTB = adcResult->bytes.ADCH;
        
        _delay_ms(100);
    }
    
    return 0;
}
```

### Ejemplo 3: Unión para manipular puertos GPIO

En este ejemplo, usamos una unión para manipular los puertos de E/S digital:

```c
union PORT_Register {
    uint8_t value;
    struct {
        uint8_t PIN0 : 1;
        uint8_t PIN1 : 1;
        uint8_t PIN2 : 1;
        uint8_t PIN3 : 1;
        uint8_t PIN4 : 1;
        uint8_t PIN5 : 1;
        uint8_t PIN6 : 1;
        uint8_t PIN7 : 1;
    } pins;
    
    // También podemos agrupar los pines en conjuntos lógicos
    struct {
        uint8_t nibble_low : 4;   // Pines 0-3
        uint8_t nibble_high : 4;  // Pines 4-7
    } groups;
};

volatile PORT_Register* portb = (volatile PORT_Register*)0x25;  // PORTB
volatile PORT_Register* ddrb = (volatile PORT_Register*)0x24;   // DDRB

void configurarLEDs() {
    // Configurar pines 0-3 como salidas para LEDs
    ddrb->groups.nibble_low = 0x0F;  // Todos los pines bajos como salida
    
    // Encender LEDs alternados
    portb->pins.PIN0 = 1;
    portb->pins.PIN2 = 1;
    
    // También podríamos hacer: portb->value = 0b00000101;
}
```

## Ventajas de usar uniones en sistemas embebidos

1. **Acceso granular**: Permiten manipular bits individuales sin operaciones bit a bit manuales.
2. **Legibilidad**: Hacen que el código sea más claro y autoexplicativo.
3. **Mantenimiento**: Facilitan el mantenimiento ya que los nombres de los bits reflejan su función.
4. **Flexibilidad**: Permiten trabajar con el mismo dato a diferentes niveles (bit, byte, word).
5. **Ahorro de memoria**: Al reutilizar el mismo espacio de memoria, son eficientes en sistemas con recursos limitados.

Las uniones son una herramienta poderosa para programación de bajo nivel en microcontroladores como el ATmega328P, donde el acceso directo a los registros de hardware es fundamental para un control preciso del sistema.
# Ejercicio Union en sistemas embebidos

## Objetivo del ejercicio

Crear un controlador de un display LCD de 7 segmentos utilizando uniones para manipular los segmentos individuales y mostrar diferentes patrones de visualización.

## Contexto

En un sistema embebido basado en ATmega328P, tienes conectado un display de 7 segmentos al Puerto B, donde cada pin controla un segmento del display:

- PB0: Segmento A (arriba)
- PB1: Segmento B (arriba derecha)
- PB2: Segmento C (abajo derecha)
- PB3: Segmento D (abajo)
- PB4: Segmento E (abajo izquierda)
- PB5: Segmento F (arriba izquierda)
- PB6: Segmento G (centro)

## Ejercicio

1. Define una unión `SevenSegment` que permita:
    
    - Acceder al valor completo del registro PORTB como un byte
    - Acceder a cada segmento individualmente como bits
    - Acceder a grupos lógicos de segmentos (horizontales/verticales)
2. Implementa las siguientes funciones:
    
    - `mostrarDigito(uint8_t digito)`: Muestra un dígito del 0-9
    - `mostrarPatron(uint8_t patron)`: Muestra un patrón personalizado
    - `animar()`: Crea una animación simple rotando segmentos
3. Bono: Implementa una máquina de estados que muestre diferentes patrones según el valor de un sensor ADC.
## Plantilla de código

```cpp
#include <avr/io.h>
#include <util/delay.h>

// TODO: Define la unión SevenSegment aquí

// Dirección del registro PORTB para ATmega328P
#define PORTB_ADDRESS 0x25

int main(void) {
    // Configurar PORTB como salida
    DDRB = 0x7F;  // 0b01111111 (7 segmentos como salidas)
    
    // TODO: Crear un puntero a la unión SevenSegment apuntando a PORTB
    
    // TODO: Implementar código que utilice la unión para manipular el display
    
    while(1) {
        // Loop principal
    }
    
    return 0;
}

// TODO: Implementar las funciones mostrarDigito, mostrarPatron y animar
```

## Solución esperada

Deberías crear una unión que permita manipular los 7 segmentos tanto a nivel de bit individual como a nivel de byte completo. La unión debería facilitar la visualización de patrones específicos sin necesidad de manipular bits manualmente cada vez.

## Pistas

1. La estructura de una unión básica podría verse así:

```cpp
union SevenSegment {
    uint8_t value;      // Valor completo
    struct {
        uint8_t a : 1;  // Segmento A (bit 0)
        uint8_t b : 1;  // Segmento B (bit 1)
        // ... más segmentos
    } segments;
};
```

2. Para mostrar un dígito, puedes crear un array de patrones predefinidos:

```cpp
const uint8_t digitPatterns[10] = {
    0b00111111,  // 0
    0b00000110,  // 1
    // ... etc.
};
```

3. Piensa en cómo puedes agrupar segmentos lógicamente para simplificar animaciones (por ejemplo, todos los segmentos horizontales, o todos los verticales).

## Desafío adicional

Extiende la unión para manejar múltiples displays de 7 segmentos usando técnicas de multiplexación, donde necesitarás mantener el estado de varios displays mientras activas solo uno a la vez.

Este ejercicio te ayudará a comprender cómo las uniones permiten interpretar la misma región de memoria de múltiples formas, lo cual es especialmente útil para manipular registros de hardware en sistemas embebidos.