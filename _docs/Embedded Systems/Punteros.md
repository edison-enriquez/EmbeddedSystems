Los punteros son variables especiales que almacenan direcciones de memoria en lugar de valores directos. Son una parte fundamental de la programación en C y C++, especialmente importantes en sistemas embebidos por su eficiencia y capacidad para interactuar directamente con el hardware.
## Conceptos básicos

Un puntero contiene la dirección de memoria donde se almacena otra variable. Usando esta dirección, podemos acceder y modificar el valor almacenado indirectamente.

```cpp
int numero = 42; // Variable normal 
int *puntero; // Declaración de un puntero a entero 
puntero = &numero; // Asignar la dirección de 'numero' al puntero
```

En este ejemplo:
- `numero` es una variable que contiene el valor 42
- `puntero` es una variable que contiene la dirección de memoria de `numero`
- El operador `&` obtiene la dirección de una variable
- El operador `*` (al usar el puntero) accede al valor en esa dirección

## Operaciones con punteros

### Declaración
```cpp
int *p;       // Puntero a entero
char *c;      // Puntero a carácter
float *f;     // Puntero a flotante
```
### Asignación
```cpp
int n = 10;
int *p = &n;  // p contiene la dirección de n
```

### Desreferenciación
```cpp
int n = 10;
int *p = &n;
*p = 20;      // Cambia el valor de n a 20 a través del puntero
```

## Aplicaciones en sistemas embebidos

En sistemas embebidos, los punteros son cruciales por varias razones:

1. **Acceso directo al hardware**: Permiten mapear registros de hardware a variables en el código.
```cpp
// Definir un registro de control para un periférico en una dirección específica
volatile uint32_t *CONTROL_REG = (uint32_t*)0x40021000;

// Modificar directamente el registro
*CONTROL_REG |= 0x01;  // Activar bit 0
```

2. **Optimización de memoria**: Permiten pasar referencias en lugar de copiar variables completas.
```cpp
void procesarDatos(DatosGrandes *datos) {
    // Trabaja con los datos sin copiarlos
}
```
3. **Estructuras de datos dinámicas**: Aunque se usan con precaución en embebidos, permiten crear estructuras como listas enlazadas.
```cpp
struct Nodo {
    int valor;
    struct Nodo *siguiente;
};
```
4. **Callbacks**: Funciones que se pasan como parámetros para ser llamadas posteriormente.
```cpp
typedef void (*CallbackFuncion)(void);

void configurarInterrupcion(CallbackFuncion callback) {
    // Configurar el callback
}
```

## Precauciones en sistemas embebidos

- **Verificación de NULL**: Siempre verificar que un puntero no sea NULL antes de desreferenciarlo.
- **Alineación de memoria**: Algunos procesadores requieren que los accesos estén alineados correctamente.
- **Áreas de memoria protegidas**: Evitar acceder a direcciones de memoria reservadas por el sistema.
- **Gestión cuidadosa**: Los errores con punteros pueden causar comportamientos impredecibles o bloqueos del sistema.

Los punteros son una herramienta poderosa que permite una programación eficiente y flexible en sistemas embebidos, pero requieren un uso cuidadoso para evitar errores difíciles de depurar.

# Punteros con uniones, estructuras y clases en sistemas embebidos

## Punteros con estructuras

Las estructuras permiten agrupar datos relacionados, y los punteros a estructuras son muy comunes en sistemas embebidos para acceder eficientemente a conjuntos de datos.

### Declaración y acceso
```cpp
// Definición de estructura
struct Sensor {
    int id;
    float temperatura;
    uint8_t estado;
};

// Declaración de variable y puntero
Sensor miSensor = {1, 25.5, 0x01};
Sensor *pSensor = &miSensor;

// Acceso a los miembros usando punteros
// Dos formas equivalentes:
(*pSensor).id = 2;       // Usando desreferenciación y operador punto
pSensor->temperatura = 26.8;  // Usando operador flecha (más común)
```

### Uso en sistemas embebidos
```cpp
// Estructura que mapea registros de un periférico
struct ADC_Registers {
    volatile uint32_t CONTROL;
    volatile uint32_t STATUS;
    volatile uint32_t DATA;
    volatile uint32_t CONFIG;
};

// Apuntar a la dirección base del periférico ADC
ADC_Registers *ADC1 = (ADC_Registers*)0x40012000;

// Configurar y leer el ADC
ADC1->CONTROL = 0x01;    // Iniciar conversión
while(!(ADC1->STATUS & 0x01)); // Esperar a que termine
uint32_t resultado = ADC1->DATA;  // Leer valor
```

## Punteros con uniones

Las uniones permiten interpretar los mismos bytes de memoria de diferentes formas, lo cual es útil para acceder a registros de hardware o para manipular datos a nivel de bits.

### Declaración básica
```cpp
union Datos {
    uint32_t valorCompleto;  // 4 bytes
    struct {
        uint8_t byte0;
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3;
    } bytes;
};

Datos dato;
Datos *pDato = &dato;

pDato->valorCompleto = 0x12345678;
uint8_t primerByte = pDato->bytes.byte0;  // Obtiene 0x78 (en sistemas little-endian)
```

### Ejemplo

```cpp
// Unión para manipular un registro de configuración
union ControlRegister {
    uint16_t valor;
    struct {
        uint16_t enable : 1;      // Bit 0
        uint16_t mode : 2;        // Bits 1-2
        uint16_t interrupt : 1;   // Bit 3
        uint16_t reserved : 12;   // Bits 4-15
    } bits;
};

// Apuntar a un registro de control
volatile ControlRegister *CTRL = (ControlRegister*)0x40020100;

// Activar periférico sin modificar otros bits
CTRL->bits.enable = 1;
CTRL->bits.mode = 2;
```

## Punteros con clases (C++)

En C++, además de las estructuras, podemos usar clases que incluyen métodos junto con los datos, proporcionando encapsulación y abstracción.

### Declaración básica
```cpp
class MotorController {
private:
    uint8_t pinPWM;
    uint8_t pinDir;
    uint8_t speed;
    
public:
    MotorController(uint8_t pwm, uint8_t dir) : pinPWM(pwm), pinDir(dir), speed(0) {}
    
    void setSpeed(uint8_t newSpeed) {
        speed = newSpeed;
        // Implementación para controlar el motor
    }
    
    uint8_t getSpeed() const {
        return speed;
    }
};

// Crear objeto y puntero
MotorController motor(9, 8);
MotorController *pMotor = &motor;

// Acceder a métodos a través del puntero
pMotor->setSpeed(128);
uint8_t velocidad = pMotor->getSpeed();
```

### Aplicación 

```cpp
class I2CSensor {
private:
    uint8_t address;
    volatile uint8_t *I2C_DATA_REG;
    volatile uint8_t *I2C_CTRL_REG;
    
public:
    I2CSensor(uint8_t addr) : address(addr) {
        // Mapear registros del hardware
        I2C_DATA_REG = (uint8_t*)0x40005000;
        I2C_CTRL_REG = (uint8_t*)0x40005004;
    }
    
    uint16_t readValue() {
        // Protocolo I2C para leer datos del sensor
        *I2C_CTRL_REG = 0x01;  // Iniciar transacción
        *I2C_DATA_REG = address << 1;  // Dirección del dispositivo
        // ... más código para completar la transacción I2C
        return (*I2C_DATA_REG << 8) | *(I2C_DATA_REG + 1);
    }
};

// Uso
I2CSensor *tempSensor = new I2CSensor(0x48);  // Asignación dinámica (usar con precaución)
uint16_t temperatura = tempSensor->readValue();
delete tempSensor;  // Liberar memoria (importante en sistemas con recursos limitados)
```

## Consideraciones especiales para sistemas embebidos

1. **Memoria estática vs. dinámica**: En sistemas embebidos es preferible usar memoria estática cuando sea posible:
```cpp
// Preferible en sistemas embebidos (asignación estática)
I2CSensor sensor(0x48);
I2CSensor *pSensor = &sensor;

// Evitar cuando sea posible (asignación dinámica)
I2CSensor *pSensor = new I2CSensor(0x48); 
```

2. **Alineación de memoria**: Algunas arquitecturas requieren que los accesos estén alineados:
```cpp
// Asegurar alineación para accesos a 32 bits
struct __attribute__((aligned(4))) AlignedData {
    uint32_t value;
};
```

3. **Volatile**: Usar el calificador `volatile` para variables que pueden cambiar fuera del flujo de control normal:
```cpp
volatile uint32_t *statusRegister = (volatile uint32_t*)0x40001000;
```

4. **Acceso atómico**: Considerar problemas de concurrencia en sistemas con interrupciones:
```cpp
// Proteger acceso a variables compartidas
void disableInterrupts();
pSharedData->value = newValue;
enableInterrupts();
```

Los punteros combinados con estructuras, uniones y clases proporcionan herramientas poderosas para interactuar con el hardware y gestionar datos de manera eficiente en sistemas embebidos.
