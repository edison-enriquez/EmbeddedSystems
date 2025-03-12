Las clases en C++ son tipos definidos por el usuario, declarados con la palabra clave `class`, que contienen datos y funciones. Aunque las clases y las estructuras comparten la misma funcionalidad, existen algunas diferencias básicas. Los miembros de datos de una clase son privados por defecto, mientras que los miembros de una estructura son públicos por defecto. Además de almacenar múltiples datos en un bloque común, también se asignan funciones (conocidas como métodos) para manipularlos y acceder a ellos. Constituyen el elemento fundamental de la Programación Orientada a Objetos.

También incluye especificadores de acceso que restringen el acceso a los elementos miembro. Los más utilizados son los siguientes:

- _público:_ se puede acceder a los miembros públicos (variables, métodos) desde cualquier lugar donde el código sea visible.
- _privado:_ a los miembros privados solo pueden acceder otras funciones miembro y no se puede acceder a ellos fuera de la clase.

La clase se puede representar en forma de

```cpp
class ClassName {
    access_specifier1:
        type1 val1;
        type2 val2;
        ret_type1 method1(type_arg1 arg1, type_arg2 arg2,...)
        ...
    access_specifier2:
        type3 val3;
        type4 val4;
        ret_type2 method2(type_arg3 arg3, type_arg4 arg4,...)
        ...
};
```

Es una práctica común hacer que todas las variables sean privadas y configurarlas/obtenerlas mediante métodos públicos. Por ejemplo:

```cpp
class SampleClass {
    private:
        int val;
    public:
        void set(int a) {
            val = a;
        }
        int get() {
            return val;
        }
};
```

Podemos almacenar los datos de un estudiante en una clase que consta de su _edad (int), nombre (string), apellido (string) y estándar (int)_ .  
  
Debe crear una clase llamada _Estudiante_ que represente los datos del estudiante, como se mencionó anteriormente, y almacenar los datos del estudiante. Cree funciones setter y getter para cada elemento; es decir, la clase debe tener al menos las siguientes funciones:

- _obtener_edad_ , _establecer_edad_
- _obtener_nombre_ , _establecer_nombre_
- _obtener_apellido_ , _establecer_apellido_
- _obtener_estándar_ , _establecer_estándar_
