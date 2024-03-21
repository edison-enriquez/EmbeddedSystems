#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Configura el pin PB5 como salida
    DDRB |= (1 << DDB5);

    while(1)
    {
        // Enciende el LED
        PORTB |= (1 << PORTB5);
        _delay_ms(1000); // Espera 1 segundo

        // Apaga el LED
        PORTB &= ~(1 << PORTB5);
        _delay_ms(1000); // Espera 1 segundo
    }
}
