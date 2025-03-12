El operador punto (`.`), llamado **operador de acceso a miembro**, se utiliza para acceder directamente a miembros individuales (variables o funciones) de un objeto, estructura o unión.

Sintaxis:
```cpp
estructura.miembro
union.miembro
```

Ejemplo:

```cpp
struct Estudiante {
    int id;
    float promedio;
};

int main() {
    Estudiante alumno;
    alumno.id = 5;       // Usando operador "."
    alumno.promedio = 9.3;
    return 0;
}
```

### Aplicación formal:

Acceso directo a miembros de un objeto o instancia específica.
No puede utilizarse con punteros directamente (para punteros se usa `->`).

