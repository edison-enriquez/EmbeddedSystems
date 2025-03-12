Un **patrón de diseño (Design Pattern)** es una solución general, reutilizable y comprobada a problemas comunes en el diseño de software orientado a objetos.  
Permiten crear sistemas eficientes, mantenibles y escalables.

## **Clasificación de los Patrones de Diseño:**

Los patrones de diseño se clasifican formalmente en tres grandes categorías:

| Categoría          | Objetivo principal formal                        |
| ------------------ | ------------------------------------------------ |
| **Creacionales**   | Facilitar la creación de objetos eficientemente. |
| **Estructurales**  | Simplificar composición entre objetos.           |
| **Comportamiento** | Simplificar la comunicación entre objetos.       |
## **1. Patrones de Creación (Creational Patterns)**

Permiten crear objetos de forma eficiente y controlada.

### **Ejemplo formal:** Patrón **Singleton**

Garantiza que exista **una única instancia** de una clase en todo el sistema.

#### Código C++ (Embebido):

```cpp
class ConfiguracionSistema {
private:
    static Configuracion instancia; // única instancia (static)

    Configuracion() {}              // Constructor privado

public:
    static Configuracion& obtenerInstancia() {
        static Configuracion instancia;  // Única instancia garantizada
        return instancia;
    }

    void establecerParametro(int valor) {
        // Código de configuración
    }
};

int main() {
    ConfiguracionSistema::getInstancia().establecerParametro(10);
    return 0;
}

```


- Configuraciones globales.
- Acceso único a periféricos críticos.

## **2. Patrones de Estructura (Structural Patterns)**

## Patrón **Adapter (Adaptador)**  
Permite que interfaces incompatibles trabajen juntas mediante un intermediario formal.
```cpp
// Interfaz formal para Sensor
class ISensor {
public:
    virtual int obtenerDatos() = 0;
};

// Sensor específico que tiene una interfaz distinta
class SensorSPI {
public:
    int obtenerLecturaSPI() { return 200; }
};

// Adaptador formal
class AdaptadorSensor : public SensorSPI, public Sensor {
public:
    int leer() override {
        return obtenerLecturaSPI();
    }
};

int main() {
    AdaptadorSensor sensor;
    int valor = sensor.leer();
    return 0;
}
```

- Adaptar dispositivos con interfaces diferentes.
- Integrar librerías externas sin modificar código existente.

## Patrón **Fachada (Facade)**

El patrón **Fachada** proporciona una interfaz simple y unificada que facilita el acceso a un conjunto complejo de subsistemas o componentes, simplificando la interacción del cliente con el sistema.

En esencia, **oculta la complejidad interna del sistema mediante una sola clase intermedia**.

### **Estructura formal del patrón Fachada:**

- **Cliente:** utiliza la fachada para interactuar con el sistema.
- **Fachada:** clase que ofrece una interfaz sencilla y clara.
- **Subsistemas:** clases internas más complejas que la fachada maneja.

```
[Cliente] ↔ [Fachada] → SubsistemaA, SubsistemaB, SubsistemaC...
```
#### Escenario:
- Se tiene un sistema embebido con múltiples componentes (ADC, PWM, GPIO).
- El cliente desea iniciar y detener la medición de un sensor mediante una interfaz simple.

```cpp
#include <stdint.h>

// Subsistemas complejos (formalmente ocultos):

class ADC {
public:
    void iniciar() { /* Inicializar ADC */ }
    uint16_t leer() { return 123; }
};

class PWM {
public:
    void iniciar() { /* Inicializar PWM */ }
    void establecerDuty(uint8_t duty) { /* Establece ciclo de trabajo */ }
};

class GPIO {
public:
    void configurarSalida() { /* Configurar pin como salida */ }
    void encender() { /* Encender pin GPIO */ }
    void apagar() { /* Apagar pin GPIO */ }
};

// Fachada formal simplificada:
class ControlSensor {
private:
    ADC adc;
    PWM pwm;
    GPIO gpio;

public:
    void iniciarMedicion() {
        gpio.configurarSalida();
        gpio.encender();
        adc.iniciar();
        pwm.iniciar();
        pwm.establecerDuty(50);
    }

    uint16_t obtenerLectura() {
        return adc.leer();
    }

    void detenerMedicion() {
        gpio.apagar();
    }
};

// Cliente (main), usando fachada para interactuar fácilmente con hardware:
int main() {
    ControlSensor sensor;

    sensor.iniciarMedicion();  
    uint16_t valor = sensor.obtenerLectura();
    sensor.detenerMedicion();

    return 0;
}

```

- **Fachada:** La clase `ControlSensor` simplifica la interfaz compleja.
- **Subsistemas:** ADC, PWM y GPIO son controlados internamente por la fachada.

#### **Uso típico formal del patrón Fachada en embebidos:**
- **Inicialización de periféricos:**  Simplificar secuencias complejas de configuración de hardware.    
- **Manejo de sensores:**  Proveer acceso sencillo a múltiples sensores complejos.    
- **Interfaces de usuario:**   Acceso simplificado a módulos complejos como pantallas, comunicaciones o almacenamiento.
## **3. Patrones de Comportamiento (Behavioral Patterns)**

Definen cómo interactúan formalmente los objetos.

### **Ejemplo formal:** Patrón **Observer (Observador)**

Un objeto (**sujeto**) notifica automáticamente cambios a otros objetos (**observadores**).

```cpp
#include <vector>

// Observador formal
class Observador {
public:
    virtual void actualizar(int estado) = 0;
};

// Sujeto formal (ej: Sensor de temperatura)
class Sensor {
    std::vector<Observador*> observadores;
    int temperatura;

public:
    void agregarObservador(Observador* obs) {
        observadores.push_back(obs);
    }

    void setTemperatura(int valor) {
        temperatura = valor;
        notificar();  // notificación automática
    }

    void notificar() {
        for(auto& obs : observadores)
            obs->actualizar(temperatura);
    }

private:
    std::vector<Observador*> observadores;
};

// Observador concreto
class Pantalla : public Observador {
public:
    void actualizar(int temperatura) override {
        // Mostrar temperatura en pantalla
    }
};

int main() {
    Sensor temperatura;
    Pantalla pantallaLCD;

    temperatura.agregarObservador(&pantalla);
    temperatura.setTemperatura(28);

    return 0;
}

```

- Monitoreo de sensores.
- Control automático de estados del sistema.

## Patrón **State (Estado)**:

El patrón **State** permite que un objeto modifique su comportamiento interno al cambiar su estado interno. Desde fuera, el objeto parece cambiar de clase según su estado.

Formalmente, este patrón encapsula diferentes comportamientos en clases separadas (**Estados**), permitiendo al objeto cambiar dinámicamente de comportamiento según su estado actual.

### **Objetivo Formal en Embebidos:**

- Simplificar el manejo de máquinas de estados, algo muy común en sistemas embebidos.
- Facilita la claridad y escalabilidad del código relacionado con múltiples estados operativos.

### **Componentes Formales del patrón State:**

- **Contexto** (Clase que tiene el estado actual)
- **Estado abstracto** (Define interfaz formal común para los estados concretos)
- **Estados concretos** (Implementan comportamientos específicos

```
[Contexto]  ↔ (Estado abstracto) ← Estados concretos (EstadoA, EstadoB, EstadoC...)

```
### Ejemplo

Un dispositivo embebido que maneja tres estados:

- **Standby**
- **Operando**
- **Error**

El comportamiento cambia según su estado actual.

```cpp
#include <iostream>

// Estado abstracto formal
class Estado {
public:
    virtual void manejar() = 0;
};

// Contexto formal
class SistemaEmbebido {
private:
    Estado* estadoActual;

public:
    void cambiarEstado(Estado* nuevoEstado) {
        estadoActual = nuevoEstado;
    }

    void ejecutar() {
        estadoActual->accion(*this);
    }

    void cambiarEstado(Estado* nuevoEstado) {
        estadoActual = nuevoEstado;
    }

private:
    Estado* estadoActual;
};

// Estados específicos (implementaciones formales)
class EstadoStandby : public Estado {
public:
    void accion(Sistema& sistema) override {
        // Implementación formal del estado Standby
    }
};

class EstadoOperando : public Estado {
public:
    void accion(Sistema& contexto) override {
        // Operación normal del sistema
    }
};

class EstadoError : public Estado {
public:
    void accion(Sistema& ctx) override {
        // manejo de errores
    }
};

int main() {
    Sistema sistema;

    EstadoStandby standby;
    EstadoOperando operando;
    EstadoError error;

    sistema.cambiarEstado(&standby);
    sistema.ejecutar();  // Estado standby

    sistema.cambiarEstado(&operando);
    sistema.ejecutar();  // Estado operando

    sistema.cambiarEstado(&error);
    sistema.ejecutar();  // Estado error

    return 0;
}
```

#### **Casos prácticos típicos del patrón State en embebidos:**

- Sistemas de control (máquinas de estados para sensores).
- Gestión de modos operativos (normal, bajo consumo, error).
- Máquinas de estado para comunicaciones UART, SPI o I²C.
- Implementación clara de algoritmos complejos (protocolos de comunicación, máquinas de estado finitas).

### Máquina de Estados con patrón State

Control de un **Sistema de Alarma Embebido** con tres estados operativos:

- **Desactivado** (Standby)
- **Activado** (En funcionamiento normal)
- **Alerta** (Detecta intrusión o condición de error)

#### **Estructura del Ejemplo:**

- **Contexto:** `SistemaAlarma`
- **Estado abstracto:** `EstadoAlarma`
- **Estados concretos:** `EstadoDesactivado`, `EstadoActivado`, `EstadoError

```cpp
#include <iostream>

// Declaración adelantada
class SistemaAlarma;

// Estado abstracto formal
class EstadoAlarma {
public:
    virtual void manejar(SistemaAlarma &contexto) = 0;
    virtual const char* nombreEstado() = 0;
};

// Contexto formal: máquina de estados
class SistemaAlarma {
private:
    EstadoAlarma* estadoActual;

public:
    SistemaAlarma(EstadoAlarma* inicial) : estadoActual(inicial) {}

    void cambiarEstado(EstadoAlarma* nuevoEstado) {
        estadoActual = nuevoEstado;
    }

    void ejecutar() {
        estadoActual->accion(*this);
    }
};

// Estado abstracto formal
class EstadoAlarma {
public:
    virtual void accion(SistemaAlarma &sistema) = 0;
};

// Estados específicos formales:

// Estado Desactivado
class EstadoDesactivado : public EstadoAlarma {
public:
    void accion(SistemaAlarma &contexto) override {
        std::cout << "[Estado] Alarma Desactivada\n";
        // Lógica para cambiar estado, ejemplo:
        // contexto.cambiarEstado(&activado);
    }
};

// Estado Activado
class EstadoActivado : public EstadoAlarma {
public:
    void accion(SistemaAlarma& contexto) override {
        std::cout << "[Estado] Alarma Activada\n";
        // Si detecta algo anormal, cambiar a alerta:
        // contexto.cambiarEstado(&error);
    }
};

// Estado Error (alarma activada)
class EstadoError : public EstadoAlarma {
public:
    void accion(SistemaAlarma& contexto) override {
        std::cout << "[Estado] Error o Intrusión detectada!\n";
        // acciones correctivas o reinicio del sistema
    }
};

int main() {
    // Creación formal de estados
    EstadoDesactivado desactivado;
    EstadoActivado activado;
    EstadoError error;

    // Inicialización formal del sistema con estado inicial
    SistemaAlarma alarma(&desactivado);

    // Ejecución formal (máquina de estados)
    alarma.ejecutar(); // Alarma desactivada

    // Cambio a estado activado
    alarma.cambiarEstado(&activado);
    alarma.ejecutar();  // Estado activado

    // Simula error o intrusión
    alarma.cambiarEstado(&error);
    alarma.ejecutar();  // Estado de error/intrusión

    return 0;
}
```

- **Contexto (`SistemaAlarma`):** administra el estado actual y transiciones entre estados.
- **Estados concretos:** implementan formalmente la lógica específica según el comportamiento del sistema en cada situación.
- Cambio formal de estado: a través de `cambiarEstado()` en la clase contexto.

## **Ventajas del uso de patrones en sistemas embebidos:**

- **Mayor mantenibilidad:**  Simplifican modificaciones futuras.    
- **Reutilización de código:**  Evitan duplicidad en código repetitivo.    
- **Mejor escalabilidad:**  Facilitan integración de nuevo hardware o cambios futuros.
- **Optimización de recursos:**  Ayudan a controlar y optimizar el uso de memoria, CPU y periféricos.

