# Timer 0 Modo CTC

Para configurar el Timer 0 en modo CTC (Clear Timer on Compare) en el microcontrolador ATmega328p, debes seguir varios pasos importantes y configurar varios registros:

1. Configuración de los registros TCCR0A y TCCR0B:
    - __TCCR0A__: Configura el modo de comparación de salida y el modo de operación del timer.
        - Para activar el modo CTC, debes establecer el bit WGM01.
        - Los bits COM0A1 y COM0A0 configuran la acción en el pin OC0A cuando ocurre una coincidencia de comparación. Por ejemplo, configurar COM0A0 a 1 hará que el pin OC0A se cambie en cada coincidencia.
    - __TCCR0B__: Selecciona el preescalador del reloj, que influye en la resolución y el rango de tiempo del timer.
        -   Los bits CS02, CS01 y CS00 determinan el factor de escala del reloj. Por ejemplo, CS01 a 1 configura el timer con un preescalador de 8.
2. Registro OCR0A (Output Compare Register 0 A):
    - Define el valor que se comparará con el contador del timer. Cuando el contador alcanza este valor, si está configurado, puede cambiar el estado de un pin y el contador se reinicia.
3. Registro TIMSK0 (Timer/Counter Interrupt Mask Register):
    - Si deseas utilizar interrupciones, debes habilitarlas configurando el bit OCIE0A para permitir la interrupción cuando el contador del Timer 0 coincide con el valor en OCR0A.
4. Configuración del pin de salida:
    - Debes configurar el pin correspondiente (por ejemplo, OC0A o OC0B) como salida para ver el efecto de la comparación. Esto se hace normalmente en el registro DDR correspondiente al puerto del pin.

Un ejemplo típico de configuración en C sería el siguiente:

```cpp
#define F_CPU 8000000UL  // Frecuencia del CPU de 8 MHz
#include <avr/io.h>

int main(void) {
    // Configura el pin como salida
    DDRD |= (1<<PD6);  // OC0A está en PD6 para Atmega328p

    // Establece el valor de comparación
    OCR0A = 49;  // Ejemplo para generar un retardo específico

    // Configura el timer en modo CTC
    TCCR0A = (1<<COM0A0) | (1<<WGM01);
    TCCR0B = (1<<CS01);  // Preescalador de 8

    while (1) {
        // El código aquí se ejecutará continuamente
    }

    return 0;
}
```