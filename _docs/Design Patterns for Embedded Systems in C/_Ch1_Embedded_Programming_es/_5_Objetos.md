# Orientado a Objetos o estructurado: usted elige

La programación estructurada es una forma disciplinada de desarrollo de software que enfatiza dos aspectos separados y distintos. Por un lado, las funciones o procedimientos forman la base de la programación conductual: un procedimiento es una colección de acciones primitivas con un único punto de entrada que logra un objetivo conductual coherente; una función es simplemente un procedimiento que devuelve un valor. Los procedimientos se pueden dividir en árboles de llamadas cuando un procedimiento invoca a otro, lo que permite la descomposición algorítmica.
Los procedimientos generalmente se invocan de forma sincrónica (es decir, se llaman), pero al agregar medios adicionales, también se pueden invocar invocaciones asincrónicas.

Un objeto es una instancia de una clase. Esto hace que un objeto sea equivalente, pero más poderoso, a una variable en un lenguaje estructurado porque el objeto proporciona tanto los valores contenidos en sus atributos como las operaciones que los manipulan. Un lenguaje estructurado es un lenguaje que soporta directamente la programación estructurada. En el contexto de este libro, C es claramente un lenguaje estructurado. C es, con diferencia, el lenguaje más frecuente para la creación de sistemas integrados y C es un lenguaje inherentemente "estructurado". Tiene todas las características: funciones, variables, etc. Sin embargo, surge una pregunta interesante: ¿se puede realizar programación orientada a objetos en un lenguaje estructurado, como C? Y aunque se pueda hacer, ¿debería hacerse?

Recuerdo una discusión similar cuando los lenguajes de programación más comunes eran los lenguajes ensambladores. ¿Era posible escribir programas estructurados en código ensamblador? Después de todo, los lenguajes ensambladores no proporcionan características de lenguaje estructurado intrínsecamente. Da la casualidad de que la respuesta es claramente: "¡Sí!" No sólo es posible, sino también rentable, escribir programas estructurados en lenguaje ensamblador. Requiere cierta disciplina por parte del programador y decisiones sobre la asignación de instrucciones en lenguaje ensamblador a conceptos estructurados (como pasar parámetros en la pila), pero es bastante fácil de hacer.

Lo mismo ocurre con la programación orientada a objetos en lenguajes estructurados como C. En este libro, adoptaremos una perspectiva de programación principalmente basada en objetos (orientada a objetos sin subclases) porque creo que hacerlo tiene beneficios. Sin embargo, la creación de programas basados en objetos u orientados a objetos en C es bastante sencilla. Analicemos brevemente los aspectos importantes de la programación orientada a objetos y cómo implementar esos conceptos en C.

## Clases

Una clase en realidad no es más que una estructura C, pero lo que tiene de especial es que contiene dos tipos diferentes de características: datos (atributos) y de comportamiento (operaciones).
La forma más sencilla de implementar clases es simplemente utilizar el archivo como límite de encapsulación; Las variables y funciones públicas se pueden hacer visibles en el archivo de encabezado, mientras que el archivo de implementación contiene los cuerpos de las funciones y las variables y funciones privadas. Se pueden vincular varios archivos con dependencias de «`Usage`» para admitir el árbol de llamadas, como en la Figura 1-1.
En este caso, una “clase” se representa como un par de archivos y su implementación utiliza algunas características (variables o funciones) de la clase Display (archivo), en este caso, la función `displayMsg()`.
Un enfoque algo más flexible utiliza estructuras dentro de los archivos para representar las clases. Las operaciones de la clase se definen como funciones ubicadas dentro del mismo archivo que la estructura. Para asegurarnos de que la función tenga acceso a los datos correctos del objeto, debemos pasar un puntero `me`.

Esto nos permite tener múltiples instancias (objetos) de la misma clase y asegurarnos de que las funciones miembro funcionen en las copias correctas de los datos. Además, las clases están dotadas de operaciones "especiales". Un constructor crea un objeto de la clase. Un inicializador (opcionalmente) inicializa el objeto y sus atributos. Un destructor destruye la clase y libera la memoria utilizada.

Considere una clase simple Sensor con elementos de datos valor, `updateFrequency` y `filterFrequency` y operaciones, `getValue()`, `setValue(v: int)`, `setUpdateFreq (r:int)`, `getUpdateFreq()`, `setFilterFreq(ff: int)` y `getFilterFreq()` . El archivo de encabezado se parecería al Listado de Código 1.

```c
/***********************
Códigos 1-1: Archivo de encabezado del sensor
***************************/
#ifndef Sensor_H  
#define Sensor_H  
/*## class Sensor */  
typedef struct Sensor Sensor;
struct Sensor {  
	int filterFrequency;  
	int updateFrequency;  
	int value;  
};  
int Sensor_getFilterFrequency(const Sensor* const me);  
void Sensor_setFilterFrequency(Sensor* const me, int p_filterFrequency);  
int Sensor_getUpdateFrequency(const Sensor* const me);  
void Sensor_setUpdateFrequency(Sensor* const me, int p_updateFrequency);  
int Sensor_getValue(const Sensor* const me);  
Sensor * Sensor_Create(void);  
void Sensor_Destroy(Sensor* const me);
```
El archivo de implemento asociado se muestra en el Código 2

```c
/**********************************
Código 2: Archivo de implementación del sensor
***********************************/

#include "Sensor.h"  
void Sensor_Init(Sensor* const me){}  
void Sensor_Cleanup(Sensor* const me) {}  
int Sensor_getFilterFrequency(const Sensor* const me) 
{  
	return me->filterFrequency;  
}  
void Sensor_setFilterFrequency(Sensor* const me, int p_filterFrequency) 
{  
	me->filterFrequency = p_filterFrequency;  
}  
int Sensor_getUpdateFrequency(const Sensor* const me) 
{  
	return me->updateFrequency;  
}  
void Sensor_setUpdateFrequency(Sensor* const me, int p_updateFrequency) 
{  
	me->updateFrequency = p_updateFrequency;  
}  
int Sensor_getValue(const Sensor* const me) 
{  
	return me->value;  
}  
Sensor * Sensor_Create(void) 
{  
	Sensor* me = (Sensor *) malloc(sizeof(Sensor));
	if(me!=NULL) Sensor_Init(me);  
	return me;  
}  
void Sensor_Destroy(Sensor* const me)
{  
	if(me!=NULL) Sensor_Cleanup(me); 
	free(me);  
}
```

En este caso, el archivo sirve como límite de encapsulación y, estilísticamente, dos archivos (un archivo de encabezado .h y un archivo de implementación .c) agrupan los elementos dentro de una sola clase. Este enfoque admite muy bien la programación basada en objetos, pero no implementa funciones virtuales de una manera que pueda anularse fácilmente en subclases.
Un enfoque alternativo que admite la programación orientada a objetos es incrustar punteros de función dentro de la propia estructura. 

## Objetos
Los objetos son instancias de clases, de la misma manera que una variable específica x (de tipo int) es una instancia de su tipo (int). El mismo conjunto de operadores (como los operadores aritméticos) se aplica a todas las variables de ese tipo, pero los valores específicos de una instancia difieren de los de otra instancia (digamos, y).

En la programación estándar en C, todavía se pueden incrustar algoritmos complejos en las clases, pero es común que estas clases sean singletons, lo que significa que hay exactamente una instancia de la clase en la aplicación. Una clase de Impresora singleton, por ejemplo, puede tener variables como impresora actual y operaciones como imprimir(), pero la aplicación tendría una sola instancia. Todavía existen beneficios al encapsular los datos utilizados por una clase con las operaciones que actúan sobre esos datos, incluso si solo hay una instancia ejecutándose. En otros casos, las clases normalmente más centradas en datos (a diferencia de las centradas en algoritmos o servicios) tendrán múltiples instancias.

Para crear una instancia de una clase, simplemente cree una instancia de la estructura. Considere un posible main() que crea y utiliza dos instancias de la clase Sensor anterior, que se muestra en el Listado de Código 3:

```c
/*****************************
Código 3: Sensor main()
*****************************/

#include "Sensor.h"  
#include <stdlib.h>  
#include <stdio.h>  
int main(int argc, char* argv[]) {  
	Sensor * p_Sensor0, * p_Sensor1;  
	p_Sensor0 = Sensor_Create();  
	p_Sensor1 = Sensor_Create();  
	/* do stuff with the sensors ere */  
	p_Sensor0->value = 99;  
	p_Sensor1->value = -1;  
	printf("The current value from Sensor 0 is %d\n",  
	Sensor_getValue(p_Sensor0));  
	printf("The current value from Sensor 1 is %d\n",  
	Sensor_getValue(p_Sensor1));  
	/* done with sensors */  
	Sensor_Destroy(p_Sensor0);  
	Sensor_Destroy(p_Sensor1);  
	return 0;  
}
```

### 1.2.3 Polimorfismo y funciones virtuales

El polimorfismo es una característica valiosa de los lenguajes orientados a objetos. Permite que el mismo nombre de función represente una función en un contexto y otra función en un contexto diferente. En la práctica, esto significa que cuando cambia el contexto estático o dinámico de un elemento, se puede llamar a la operación adecuada.

Por supuesto, la forma estándar de hacer esto en C es utilizar declaraciones condicionales como if o switch. El problema con el enfoque estándar es que rápidamente se vuelve difícil de manejar cuando hay muchos contextos diferentes disponibles. Además, el enfoque requiere que se conozcan todos los contextos posibles cuando se escribe la función original, o al menos la función debe modificarse para permitir un nuevo contexto. Con funciones polimórficas, no se requiere presciencia. Cuando se descubre el nuevo contexto, la función polimórfica se puede crear y agregar sin requerir cambios en la función original.

Considere un sensor en el que la interfaz real puede diferir. La función `acquireValue` en un contexto puede requerir acceder a un sensor asignado en memoria, esperar un momento y luego leer una dirección diferente para adquirir el valor. Un contexto diferente puede utilizar un sensor con mapa de puerto. Definitivamente preferiríamos que el cliente del sensor no supiera cómo funciona la interfaz del sensor; requerir dicho conocimiento hace que la aplicación sea mucho más frágil y difícil de mantener. Con el enfoque estándar de C, escribiríamos un código similar al Listado de Código 4 con los atributos `whatKindOfInterface` agregados a la estructura Sensor.

```c
/***************************************
Código 4: Polimorfismo de la manera más difícil
****************************************/

int acquireValue(Sensor *me) {  
	int *r, *w; /* read and write addresses */  
	int j;  
	switch(me->whatKindOfInterface) {  
		case MEMORYMAPPED:  
			w = (int*)WRITEADDR; /* address to write to sensor */  
			*w = WRITEMASK; /* sensor command to force a read */  
			for (j=0;j<100;j++) { /* wait loop */ };  
			r = (int *)READADDR; /* address of returned value */  
			me->value = *r;  
			break;  
		case PORTMAPPED:  
			me->value = inp(SENSORPORT);  
			/* inp() is a compiler-specific port function */  
			break;  
	}; /* end switch */  
	return me->value;  
};
```

## Subclases

La subclases (conocida como generalización en el Lenguaje Unificado de Modelado [UML] o como herencia) es una forma de representar clases que son un "tipo especializado de" otra clase. La regla básica es que la clase especializada hereda las características de la clase más general. Es decir, todas las características de la clase más general (también conocida como clase base o padre) son también características de la clase especializada (también conocida como clase derivada o hija), pero a esta última se le permite especializarse y extenderse. la clase más general.

Una de las ventajas clave de la subclasificación es la capacidad de reutilizar el diseño y el código. Si diseño una clase para un contexto específico y quiero reutilizarla más adelante en un contexto diferente, puedo simplemente diseñar y codificar las especializaciones y extensiones sin tocar la clase base. Además, en uso, puedo escribir algoritmos que manipulen una instancia de un tipo, sin importar qué subclase pueda ser, cuando sea apropiado y modificar el comportamiento para que sea semánticamente correcto con la subclase cuando sea necesario.

Por "especializarse" me refiero a que la clase especializada puede redefinir las operaciones proporcionadas por la clase base. Debido a que una subclase es una forma especializada de una clase base, cualquier operación que tenga sentido para una instancia de la clase base también debería tener sentido con una instancia de la clase derivada. Sin embargo, sucede a menudo que la implementación de esa operación debe ser ligeramente diferente. Por ejemplo, si escribo el código para poner en cola datos de un sensor, es probable que tenga operaciones como `insert(int value)`, `int remove()`, `int getSize()`, etc. Si creo un tipo de cola especializada que pueda almacenar grandes cantidades de datos en un dispositivo de almacenamiento masivo, como una unidad flash, esas operaciones seguirán teniendo sentido, pero su implementación será diferente. Nótese que la especialización se refiere exclusivamente a cambiar la implementación de operaciones y en absoluto a la redefinición de datos.

La especialización se puede realizar fácilmente con el enfoque de declaración de cambio de caso mencionado en la sección anterior, pero es mucho más versátil si en su lugar se utilizan punteros de función. Luego, el diseñador puede simplemente escribir las funciones especializadas y crear un nuevo constructor que apunte a las nuevas funciones en lugar de a las antiguas. Es decir, las subclases pueden anular las operaciones insertando punteros a diferentes funciones que proporcionan comportamientos especializados. La desventaja es que los punteros de función son un poco complicados y son la principal causa de defectos inducidos por los programadores en los programas C.

Por "extender" me refiero a que la clase secundaria tendrá nuevas características, como nuevos atributos u operaciones. En el caso de la cola de datos, esto significa que puedo agregar nuevos atributos como el nombre del archivo de datos utilizado para almacenar datos en caché en la unidad flash, así como nuevas operaciones como las operaciones de descarga() y carga() para escribir. sacar el búfer en memoria para flashear o leer datos de la unidad flash en el búfer en memoria, respectivamente. El diagrama de clases UML de la Figura 1-2 muestra las clases Queue y CachedQueue. Para simplificar el problema, asumimos que la cola nunca se usa incorrectamente (por lo que no tenemos que manejar condiciones de desbordamiento y subdesbordamiento) y queremos almacenar un máximo de 100 enteros en la cola11.
CachedQueue es conceptualmente sencillo. Si hay espacio en el búfer de inserción, inserte los datos como en la cola normal. Sin embargo, si llena el búfer interno, la operación insert() llamará a flush() para escribir el búfer de inserción en el disco y luego el búfer interno se restablecerá. Para eliminar datos, es sólo un poco más complicado. Si el búfer interno está vacío, entonces remove() llama a la función load() para leer los datos más antiguos del disco.

___
> __Leyendo el diagrama de clases UML__
	El diagrama de clases que se muestra tiene varias características clásicas de los diagramas de clases UML. Los cuadros representan las clases mientras que las líneas representan las relaciones entre las clases. El cuadro de clase se divide (opcionalmente) en tres segmentos. El segmento superior contiene el nombre de la clase.
	El segmento del medio enumera los atributos (miembros de datos), junto con sus tipos. El segmento inferior muestra las operaciones dentro de la clase.
	En la figura se muestran dos relaciones diferentes. La línea con la punta de flecha cerrada es la relación de generalización; la línea apunta a la clase más básica. La otra línea se conoce como composición. La composición es una relación que implica una fuerte propiedad y la responsabilidad de la creación y destrucción de la instancia de la clase en el otro extremo de la relación. La punta de flecha abierta representa la navegación (en este caso, el propietario tiene un puntero hacia la pieza, pero no al revés). El nombre cerca de la punta de flecha es el nombre del puntero dentro de la clase CachedQueue. El número cerca de la punta de la flecha es la multiplicidad: la cantidad de instancias necesarias para desempeñar el rol (en este caso, se necesita una sola instancia).


Ciertamente hay más de una forma de implementar subclases en C. En el enfoque utilizado aquí, para manejar la especialización, emplearemos los punteros de función miembro descritos en la sección anterior. Para ampliar, simplemente incrustaremos la clase base como una estructura dentro de la clase secundaria.

Por ejemplo, veamos el código del ejemplo de cola de la Figura 1-2. El Listado de Código 5 es el archivo de encabezado de la clase Queue, cuya estructura debería ser más o menos la esperada.

```c
/*****************************
Code 5: Queue Header
*****************************/

#ifndef QUEUE_H_  
#define QUEUE_H_  
#define QUEUE_SIZE 10  
/* class Queue */  
typedef struct Queue Queue;  
struct Queue {  

	int buffer[QUEUE_SIZE];  <br>int head;|/* where the data things are */	
	int size;  
	int tail;  
	int (*isFull)(Queue* const me);  
	int (*isEmpty)(Queue* const me);  
	int (*getSize)(Queue* const me);  
	void (*insert)(Queue* const me, int k);  
	int (*remove)(Queue* const me);  
};  
/* Constructors and destructors:*/  
void Queue_Init(Queue* const me,int (*isFullfunction)(Queue* const me),  
int (*isEmptyfunction)(Queue* const me),  
int (*getSizefunction)(Queue* const me),  
void (*insertfunction)(Queue* const me, int k),  
int (*removefunction)(Queue* const me) );  
void Queue_Cleanup(Queue* const me);  
/* Operations */  
int Queue_isFull(Queue* const me);  
int Queue_isEmpty(Queue* const me);  
int Queue_getSize(Queue* const me);  
void Queue_insert(Queue* const me, int k);  
int Queue_remove(Queue* const me);  
Queue * Queue_Create(void);  
void Queue_Destroy(Queue* const me);  
#endif /*QUEUE_H_*/
```
El Listado de Código 6 muestra la implementación (simple) de las operaciones de la Cola y el Listado de Código 7 proporciona un pequeño programa de prueba simple que muestra elementos insertados y eliminados dentro y fuera de la cola.

```c
/*********************************
Code 6: Queue Implementation
*********************************/

#include <stdio.h>  
#include <stdlib.h>  
#include "queue.h"  
void Queue_Init(Queue* const me,int (*isFullfunction)(Queue* const me),  
int (*isEmptyfunction)(Queue* const me),  
int (*getSizefunction)(Queue* const me),  
void (*insertfunction)(Queue* const me, int k),  
int (*removefunction)(Queue* const me) ){  
/* initialize attributes */  
me->head = 0;  
me->size = 0;  
me->tail = 0;  
/* initialize member function pointers */  
me->isFull = isFullfunction;  
me->isEmpty = isEmptyfunction;  
me->getSize = getSizefunction;  
me->insert = insertfunction;  
me->remove = removefunction;  
}  
/* operation Cleanup() */  
void Queue_Cleanup(Queue* const me) {  
}  
/* operation isFull() */  
int Queue_isFull(Queue* const me){  
return (me->head+1) % QUEUE_SIZE == me->tail;  
}  
/* operation isEmpty() */  
int Queue_isEmpty(Queue* const me){  
return (me->head == me->tail);  
}  
/* operation getSize() */  
int Queue_getSize(Queue* const me) {  
return me->size;  
}  
/* operation insert(int) */  
void Queue_insert(Queue* const me, int k) {  
if (!me->isFull(me)) {  
me->buffer[me->head] = k;  
me->head = (me->head+1) % QUEUE_SIZE;  
++me->size;  
}  
}  
/* operation remove */  
int Queue_remove(Queue* const me) {  
int value = -9999; /* sentinel value */  
if (!me->isEmpty(me)) {  
value = me->buffer[me->tail];  
me->tail = (me->tail+1) % QUEUE_SIZE;  
–me->size;
}  
return value;  
}  
Queue * Queue_Create(void) {  
Queue* me = (Queue *) malloc(sizeof(Queue));  
if(me!=NULL)  
{  
Queue_Init(me, Queue_isFull, Queue_isEmpty, Queue_getSize,  
Queue_insert, Queue_remove);  
}  
return me;  
}  
void Queue_Destroy(Queue* const me) {  
if(me!=NULL)  
{  
Queue_Cleanup(me);  
}  
free(me);  
}
```

```c
/******************************
Code 7: Queue Test Program
********************************/

#include <stdio.h>  
#include <stdlib.h>  
#include "queue.h"  
int main(void) 
{  
	int j,k, h, t;  
	/* test normal queue */  
	Queue * myQ;  
	myQ = Queue_Create();  
	k = 1000;  
	for (j=0;j<QUEUE_SIZE;j++) {  
		h = myQ->head;  
		myQ->insert(myQ,k);  
		printf("inserting %d at position %d, size =%d\n",k--,h, myQ->getSize(myQ));  
	};  
	printf("Inserted %d elements\n",myQ->getSize(myQ));  
	for (j=0;j<QUEUE_SIZE;j++) {  
	t = myQ->tail;  
	k = myQ->remove(myQ);  
	printf("REMOVING %d at position %d, size =%d\n",k,t, myQ->getSize(myQ);  
	};  
	printf("Last item removed = %d\n", k);  
	printf("Current queue size %d\n", myQ->getSize(myQ));  
	puts("Queue test program");  
	return EXIT_SUCCESS;  
}
```

Ahora supongamos que la memoria es muy escasa y, por lo tanto, necesitamos reducir el tamaño del búfer en memoria y almacenar la mayoría de los elementos en el disco. Nuestro `CachedQueue` cumple los requisitos.
El Listado de Código 8 muestra el archivo de encabezado de la clase. Puedes ver algunos aspectos importantes de la definición de la clase. Primero, tenga en cuenta que la clase base se conserva en la subclase como un atributo denominado cola. Esto incorpora las operaciones y atributos de la clase base dentro de la subclase. En segundo lugar, tenga en cuenta que las operaciones definidas para la clase base se replican como punteros de función miembro en la subclase. De esa forma, se pueden invocar directamente en la instancia de la subclase. Cada una de estas funciones virtuales puede entonces ocuparse completamente de la solicitud o tratar algún aspecto de la misma y delegar el resto a la función original definida en la clase `Queue` (aún contenida dentro de sus funciones virtuales). Por último, tenga en cuenta que la cola de salida agregada también es un atributo de la subclase. Esto permite que `CachedQueue` administre dos buffers en memoria. El "normal" (representado por la clase base) es donde se insertan nuevos datos. El otro (representado `outputQueue`) es de donde provienen los datos para su eliminación.

```c
/********************
Code Listing 8: CachedQueue header file
**********************/

#ifndef CACHEDQUEUE_H_  
#define CACHEDQUEUE_H_  
#include "queue.h"  
typedef struct CachedQueue CachedQueue;  
struct CachedQueue {  
Queue* queue; /* base class */  
/* new attributes */  
char filename[80];  
int numberElementsOnDisk;  
/* aggregation in subclass */  
Queue* outputQueue;  
/* inherited virtual functions */  
int (*isFull)(CachedQueue* const me);  
int (*isEmpty)(CachedQueue* const me);  
int (*getSize)(CachedQueue* const me);  
void (*insert)(CachedQueue* const me, int k);  
int (*remove)(CachedQueue* const me);  
/* new virtual functions */  
void (*flush)(CachedQueue* const me);  
void (*load)(CachedQueue* const me);  
};

/* Constructors and destructors:*/  
void CachedQueue_Init(CachedQueue* const me, char* fName,  
int (*isFullfunction)(CachedQueue* const me),  
int (*isEmptyfunction)(CachedQueue* const me),
int (*getSizefunction)(CachedQueue* const me),  
void (*insertfunction)(CachedQueue* const me, int k),  
int (*removefunction)(CachedQueue* const me),  
void (*flushfunction)(CachedQueue* const me),  
void (*loadfunction)(CachedQueue* const me));  
void CachedQueue_Cleanup(CachedQueue* const me);  
/* Operations */  
int CachedQueue_isFull(CachedQueue* const me);  
int CachedQueue_isEmpty(CachedQueue* const me);  
int CachedQueue_getSize(CachedQueue* const me);  
void CachedQueue_insert(CachedQueue* const me, int k);  
int CachedQueue_remove(CachedQueue* const me);  
void CachedQueue_flush(CachedQueue* const me);  
void CachedQueue_load(CachedQueue* const me);  
CachedQueue * CachedQueue_Create(void);  
void CachedQueue_Destroy(CachedQueue* const me);  
#endif /*CACHEDQUEUE_H_*/
```

El Listado de Código 9 muestra la implementación (sin E/S de archivos, solo para simplificar un poco el ejemplo). Puede ver cómo la función CachedQueue_Init() construye la instancia de subclase (con una llamada a Queue_Create()) y luego configura sus propios atributos y funciones miembro virtuales. También puede ver cómo la función CachedQueue_getSize() calcula la cantidad de elementos retenidos: es la suma de los datos retenidos en la cola, la salidaQueue y la cantidad de elementos almacenados en el disco.
Si bien la implementación no está a la altura de los estándares entregables (me gustaría agregar manejo de errores, por ejemplo), ilustra una forma de crear clases e instancias de esas clases en el lenguaje C.

```c

/************************************
Code 9: CachedQueue Implementation
**************************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include "cachedQueue.h"  
void CachedQueue_Init(CachedQueue* const me, char* fName,  
int (*isFullfunction)(CachedQueue* const me),  
int (*isEmptyfunction)(CachedQueue* const me),  
int (*getSizefunction)(CachedQueue* const me),  
void (*insertfunction)(CachedQueue* const me, int k),  
int (*removefunction)(CachedQueue* const me),  
void (*flushfunction)(CachedQueue* const me),  
void (*loadfunction)(CachedQueue* const me)) {  
    /* initialize base class */  
    me->queue = Queue_Create(); /* queue member must use its original functions */  
    /* initialize subclass attributes */  
    me->numberElementsOnDisk = 0;  
    strcpy(me->filename, fName);
    /* initialize aggregates */  
    me->outputQueue = Queue_Create();  
    /* initialize subclass virtual operations ptrs */  
    me->isFull = isFullfunction;  
    me->isEmpty = isEmptyfunction;  
    me->getSize = getSizefunction;  
    me->insert = insertfunction;  
    me->remove = removefunction;  
    me->flush = flushfunction;  
    me->load = loadfunction;  
}  
/* operation Cleanup() */  
void CachedQueue_Cleanup(CachedQueue* const me) {  
    Queue_Cleanup(me->queue);  
}  
/* operation isFull() */  
int CachedQueue_isFull(CachedQueue* const me){  
    return me->queue->isFull(me->queue) &&  
    me->outputQueue->isFull(me->outputQueue);  
}  
/* operation isEmpty() */  
int CachedQueue_isEmpty(CachedQueue* const me){  
    me->queue->isEmpty(me->queue) me->outputQueue-> isEmpty(me->outputQueue) 
    (me->numberElementsOnDisk == 0);  
}  
/* operation getSize() */  
int CachedQueue_getSize(CachedQueue* const me) {  
    me->queue->getSize(me->queue) me->outputQueue->getSize(me->outputQueue)
    me->numberElementsOnDisk;  
}  
/* operation insert(int) */  
// Imsert Algorithm:  
// if the queue is full,

//  <br>// end if|call flush to write out the queue to disk and reset the queue|

// insert the data into the queue  
void CachedQueue_insert(CachedQueue* const me, int k) {  
    if (me->queue->isFull(me->queue)) me->flush(me);  
    me->queue->insert(me->queue, k);  
}  
/* operation remove */  
// remove algorithm  
// if there is data in the outputQueue,  
// remove it from the outputQueue
// else if there is data on disk  


//  <br>//|call load to bring it into the outputQueue  <br>remove it from the outputQueue|
// else if there is data in the queue|
//  <br>//|remove it from there  <br>(if there is no data to remove then return sentinel value)|

int CachedQueue_remove(CachedQueue* const me) {  
    if (!me->outputQueue->isEmpty(me->outputQueue))  
    return me->outputQueue->remove(me->outputQueue);  
    else if (me->numberElementsOnDisk>0) {  
        me->load(me);  
        return me->queue->remove(me->queue);  
    }  
    else return me->queue->remove(me->queue);  
}  
/* operation flush */  
// Precondition: this is called only when queue is full  

//|and filename is valid|
// flush algorithm  <br>// if file is not open, then open file  <br>// while not queue->isEmpty()|
//  <br>//  <br>//|queue->remove()  <br>write data to disk  <br>numberElementsOnDisk++|

// end while  
void CachedQueue_flush(CachedQueue* const me){  
    // write file I/O statements here . . .  
}  
/* operation load */  
// Precondition: this is called only when outputQueue is empty  

//|and filename is valid|
// load algorithm  <br>// while (!outputQueue->isFull() && (numberElementsOnDisk>0)|
//  <br>//  <br>//|read from start of file (i.e., oldest datum)  <br>numberElementsOnDisk– –;  <br>outputQueue->insert()|

// end while  
void CachedQueue_load(CachedQueue* const me) {  
    // write file I/O statements here . . .  
}  
CachedQueue * CachedQueue_Create(void) {  
    CachedQueue* me = (CachedQueue *)  
    malloc(sizeof(CachedQueue));  
    if(me!=NULL)  
    {  
        CachedQueue_Init(me, "C:\\queuebuffer.dat",  
        CachedQueue_isFull, CachedQueue_isEmpty,
        CachedQueue_getSize, CachedQueue_insert, CachedQueue_remove,  
        CachedQueue_flush, CachedQueue_load);  
    }  
    return me;  
}  
void CachedQueue_Destroy(CachedQueue* const me) {  
    if(me!=NULL)  
    {  
        CachedQueue_Cleanup(me);  
    }  
    free(me);  
}
```

La capacidad de utilizar herencia (subclases) será útil en algunos de los patrones de diseño que analizaré más adelante en este libro, además de ser valiosa por sí sola.

## Máquinas de estados finitos

Una máquina de estados finitos (FSM) es una máquina especificada por un conjunto finito de condiciones de existencia (llamadas "estados") y un conjunto igualmente finito de transiciones entre los estados desencadenados por eventos.

Un FSM se diferencia de un diagrama de actividad o diagrama de flujo en que las transiciones se desencadenan por eventos (principalmente) en lugar de desencadenarse cuando se completa el trabajo realizado en el estado anterior. Los gráficos de estado se utilizan principalmente para modelar el comportamiento de elementos reactivos, como clases y casos de uso, que esperan en un estado hasta que ocurre un evento de interés. En ese punto, se procesa el evento, se realizan acciones y el elemento pasa a un nuevo estado.
Se pueden especificar acciones, como la ejecución de una declaración primitiva en lenguaje C o la invocación de una operación, para que se ejecuten cuando se entra o sale de un estado, o cuando se realiza una transición. El orden de ejecución de las acciones es el de las acciones de salida del estado predecesor, seguidas de las acciones de transición, seguidas de las acciones de entrada del estado posterior.

El UML utiliza gráficos de estado como representación formal de FSM, que son significativamente más expresivos y escalables que los FSM "clásicos" de Mealy-Moore. Las máquinas de estados UML, basadas en la notación y la semántica de los diagramas de estados del Dr. David Harel, tienen varias extensiones más allá de las máquinas de estados de Mealy-Moore, que incluyen:
- Estados anidados para especificar la membresía estatal jerárquica
- Estados AND para especificar independencia lógica y concurrencia. 
- Pseudoestados para anotar semántica dinámica específica comúnmente necesaria. 

La Figura 1-3 muestra algunos de los elementos básicos de un diagrama de estado para la clase SecuritySupervisor mostrada anteriormente en la Figura 1-1. Incluye transiciones y estados OR básicos, así como algunos conceptos menos elementales, incluidos estados anidados y pseudoestados iniciales y condicionales.

Las transiciones son líneas con flechas que provienen de un estado predecesor y terminan en un estado posterior. Las transiciones suelen tener la firma de evento y la lista de acciones opcionales. La forma básica de la firma de un evento es

nombre-evento '('lista-parámetros')' '['guardia']' '/' lista-acciones

El nombre del evento es simplemente el nombre lógico de la clase de evento que puede enviarse a una instancia del Clasificador en tiempo de ejecución, como la pulsación de tecla en la Figura 1-3. UML define cuatro tipos distintos de eventos que pueden pasarse o manejarse:
• SignalEvent: un evento enviado de forma asincrónica
• CallEvent: un evento enviado sincrónicamente
• TimeEvent – un evento debido al paso de un intervalo de tiempo (el más común) o la llegada de una época
• ChangeEvent: un cambio en una variable de estado o atributo del clasificador.

La transferencia de eventos asincrónica siempre se implementa poniendo en cola el evento hasta que el elemento esté listo para procesarlo. Es decir, el remitente “envía y olvida” el evento y continúa con sus asuntos, ignorando si el evento ha sido procesado o no. La transferencia de eventos sincrónica ejecuta el procesamiento de estado del evento en el hilo del remitente, y el remitente no puede continuar hasta que se complete el procesamiento de ese estado. Esto comúnmente se implementa invocando un método de clase llamado controlador de eventos que ejecuta la parte relevante de la máquina de estado, devolviendo el control al remitente solo cuando se completa el procesamiento del evento. Estas "operaciones desencadenadas" no tienen un cuerpo de método estándar; el cuerpo de su método es la lista de acciones en la máquina de estados.

Los eventos pueden tener parámetros: valores escritos aceptados por la máquina de estado que luego pueden usarse en la guardia y acciones en el procesamiento del evento. El diagrama de estado especifica la lista de parámetros formales, mientras que el objeto que envía el evento debe proporcionar los parámetros reales necesarios para vincularse a la lista de parámetros formales. Usaremos una sintaxis ligeramente peculiar para pasar eventos. Crearemos una estructura llamada params que contiene los parámetros nombrados para cada evento que transporta datos. Si un evento e tiene dos parámetros, xey, para usarlos en una guardia, por ejemplo, deberías desreferenciar la estructura params para acceder a su valor. Entonces, una transición desencadenada por el evento e con una protección que especifica que x debe ser mayor que 0 e y debe ser menor o igual a 10 para que se realice la transición se vería así:

`e[params->x>0 && params->y<=10]`

Los acontecimientos temporales casi siempre son relativos a la entrada a un estado. Una forma común de nombrar dicho evento (y lo que usaremos aquí) es “tm(intervalo)”, donde “intervalo” es el parámetro de intervalo de tiempo para el evento de tiempo de espera12. Si el tiempo de espera ocurre antes de que ocurra otro evento específico, entonces se tomará la transición provocada por el evento de tiempo de espera; si se envía otro evento al objeto antes de que se active el tiempo de espera, entonces el tiempo se descarta; si se vuelve a ingresar al estado, el intervalo de tiempo de espera se reinicia desde el principio.

Si una transición no proporciona un desencadenante de evento con nombre, este se activa mediante el evento de "finalización" o "nulo". Este evento ocurre tan pronto como se ingresa al estado (lo que incluye la ejecución de acciones de entrada para el estado) o cuando se completan las actividades del estado.
Una guardia es una expresión booleana contenida entre corchetes que sigue al desencadenante del evento.

El guardia debe devolver solo VERDADERO o FALSO y no tener efectos secundarios. Si se especifica una protección para una transición y se produce el desencadenante del evento (si lo hay), entonces la transición se realizará si y sólo si la protección se evalúa como VERDADERA. Si la guardia evalúa como FALSO, entonces el evento desencadenante se descarta silenciosamente y no se ejecuta ninguna acción.

La lista de acciones para la transición se ejecuta si y sólo si se realiza la transición; es decir, el objeto recibe el evento nombrado mientras está en el estado predecesor y la protección, si la hay, se evalúa como VERDADERA. El conjunto completo de acciones de salida, acciones de transición y acciones de entrada se ejecuta en ese orden y se ejecuta utilizando la semántica de ejecución hasta su finalización. La Figura 1-3 muestra acciones en varias transiciones diferentes, así como en la entrada a algunos de los estados.

Una ejecución de las tres “clases” de la Figura 1-1 usando test1 del TestDriver (que envía '1', '2', '3', '4', 'e' (el código para la tecla ENTER), seguida por 'r' (el código para la tecla RESET) se muestra en la Figura 1-4 en un diagrama de secuencia UML.

Si bien más adelante discutiré los patrones de diseño para la implementación de máquinas de estados, la implementación más común es generar declaraciones simples si-entonces o de cambio de caso. Por ejemplo, un esquema de implementación común y fácil es
- Agregar una variable de estado (por ejemplo, activeState)
- Para cada evento de la “clase”, agregue una función de receptor de eventos y pase todos los datos que necesite como parámetros
- Crear una función de despachador de eventos, llamada por cada receptor de eventos; esto procesa el evento entrante
La estructura del despachador de eventos puede ser tan simple como

```c
switch(activeState) {  
	/* for each state */  
	case state1:  
		/* for each event */  
		Switch (eventID) {  
			event1:  
			/* check each guard */  
				If (guard1()) {  
					action1();  
				} else if (guard2()) {  
					action2();  
				};  
				break;  
			event2:  
				if (guard3()) {  
					action3();  
				} else if (guard4()) {  
					action5();  
				};  
					break;  
		};  
		break;  
	case state2:  
	// etc  
}
```

Por ejemplo, dada la clase SecuritySupervisor, podría implementar el despachador de eventos de la máquina de estado como se muestra en el Listado de Código 10. Agregar eventos asincrónicos requiere agregar la cola de los eventos y sus datos. Nota: Null_id representa los llamados "eventos nulos": transiciones que no se desencadenan por eventos explícitos, sino que simplemente se "activan" cuando se completan las acciones en el estado anterior.

```c
/***************************
Code 10: SecuritySupervisor Event Dispatcher
***************************7

static eventStatus dispatchEvent(short id) {  
eventStatus res = eventNotConsumed;  
switch (activeState) {  
/* are we in the Idle state? */
case SecuritySupervisor_Idle:  
{  
    if(id == Null_id) /* null triggered event? */  
    {  
        if(retries>=3)  
        {  
        activeState = SecuritySupervisor_ErrorState;  
        displayMsg("ERROR: Max retries Exceeded");  
        res = eventConsumed;  
        }  
        else  
        {  
        ++retries;  
        activeState = SecuritySupervisor_Accepting;  
        res = eventConsumed;  
        }  
    }  
}  
break;  
/* are we in the Accepting State? */  
case SecuritySupervisor_Accepting:  
{  
    if(id == keypress_SecuritySupervisor_Event_id)  
    {  
        /* params struct has the data in the attribute ’key’ */  
        /* transition 1 */  
        if(isCANCEL(params->key))  
        {  
        retries = 0;  
        displayMsg("Cancelled");  
        activeState = SecuritySupervisor_Idle;  
        {  
            /* state ROOT.Idle.(Entry) */  
            strcpy(pin, "");  
        }  
        res = eventConsumed;  
        }  
        else  
        {  
            /* transition 3 */  
            if(isDigit(params->key))  
            {  
                /* transition 3 */  
                addKey(params->key);  
                activeState = SecuritySupervisor_Accepting;  
                res = eventConsumed;  
            }  
            else  
            {  
                /* transition 5 */
                if(isENTER(params->key))  
                {  
                activeState =  
                SecuritySupervisor_CheckingLength;  
                res = eventConsumed;  
                }  
            }  
        }  
    }  
}  
break;  
case SecuritySupervisor_CheckingLength:  
{  
    if(id == Null_id)  
    {  
        /* transition 10 */  
        if(strlen(pin) == 4)  
        {  
            activeState = SecuritySupervisor_ValidatingPIN;  
            res = eventConsumed;  
        }  
        else  
        {  
            {  
                /* transition 9 */  
                displayMsg("ERROR: PIN wrong length");  
            }  
            activeState = SecuritySupervisor_Idle;  
            {     
                /* state ROOT.Idle.(Entry) */  
                strcpy(pin, "");  
            }  
            res = eventConsumed;  
        }  
    }  
}  
break;  
case SecuritySupervisor_ValidatingPIN:  
{  
    if(id == Null_id)  
    {  
        /* transition 13 */  
        if(isValid(pin))  
        {  
            {  
                /* transition 13 */  
                unlockDoor();  
                displayMsg("Door unlocked");  
            }  
            activeState = SecuritySupervisor_SecurityOpen;  
            res = eventConsumed;
        }  
        else  
        {  
            {  
            /* transition 12 */  
            displayMsg("ERROR:: Invalid PIN");  
            }  
            activeState = SecuritySupervisor_Idle;  
            {  
                /* state ROOT.Idle.(Entry) */  
                strcpy(pin, "");  
            }  
            res = eventConsumed;  
        }  
    }     
}  
break;  
case SecuritySupervisor_SecurityOpen:  
{  
    if(id == keypress_SecuritySupervisor_Event_id)  
    {  
        /* params-key has the data passed with the event */  
        /* transition 14 */  
        if(isRESET(params->key))  
        {  
        {  
        /* transition 14 */  
        lockDoor(); retries = 0;  
        displayMsg("Door locked.");  
        }  
        activeState = SecuritySupervisor_Idle;  
        {  
        /* state ROOT.Idle.(Entry) */  
        strcpy(pin, "");  
        }  
        res = eventConsumed;  
        }  
    }  
}  
break;  
default:  
break;  
}  
    return res;  
}
```

Ciertamente hay más cosas sobre las máquinas de estados de las que hemos introducido hasta ahora, pero se analizan más adelante en el Capítulo 5. 

Para una discusión más detallada de las máquinas de estados UML, consulte el Capítulo 3 de Real-Time UML 3.ª edición13 y los Capítulos 7 y 12. en Pasar tiempos difíciles14.