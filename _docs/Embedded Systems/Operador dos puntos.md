Este operador se utiliza principalmente en dos contextos relacionados con estructuras, objetos o uniones:

### **Lista de inicialización** (*Constructor initializer list*)

Permite inicializar los miembros de una estructura o clase directamente en el constructor.

**Ejemplo formal:**
```cpp
struct Estudiante {
    int id;
    float promedio;

    // Constructor con lista de inicialización usando ":"
    Estudiante(int id_, float promedio_) : id(id_), promedio(promedio_) {}
};

int main() {
    Estudiante alumno(1, 8.7);
    return 0;
}
```

**Ejemplo formal usando objetos**:

```cpp
#include <iostream>
#include <string>

using namespace std;

class Persona {
private:
    string nombre;
    int edad;

public:
    // Constructor usando lista de inicialización ":"
    Persona(const string& nom, int ed) : nombre(nom), edad(ed) {
        // el cuerpo del constructor puede estar vacío o contener otras operaciones
    }

    void mostrarDatos() {
        cout << "Nombre: " << nombre << ", Edad: " << edad << endl;
    }
};

int main() {
    Persona p("Ana", 30);
    p.mostrarDatos();
    return 0;
}
```
### **Campos de bits** (bit-fields)

Permite especificar el número exacto de bits utilizados por un miembro de una estructura.

**Ejemplo formal:**
```cpp
struct Estado {
    unsigned activo : 1;   // Usa solo 1 bit
    unsigned valor : 4;    // Usa 4 bits
};

int main() {
    Estado estado;
    estado.activo = 1;
    estado.valor = 9;
    return 0;
}
```

### Aplicación formal:

- En constructores, inicializa miembros de forma eficiente antes del cuerpo del constructor.
- En campos de bits, controla explícitamente el uso del espacio en memoria para eficiencia

