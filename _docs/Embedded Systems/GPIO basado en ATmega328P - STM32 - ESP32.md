El GPIO (General Purpose Input/Output) constituye la interfaz básica mediante la cual los microcontroladores interactúan con el mundo físico. Estos pines digitales pueden configurarse como entradas para leer señales externas o como salidas para controlar dispositivos. A continuación, analizaremos formalmente la implementación del GPIO en dos plataformas populares: el ATmega328P, el stm32 y el ESP32.

## GPIO en ATmega328P: Arquitectura de puertos

El ATmega328P organiza sus pines GPIO en tres puertos principales:

- **Puerto B** (PORTB): Pines PB0-PB7 (8 pines)
- **Puerto C** (PORTC): Pines PC0-PC6 (7 pines)
- **Puerto D** (PORTD): Pines PD0-PD7 (8 pines)

### Registros de control

Cada puerto está controlado por tres registros fundamentales:

1. **DDRx (Data Direction Register)**:
    - Configura la dirección del pin (entrada o salida)
    - `0` = Entrada, `1` = Salida
    - Ejemplo: `DDRB = 0x01` configura PB0 como salida y PB1-PB7 como entradas
2. **PORTx (Port Data Register)**:
    - Cuando el pin está configurado como salida: establece el nivel de voltaje
    - Cuando el pin está configurado como entrada: activa/desactiva la resistencia pull-up interna
    - Ejemplo: `PORTB = 0x01` establece PB0 en HIGH y el resto en LOW
3. **PINx (Port Input Pins Register)**:
    - Registro de solo lectura que refleja el estado actual de los pines
    - Ejemplo: `estado = PINB & 0x02` lee el estado de PB1
### Operaciones a nivel de bit

Las operaciones a nivel de bit son fundamentales para manipular pines individuales:
```cpp
// Configurar PB5 como salida
DDRB |= (1 << DDB5);

// Activar PB5 (HIGH)
PORTB |= (1 << PORTB5);

// Desactivar PB5 (LOW)
PORTB &= ~(1 << PORTB5);

// Cambiar estado de PB5 (toggle)
PORTB ^= (1 << PORTB5);

// Leer estado de PB0
if (PINB & (1 << PINB0)) {
    // PB0 está en HIGH
}
```

## GPIO en STM32:Arquitectura de puertos

Los microcontroladores STM32 están basados en la arquitectura ARM Cortex-M y organizan sus pines GPIO en múltiples puertos:

- **Puertos A-G** (GPIOA-GPIOG): Cada puerto contiene hasta 16 pines (dependiendo del modelo específico)
- La nomenclatura de los pines sigue el formato: PA0 (Puerto A, pin 0), PB5 (Puerto B, pin 5), etc.

### Registros de control

A diferencia del ATmega328P, los STM32 utilizan un conjunto más completo de registros para cada puerto:

1. **GPIOx_MODER (Mode Register)**:
    - Define el modo de operación: entrada, salida, función alternativa o analógico
    - 2 bits por pin: 00 = Entrada, 01 = Salida, 10 = Función alternativa, 11 = Analógico
2. **GPIOx_OTYPER (Output Type Register)**:
    - Define el tipo de salida: push-pull o open-drain
    - 1 bit por pin: 0 = Push-pull, 1 = Open-drain
3. **GPIOx_OSPEEDR (Output Speed Register)**:
    - Configura la velocidad de conmutación de los pines
    - 2 bits por pin: 00 = Baja, 01 = Media, 10 = Alta, 11 = Muy alta
4. **GPIOx_PUPDR (Pull-up/Pull-down Register)**:
    - Configura las resistencias internas pull-up o pull-down
    - 2 bits por pin: 00 = Ninguna, 01 = Pull-up, 10 = Pull-down
5. **GPIOx_IDR (Input Data Register)**:
    - Registro de solo lectura para leer el estado de los pines
6. **GPIOx_ODR (Output Data Register)**:
    - Registro para establecer el estado de salida de los pines
7. **GPIOx_BSRR (Bit Set/Reset Register)**:
    - Permite establecer o resetear bits individuales en una única operación atómica
    - Bits 0-15: establecen los pines correspondientes
    - Bits 16-31: resetean los pines correspondientes
8. **GPIOx_LCKR (Lock Register)**:
    - Permite bloquear la configuración de los pines para evitar modificaciones accidentales
9. **GPIOx_AFRL/AFRH (Alternate Function Low/High Registers)**:
    - Seleccionan la función alternativa específica cuando el pin está en modo AF
    - Cada pin puede tener hasta 16 funciones alternativas diferentes


### Reloj y habilitación de puertos

Una diferencia importante en los STM32 es la necesidad de habilitar el reloj para cada puerto GPIO antes de usarlo:
```cpp
// Habilitar reloj para GPIOA
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
```

### Modos y configuración

Los STM32 ofrecen una flexibilidad sustancialmente mayor en la configuración de pines:

1. **Modos de operación**:
    - Entrada
    - Salida (push-pull u open-drain)
    - Función alternativa (para periféricos como UART, SPI, I2C, etc.)
    - Analógico (para ADC)
2. **Opciones de velocidad**:
    - Baja (típicamente hasta 2 MHz)
    - Media (típicamente hasta 25 MHz)
    - Alta (típicamente hasta 50 MHz)
    - Muy alta (típicamente hasta 100 MHz)
3. **Resistencias internas**:
    - Pull-up
    - Pull-down
    - Flotante (sin resistencia)

### Ejemplo de configuración
```cpp
// Configurar PA5 como salida push-pull de alta velocidad
// 1. Habilitar reloj para GPIOA
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

// 2. Configurar PA5 como salida
GPIOA->MODER &= ~(0x3 << (5 * 2));  // Limpiar bits
GPIOA->MODER |= (0x1 << (5 * 2));   // Establecer como salida

// 3. Configurar como push-pull
GPIOA->OTYPER &= ~(0x1 << 5);       // 0 = Push-pull

// 4. Configurar alta velocidad
GPIOA->OSPEEDR &= ~(0x3 << (5 * 2)); // Limpiar bits
GPIOA->OSPEEDR |= (0x2 << (5 * 2));  // 10 = Alta velocidad

// 5. Sin resistencias pull-up/down
GPIOA->PUPDR &= ~(0x3 << (5 * 2));   // 00 = Sin pull-up/down
```

### Operaciones de escritura/lectura

Los STM32 ofrecen múltiples métodos para manipular los pines:

1. **Escritura mediante ODR**:
```cpp
// Establecer PA5 en HIGH GPIOA->ODR |= (1 << 5); // Establecer PA5 en LOW GPIOA->ODR &= ~(1 << 5);`
```

2. **Escritura mediante BSRR** (más eficiente, operación atómica):
```cpp
// Establecer PA5 en HIGH GPIOA->BSRR = (1 << 5); // Establecer PA5 en LOW GPIOA->BSRR = (1 << (5 + 16));
````

3. **Lectura**:
```cpp
// Leer estado de PA7 if (GPIOA->IDR & (1 << 7)) {     // PA7 está en HIGH }
```

## Características adicionales del STM32

### Funciones alternativas

Los pines del STM32 pueden configurarse para múltiples funciones alternativas, como UART, SPI, I2C, timers, etc:

```cpp
// Configurar PA2 para USART2_TX (AF7)
GPIOA->MODER &= ~(0x3 << (2 * 2));
GPIOA->MODER |= (0x2 << (2 * 2));  // Modo función alternativa

// Seleccionar AF7 (USART)
GPIOA->AFR[0] &= ~(0xF << (2 * 4));  // AFR[0] para pines 0-7
GPIOA->AFR[0] |= (0x7 << (2 * 4));   // 7 = USART
```

### ### Interrupciones EXTI

El sistema de interrupciones externas (EXTI) en STM32 es muy flexible
```cpp
// Configurar PA0 para interrupción por flanco ascendente
// 1. Configurar como entrada
GPIOA->MODER &= ~(0x3 << (0 * 2));  // 00 = Entrada

// 2. Conectar PA0 a línea EXTI0
SYSCFG->EXTICR[0] &= ~(0xF << 0);   // Limpiar bits
SYSCFG->EXTICR[0] |= (0x0 << 0);    // 0 = GPIOA

// 3. Habilitar interrupción en flanco ascendente
EXTI->RTSR |= (1 << 0);    // Flanco ascendente
EXTI->FTSR &= ~(1 << 0);   // No flanco descendente
EXTI->IMR |= (1 << 0);     // Desenmascarar interrupción

// 4. Configurar NVIC
NVIC_SetPriority(EXTI0_IRQn, 0);
NVIC_EnableIRQ(EXTI0_IRQn);
```

## ## Organización de la memoria en STM32

En los microcontroladores STM32, todos los periféricos están mapeados en memoria. Esto significa que cada registro de control tiene una dirección de memoria específica. Para facilitar el acceso a estos registros, los fabricantes proporcionan archivos de cabecera que definen estructuras y punteros a estas direcciones.

Por ejemplo, en los archivos de cabecera del STM32, encontrarás definiciones como estas:
```cpp
// Definición de la estructura que representa un periférico GPIO
typedef struct {
  volatile uint32_t MODER;    // Offset: 0x00 - Mode register
  volatile uint32_t OTYPER;   // Offset: 0x04 - Output type register
  volatile uint32_t OSPEEDR;  // Offset: 0x08 - Output speed register
  volatile uint32_t PUPDR;    // Offset: 0x0C - Pull-up/pull-down register
  volatile uint32_t IDR;      // Offset: 0x10 - Input data register
  volatile uint32_t ODR;      // Offset: 0x14 - Output data register
  volatile uint32_t BSRR;     // Offset: 0x18 - Bit set/reset register
  volatile uint32_t LCKR;     // Offset: 0x1C - Configuration lock register
  volatile uint32_t AFR[2];   // Offset: 0x20-0x24 - Alternate function registers
} GPIO_TypeDef;

// Definición del puntero a la dirección base de GPIOA
#define GPIOA_BASE     (AHB1PERIPH_BASE + 0x0000)
#define GPIOA          ((GPIO_TypeDef *) GPIOA_BASE)
```

## Por qué se usa esta implementación

Esta implementación basada en punteros a estructuras tiene varias ventajas:

1. **Acceso directo a hardware**: Permite manipular directamente los registros del hardware.
2. **Eficiencia**: Es muy eficiente en términos de rendimiento y uso de memoria.
3. **Organización estructurada**: Agrupa todos los registros relacionados con un periférico en una única estructura.
4. **Consistencia**: Mantiene un patrón consistente para acceder a todos los periféricos.

Entonces, cuando escribes:
```cpp
GPIOA->MODER |= (1 << 10);
```

Estas:
1. Accediendo a la dirección de memoria donde comienza la estructura del periférico GPIOA
2. Navegando al offset donde se encuentra el registro MODER
3. Realizando una operación OR bit a bit en ese registro

Esta técnica de usar punteros a estructuras para representar periféricos es común en la programación de microcontroladores, especialmente en arquitecturas ARM como los STM32, y proporciona una forma limpia y eficiente de interactuar con el hardware.
## GPIO en ESP32: Arquitectura de pines

El ESP32 presenta una arquitectura de GPIO más compleja y flexible:

- **40 pines físicos** (algunas variantes tienen menos pines expuestos)
- **34 pines GPIO** numerados de GPIO0 a GPIO39
- **Restricciones de uso**: Algunos pines tienen funciones especiales durante el arranque o están conectados a periféricos internos
### Registros de control

El ESP32 utiliza un conjunto más extenso de registros agrupados en estructuras:

1. **Registros de configuración**:
    - `GPIO.ENABLE_REG`: Habilita la función GPIO para los pines
    - `GPIO.OUT_REG`, `GPIO.OUT_W1TS_REG`, `GPIO.OUT_W1TC_REG`: Controlan el estado de salida
    - `GPIO.IN_REG`: Lee el estado de los pines
    - `GPIO.PIN[n]`: Contiene configuración específica para cada pin
2. **Funciones específicas**:
    - Los pines tienen registros para configurar:
        - Función de pad (multiplexado)
        - Resistencias pull-up/pull-down
        - Características de driving/slew-rate
        - Interrupciones

### Acceso mediante API

A diferencia del ATmega328P, se recomienda utilizar las APIs proporcionadas en lugar de manipular directamente los registros:

```cpp
// Configurar GPIO18 como salida
gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << GPIO_NUM_18),
    .mode = GPIO_MODE_OUTPUT,
    .pull_up_en = GPIO_PULLUP_DISABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_DISABLE
};
gpio_config(&io_conf);

// Establecer GPIO18 en HIGH
gpio_set_level(GPIO_NUM_18, 1);

// Leer GPIO19
int level = gpio_get_level(GPIO_NUM_19);
```

### Características avanzadas

1. **Matriz de multiplexación**:
    - La mayoría de los pines pueden asignarse a diferentes funciones mediante la matriz de multiplexación
    - Ejemplo: `gpio_matrix_out(25, SIG_PWM0_OUT, false, false)` asigna la señal PWM0 al GPIO25
2. **Sistema de interrupciones**:
    - Admite interrupciones por flanco ascendente, descendente o ambos
    - Interrupciones de nivel alto/bajo
    - ISR (rutina de servicio de interrupción) configurable
3. **Modos especiales**:
    - Entrada con resistencia *pull-up*
    - Entrada con resistencia *pull-down*
    - Salida *open-drain*
    - Modo adicional de matriz digital capacitiva (*touch sensors*)


## **Ejemplos**

### Configuración de LED y botón: **ATmega328P**
 ```cpp
 #include <avr/io.h>

void setup() {
    // LED en PB5 (Arduino pin 13)
    DDRB |= (1 << DDB5);          // Configurar como salida
    
    // Botón en PD2 (Arduino pin 2)
    DDRD &= ~(1 << DDD2);         // Configurar como entrada
    PORTD |= (1 << PORTD2);       // Activar pull-up
}

void loop() {
    if (!(PIND & (1 << PIND2))) { // Si botón presionado (lógica inversa por pull-up)
        PORTB |= (1 << PORTB5);   // Encender LED
    } else {
        PORTB &= ~(1 << PORTB5);  // Apagar LED
    }
}
```

### Configuración de LED y botón: ** **STM32**
```cpp
// Habilitar reloj GPIOA
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

// Configurar PA5 como salida
GPIOA->MODER &= ~(0x3 << (5 * 2));
GPIOA->MODER |= (0x1 << (5 * 2));

// Encender LED usando ODR
GPIOA->ODR |= (1 << 5);

// Encender LED usando BSRR (preferido)
GPIOA->BSRR = (1 << 5);

// Apagar LED
GPIOA->BSRR = (1 << (5 + 16));

// Invertir LED
GPIOA->ODR ^= (1 << 5);
```

### Usando las bibliotecas HAL de STM32 (más habitual)

```cpp
// Inicializar LED en PA5
GPIO_InitTypeDef GPIO_InitStruct = {0};
__HAL_RCC_GPIOA_CLK_ENABLE();
GPIO_InitStruct.Pin = GPIO_PIN_5;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

// Encender LED
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

// Apagar LED
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

// Invertir LED
HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
```
### Configuración de LED y botón: **ESP32**

```cpp
#include "driver/gpio.h"

#define LED_PIN     GPIO_NUM_2
#define BUTTON_PIN  GPIO_NUM_0

void app_main() {
    // Configurar LED
    gpio_config_t led_config = {
        .pin_bit_mask = (1ULL << LED_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&led_config);
    
    // Configurar botón con pull-up
    gpio_config_t button_config = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&button_config);
    
    while (1) {
        if (gpio_get_level(BUTTON_PIN) == 0) {
            gpio_set_level(LED_PIN, 1);
        } else {
            gpio_set_level(LED_PIN, 0);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
```

