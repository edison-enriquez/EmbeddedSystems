# Depuración y prueba

El general prusiano von Clausewitz escribió: “Todo en la guerra es muy simple, pero lo más simple es muy difícil10”. ¡Bien podría haberlo dicho sobre el software!
Lo más simple y muy difícil del software no es escribir el software, sino escribir el software correcto con la funcionalidad adecuada. El estado del arte en el desarrollo de software libre de defectos es una práctica ágil conocida como desarrollo basado en pruebas (TDD). En TDD, las pruebas unitarias para una pieza de software se escriben simultáneamente con, o incluso ligeramente antes, el software que verificará. Con mucha frecuencia, las pruebas unitarias se omiten por completo o se realizan demasiado tarde para tener algún efecto beneficioso en el software.
Hay muchos tipos diferentes de pruebas unitarias que se pueden aplicar al software en general y al software integrado en particular. Éstas incluyen:

- Funcional: prueba el comportamiento o la funcionalidad de un sistema o elemento del sistema.
- Calidad de servicio: prueba el “rendimiento” de un sistema o elemento del sistema, a menudo para medir el desempeño del sistema o elemento frente a sus requisitos de desempeño.
- Pruebas de condiciones previas: prueba que el comportamiento del sistema o elemento del sistema es correcto en el caso de que se cumplan las invariantes precondicionales y en el caso de que se violen las invariantes precondicionales.
- Rango: prueba valores dentro de un rango de datos
- Estadístico: prueba valores dentro de un rango seleccionándolos estocásticamente a partir de una función de densidad de probabilidad (PDF)
- Límite: prueba valores justo en los bordes, justo dentro y justo fuera de un rango de datos.
- Cobertura: prueba que todas las rutas de ejecución se ejecutan durante un conjunto de pruebas.
- Estrés: prueba datos que exceden el ancho de banda esperado de un sistema o elemento del sistema.
- Volumen, también conocido como “prueba de carga”, prueba el sistema con grandes cantidades de datos que cumplen o superan su carga de diseño.
- Sembramiento de fallas: pruebas en las que se introduce intencionalmente una falla en el sistema para garantizar que el sistema la maneje adecuadamente.
- Pruebas en el host: realizar la mayoría de las pruebas en las plataformas del host utilizando un host nativo
cumplidor y un subconjunto crítico en la plataforma de destino utilizando un compilador cruzado
- Simulación en el host: simulación de la plataforma de destino en el host con compilación cruzada
software y volver a probar un subconjunto crítico en el objetivo con el mismo código objeto
- Herramientas de prueba de software comerciales: utilizando herramientas de prueba de software, como TestRT™,
LDRA™ o VectorCAST™
- Herramientas comerciales integradas de hardware y software: esto incluye herramientas como analizadores lógicos, emuladores en circuito, herramientas de prueba compatibles con JTAG y emuladores de ROM. De los diversos tipos de pruebas, las pruebas de rendimiento suelen ser las más difíciles de realizar adecuadamente. Esto se debe a que la mayoría de los métodos comunes para ejecutar casos de prueba implican ejecutar software adicional en la misma plataforma de destino, lo que afecta el tiempo y el rendimiento del software bajo prueba. Siempre que sea posible, es claramente mejor utilizar la depuración asistida por hardware con emuladores en circuito o emuladores ROM para realizar pruebas de rendimiento.
