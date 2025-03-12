El operador `::` es conocido como el **operador de resolución de ámbito**. Permite acceder a miembros estáticos, variables globales o funciones definidas dentro de espacios de nombres (`namespace`), clases, estructuras o uniones desde fuera de su ámbito inmediato.

### Sintaxis:

```cpp
Clase::miembro_estatico
Namespace::funcion()
Struct::variable_estatica
```

### Ejemplo:

```cpp
struct Estudiante {
    static int totalEstudiantes;
};

// Definición del miembro estático fuera de la estructura
int Estudiante::totalEstudiantes = 0;

int main() {
    Estudiante::totalEstudiantes = 5; // Acceso a miembro estático
    return 0;
}

```
### Aplicación formal:

- Acceso a miembros estáticos o funciones de estructuras o clases.
- Resolución explícita para miembros declarados en espacios de nombres.
- Acceso a funciones o variables globales cuando existe ambigüedad.