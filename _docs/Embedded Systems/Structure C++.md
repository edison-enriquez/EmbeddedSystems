_Una estructura de datos compuesta (struct)_ es una forma de combinar varios campos para representar una estructura de datos compuesta, lo que sienta las bases de la programación orientada a objetos. Por ejemplo, podemos almacenar información sobre un estudiante en una estructura compuesta por su _edad (int), nombre (string), apellido (string) y estándar (int)_ .  
  
_Una estructura_ se puede representar como:
```cpp
struct NewType {
    type1 value1;
    type2 value2;
    .
    .
    .
    typeN valueN;
};
```

Ejemplo:
Crear una estructura, denominada _Student_ , que represente los detalles del estudiante, como se mencionó anteriormente, y almacenar los datos de un estudiante.

```cpp
#include <iostream>
#include <string>

using namespace std;

// Definición de la estructura Student
struct Student {
    int id;
    string nombre;
    int edad;
    float promedio;
};

int main() {
    // Crear y asignar datos a un estudiante
    Student estudiante;

    estudiante.id = 1;
    estudiante.nombre = "Juan Perez";
    estudiante.edad = 20;
    estudiante.promedio = 8.5;

    // Imprimir los datos del estudiante
    cout << "ID del Estudiante: " << estudiante.id << endl;
    cout << "Nombre: " << estudiante.nombre << endl;
    cout << "Edad: " << estudiante.edad << endl;
    cout << "Promedio: " << estudiante.promedio << endl;

    return 0;
}
```
