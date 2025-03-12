
## Herencia (Inheritance)

La **herencia** es el mecanismo mediante el cual una clase (denominada **clase derivada o hija**) puede adquirir propiedades (atributos) y comportamientos (métodos) de otra clase ya existente (llamada **clase base o padre**).

Sintaxis Formal:
```cpp
class ClaseDerivada : public ClaseBase {
  // definición de métodos y atributos adicionales
};

```

## Clase Base (*Base Class*)

Es la clase original desde la cual otras clases (llamadas derivadas) heredan atributos y métodos.

## Clase Derivada (*Derived Class*)

Es una clase nueva que extiende la funcionalidad o características de la clase base, agregando métodos o atributos adicionales o redefiniendo métodos ya existentes.

**Ejemplo**
```cpp
#include <iostream>

// Clase Base abstracta
class Dispositivo {
public:
    virtual void activar() = 0;  // Método abstracto (virtual puro)
    virtual void desactivar() = 0; 

    virtual ~Dispositivo() {}    // Destructor virtual formal
};

// Clase derivada que hereda formalmente de Dispositivo
class LED : public Dispositivo {
public:
    void activar() override {
        // Código específico para activar LED
    }

    void desactivar() override {
        // Código formal para apagar LED
    }
};

// Otra clase derivada
class Motor : public Dispositivo {
public:
    void activar() override {
        // código para activar motor
    }

    void desactivar() override {
        // código para desactivar motor
    }
};

int main() {
    Dispositivo* dispositivo = new LED();
    dispositivo->activar();    // activa el LED
    dispositivo->desactivar(); // desactiva el LED

    delete dispositivo;        // libera memoria correctamente gracias al destructor virtual
    return 0;
}

```

- `Dispositivo` es una clase abstracta que define la interfaz formal de los dispositivos.
- `LED` y `Motor` son clases derivadas que implementan formalmente esa interfaz.
- Permite la creación de un código generalizado y reutilizable.

## Tipos de Herencia en C++

| Tipo                    | Ejemplo formal                       | Descripción formal                                                                     |
| ----------------------- | ------------------------------------ | -------------------------------------------------------------------------------------- |
| Pública (`public`)      | `class Derivada : public Base { };`  | Miembros públicos y protegidos mantienen su visibilidad original en la clase derivada. |
| Protegida (`protected`) | `class Derivada : protected Base {}` | Miembros públicos/protegidos se vuelven protegidos.                                    |
| Privada (`private`)     | `class Derivada : private Base`      | Miembros públicos y protegidos de la base se vuelven privados en la derivada           |
La más común en sistemas embebidos es la herencia pública (`public`).

Ejemplo:  
```cpp
#include <stdint.h>

// Clase base formal para puerto GPIO genérico
class GPIO {
protected:
    volatile uint32_t *puerto;
    uint8_t pin;

public:
    GPIO(uint32_t* dir_puerto, uint8_t num_pin)
        : puerto(dir_puerto), pin(num_pin) {}

    virtual void encender() {
        *puerto |= (1 << pin);
    }

    virtual void apagar() {
        *puerto &= ~(1 << pin);
    }
};

// Clase derivada
class LED : public GPIO {
public:
    LED(uint32_t* dir_puerto, uint8_t num_pin)
        : GPIO(dir_puerto, num_pin) {}

    void parpadear() {
        encender();
        // retardo aquí (omitido por brevedad)
        apagar();
    }
};

int main() {
    LED ledRojo((uint32_t*)0x50000000, 2);
    ledRojo.encender();
    ledRojo.apagar();

    return 0;
}
```

- `LED` hereda funcionalidad básica de GPIO.
- Lista de inicialización formal usando `:` para inicializar atributos.

## Relaciones entre clases

|Tipo formal de relación|Definición formal|Ejemplo formal (contexto embebido)|
|---|---|---|
|**Herencia**|`Es-un`|LED `es-un` Dispositivo|
|**Composición**|`Tiene-un`|Motor `tiene-un` ControladorPWM|
|**Agregación**|`Usa-un`|Sistema `usa-un` SensorTemperatura|
- La **herencia** formaliza jerarquía y comportamiento.
- **Composición y agregación** se usan frecuentemente en sistemas embebidos para representar relaciones entre componentes físicos.

## Uso práctico

Las clases derivadas permiten tener una estructura modular, reutilizable y eficiente.  
Por ejemplo:

- Controladores para distintos sensores.
- Manejo de múltiples interfaces de comunicación (UART, SPI, I²C).
- Gestión de distintos tipos de dispositivos (LEDs, Motores, Relés).
## Polimorfismo
Permite definir diferentes implementaciones de métodos con el mismo nombre en diferentes clases relacionadas por herencia, facilitando comportamiento dinámico según el objeto.

```cpp
#include <iostream>

class Dispositivo {
public:
    virtual void activar() = 0; // método virtual puro
};

class LED : public Dispositivo {
public:
    void activar() override {
        std::cout << "LED encendido\n";
    }
};

class Motor : public Dispositivo {
public:
    void activar() override {
        std::cout << "Motor activado\n";
    }
};

int main() {
    Dispositivo* dispositivo1 = new LED();
    Dispositivo* dispositivo2 = new LED();

    dispositivo1->activar();  // LED encendido
    delete dispositivo;

    return 0;
}
```

- Se declara un método `activar()` virtual puro (`= 0`), convirtiendo `Dispositivo` en clase abstracta.
- Cada dispositivo implementa su propio comportamiento del método `activar()`.

### **Clases Abstractas y Virtuales** :

- Una clase abstracta es aquella que contiene al menos un método virtual puro.
- No puede instanciar objetos directamente, solo heredarse.

#### ¿Qué es `virtual` en C++?

**`virtual`**  Es una Palabra reservada usada para permitir la redefinición de métodos en clases derivadas, facilitando el polimorfismo dinámico.