
## Diagrama de Clases
Esta sección describe los diversos elementos del diagrama de clases.

<img alt="<texto-alt>" src="./images/Basic_Class_Diagram.jpeg">
<center>(Fig 1. Diagrama de Clases Basico)</center>


1. Elementos nodales
    1. __Clase__:
    Una clase es una representación de un elemento que combina elementos de datos (llamados atributos) con funciones que actúan sobre ellos (llamadas operaciones). Las clases normalmente se implementan como estructuras que contienen los atributos.
    2. __Instancia__:
    Una instancia es la creación de una nueva variable del tipo de estructura que define la clase.
    3. __Interfaz__:
    Una interfaz es una especificación de un conjunto de servicios (operaciones y/o recepciones de eventos) que una clase debe implementar. Una interfaz no tiene implementación ni atributos; no puede ser
    Una interfaz es una especificación de un conjunto de servicios (operaciones y/o recepciones de eventos) que una clase debe implementar. Una interfaz no tiene implementación ni atributos; no se puede crear una instancia. Una interfaz se representa con el mismo tipo de cuadro que una clase, por lo que se distingue visualmente con el estereotipo «Interfaz».
    4. __Atributo__:
    Una variable mantenida dentro de una clase.
    5. __Operación__:
    Una función mantenida dentro de una clase que normalmente manipula los atributos de la clase. En este libro, el estilo de implementación común de una operación es utilizar la notación <Nombre de clase>_<Nombre de operación>, como SensorClass_getData(). El primer parámetro pasado a la clase es un puntero a la instancia de la clase.
    6. __Recepción de eventos__:
    Un tipo especial de operación que se invoca de forma asincrónica y provoca que se produzcan transiciones de eventos en la máquina de estados asociada con la clase.
    7. __Comentario__:
    Una forma gráfica de representar comentarios textuales. Puede estar anclado a uno o más elementos del diagrama o puede estar desanclado.

