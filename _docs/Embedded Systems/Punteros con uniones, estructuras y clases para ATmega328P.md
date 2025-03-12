## Direcciones correctas para ATmega328P

El ATmega328P es un microcontrolador de 8 bits con arquitectura AVR.
### Registros importantes del ATmega328P

```cpp
// Definiciones de direcciones de registros del ATmega328P
#define PINB  (*(volatile uint8_t *)(0x23))
#define DDRB  (*(volatile uint8_t *)(0x24))
#define PORTB (*(volatile uint8_t *)(0x25))

#define PINC  (*(volatile uint8_t *)(0x26))
#define DDRC  (*(volatile uint8_t *)(0x27))
#define PORTC (*(volatile uint8_t *)(0x28))

#define PIND  (*(volatile uint8_t *)(0x29))
#define DDRD  (*(volatile uint8_t *)(0x2A))
#define PORTD (*(volatile uint8_t *)(0x2B))

// ADC
#define ADCL  (*(volatile uint8_t *)(0x78))
#define ADCH  (*(volatile uint8_t *)(0x79))
#define ADCSRA (*(volatile uint8_t *)(0x7A))
#define ADMUX  (*(volatile uint8_t *)(0x7C))

// Timer/Counter 0
#define TCNT0  (*(volatile uint8_t *)(0x46))
#define TCCR0A (*(volatile uint8_t *)(0x44))
#define TCCR0B (*(volatile uint8_t *)(0x45))
#define OCR0A  (*(volatile uint8_t *)(0x47))
#define OCR0B  (*(volatile uint8_t *)(0x48))

// I2C (TWI)
#define TWBR   (*(volatile uint8_t *)(0xB8))
#define TWSR   (*(volatile uint8_t *)(0xB9))
#define TWAR   (*(volatile uint8_t *)(0xBA))
#define TWDR   (*(volatile uint8_t *)(0xBB))
#define TWCR   (*(volatile uint8_t *)(0xBC))
```

## Ejemplo: Acceso al ADC

```cpp
// Estructura para los registros del ADC del ATmega328P
struct ADC_Registers {
    volatile uint8_t ADCL;    // 0x78
    volatile uint8_t ADCH;    // 0x79
    volatile uint8_t ADCSRA;  // 0x7A
    volatile uint8_t ADCSRB;  // 0x7B
    volatile uint8_t ADMUX;   // 0x7C
};

// Apuntar a la dirección base del ADC
ADC_Registers *ADC = (ADC_Registers*)0x78;

// Configurar y leer el ADC
void configurarADC() {
    // ADMUX: Referencia = AVcc, Canal = ADC0
    ADC->ADMUX = (1 << 6);   // REFS0 = 1, MUX3:0 = 0000
    
    // ADCSRA: Habilitar ADC, Prescaler = 128 (para 16MHz -> 125kHz)
    ADC->ADCSRA = (1 << 7) | (1 << 2) | (1 << 1) | (1 << 0);
}

uint16_t leerADC() {
    // Iniciar conversión
    ADC->ADCSRA |= (1 << 6);
    
    // Esperar a que termine
    while(ADC->ADCSRA & (1 << 6));
    
    // Leer resultado (primero ADCL, luego ADCH)
    uint8_t low = ADC->ADCL;
    uint8_t high = ADC->ADCH;
    
    return (high << 8) | low;
}
```

## Ejemplo: Control de puertos I/O

```cpp
// Estructura para los registros de un puerto GPIO
struct GPIO_Port {
    volatile uint8_t PIN;     // Puerto de entrada
    volatile uint8_t DDR;     // Registro de dirección de datos
    volatile uint8_t PORT;    // Puerto de salida
};

// Punteros a los puertos B, C y D
GPIO_Port *PORTB_REG = (GPIO_Port*)0x23;
GPIO_Port *PORTC_REG = (GPIO_Port*)0x26;
GPIO_Port *PORTD_REG = (GPIO_Port*)0x29;

// Ejemplo de uso
void configurarLED() {
    // LED conectado a PB5 (Arduino Uno pin 13)
    PORTB_REG->DDR |= (1 << 5);  // Configurar como salida
}

void encenderLED() {
    PORTB_REG->PORT |= (1 << 5);  // Poner en HIGH
}

void apagarLED() {
    PORTB_REG->PORT &= ~(1 << 5); // Poner en LOW
}

bool leerBoton() {
    // Botón conectado a PD2 (Arduino Uno pin 2)
    return PORTD_REG->PIN & (1 << 2); // Leer estado
}
```

## Ejemplo: I2C (TWI) en ATmega328P

```cpp
// Estructura para los registros TWI (I2C)
struct TWI_Registers {
    volatile uint8_t TWBR;   // 0xB8 - TWI Bit Rate Register
    volatile uint8_t TWSR;   // 0xB9 - TWI Status Register
    volatile uint8_t TWAR;   // 0xBA - TWI Address Register
    volatile uint8_t TWDR;   // 0xBB - TWI Data Register
    volatile uint8_t TWCR;   // 0xBC - TWI Control Register
    volatile uint8_t TWAMR;  // 0xBD - TWI Address Mask Register
};

TWI_Registers *TWI = (TWI_Registers*)0xB8;

class I2CSensor {
private:
    uint8_t address;
    
public:
    I2CSensor(uint8_t addr) : address(addr) {
        // Configurar velocidad I2C para 100kHz con reloj de 16MHz
        TWI->TWBR = 72;
        // Habilitar TWI
        TWI->TWCR = (1 << 2); // TWEN = 1
    }
    
    bool iniciarTransmision() {
        // Condición de inicio
        TWI->TWCR = (1 << 7) | (1 << 5) | (1 << 2); // TWINT | TWSTA | TWEN
        while (!(TWI->TWCR & (1 << 7))); // Esperar a que termine (TWINT)
        
        // Comprobar código de estado
        if ((TWI->TWSR & 0xF8) != 0x08) return false;
        
        // Enviar dirección + Write
        TWI->TWDR = (address << 1);
        TWI->TWCR = (1 << 7) | (1 << 2); // TWINT | TWEN
        while (!(TWI->TWCR & (1 << 7))); // Esperar
        
        return ((TWI->TWSR & 0xF8) == 0x18); // Verificar ACK
    }
    
    // Métodos adicionales para lectura/escritura omitidos por brevedad
};
```

## Uso de uniones para manipular registros

```cpp
// Unión para manipular el registro ADCSRA
union ADCSRARegister {
    uint8_t valor;
    struct {
        uint8_t ADPS  : 3;  // Bits 0-2: Prescaler
        uint8_t ADIE  : 1;  // Bit 3: Interrupt Enable
        uint8_t ADIF  : 1;  // Bit 4: Interrupt Flag
        uint8_t ADATE : 1;  // Bit 5: Auto Trigger Enable
        uint8_t ADSC  : 1;  // Bit 6: Start Conversion
        uint8_t ADEN  : 1;  // Bit 7: ADC Enable
    } bits;
};

volatile ADCSRARegister *adcsra = (volatile ADCSRARegister*)0x7A;

// Configurar ADC sin afectar otros bits
void habilitarADC() {
    adcsra->bits.ADEN = 1;  // Activar ADC
    adcsra->bits.ADPS0 = 1; // Configurar prescaler a 128
    adcsra->bits.ADPS1 = 1;
    adcsra->bits.ADPS2 = 1;
}

void iniciarConversion() {
    adcsra->bits.ADSC = 1;  // Iniciar conversión
}
```

