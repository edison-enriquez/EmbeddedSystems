
- **Clase:**  
    Es un tipo de dato definido por el usuario que encapsula datos (variables miembro) y funciones (métodos). En sistemas embebidos, generalmente se prioriza una implementación eficiente en recursos.
    
- **Objeto:**  
    Es una instancia concreta de una clase, ocupando un espacio específico en memoria.

Una _clase_ define el modelo de un objeto. Para declarar objetos de una clase, usamos la misma sintaxis que para declarar variables de otros tipos básicos. Por ejemplo:

```cpp
Box box1;          // Declares variable box1 of type Box
Box box2;          // Declare variable box2 of type Box
```

Ejemplo para sistemas embebidos:
```cpp
#include <stdint.h>

// Definición formal de una clase para control de LED
class LED {
private:
    volatile uint32_t* puerto;  // Puntero al registro GPIO
    uint8_t pin;                // Pin específico para el LED

public:
    // Constructor con inicialización directa para optimizar recursos
    LED(uint32_t* puertoGPIO, uint8_t pinGPIO)
        : puerto(puertoGPIO), pin(pinGPIO) {}

    void encender() {
        *puerto |= (1 << pin);  // Activar pin (set bit)
    }

    void apagar() {
        *puerto &= ~(1 << pin); // Desactivar pin (clear bit)
    }

    void alternar() {
        *puerto ^= (1 << pin);  // Cambia estado actual del pin (toggle)
    }
};

int main() {
    // Instancia (objeto) de la clase LED con dirección específica (hardware)
    LED ledVerde((uint32_t*)0x40021000, 3);

    ledVerde.encender();  // Enciende LED
    // Delay...
    ledVerde.apagar();    // Apaga LED

    return 0;
}
```

- **Clases:** permiten encapsular el acceso a hardware, ofreciendo métodos claros (`encender()`, `apagar()`, `alternar()`).
- **Objetos:** una instancia (`ledVerde`) accede directamente al hardware, usando direcciones de memoria específicas.

**Clase para Sensor ADC (Convertidor Analógico-Digital):**

```cpp
#include <stdint.h>

class SensorADC {
private:
    volatile uint16_t* registroADC;

public:
    SensorADC(uint16_t* direccionADC) 
        : registroADC(direccionADC) {}

    uint16_t leerValor() {
        return *registroADC; // Lectura directa desde registro ADC
    }
};

int main() {
    SensorADC sensorTemperatura((uint16_t*)0x4001244C);  // Dirección ADC hipotética

    uint16_t valorTemperatura = sensorTemperatura.leerValor();

    // Proceso posterior con valor leído...

    return 0;
}
```

## Diferencias formales entre **clase** y **estructura** en contexto embebido

- **Clase:** por defecto todos sus miembros son privados si no se especifica acceso.
- **Estructura (struct):** miembros públicos por defecto.

```cpp
// Ejemplo formal breve para clarificar diferencias:
class ClaseEjemplo {
    int privado; // privado por defecto
};

struct EstructuraEjemplo {
    int publico; // público por defecto
};
```

- Evitar virtualización o polimorfismo excesivo (genera *overhead* adicional).
- Limitar herencia y virtualización para mantener bajo consumo de memoria y rendimiento adecuado.
- Preferir variables explícitas (como `uint8_t`, `uint16_t`) para optimizar la memoria.