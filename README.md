Técnicas de Compilación
=======================

Maximiliano A. Eschoyez

# Resumen

El objetivo de este Trabajo Final es extender las funcionalidades del programa
realizado como Trabajo Práctico Nro. 2. El programa a desarrollar tiene como objetivo
tomar un archivo de código fuente en C, generar como salida una verificación
gramatical reportando errores en caso de existir, generar código intermedio y realizar
el etiquedato de bloques de código intermedio para futuras optimizaciones.

# Consigna

El objetivo de este Trabajo Final es mejorar el filtro generado en el Trabajo Práctico
Nro. 2. Dado un archivo de entrada en C, se debe generar como salida el reporte de errores
en caso de existir. Para lograr esto se debe construir un parser que tenga como mínimo la
implementación de los siguientes puntos:
* Reconocimiento de bloques de código delimitados por llaves y controlar balance de apertura y cierre.
* Verificación de la estructura de las operaciones aritmético/lógicas y las variables o números afectadas.
* Verificación de la correcta utilización del punto y coma para la terminación de instrucciones.
* Balance de llaves, corchetes y paréntesis.
* Tabla de símbolos.
* Llamado a funciones de usuario.

Si la fase de verificación gramatical no ha encontrado errores, se debe proceder a:
* generar una versión embellecida del código fuente original para facilitar su lectura y posible impresión,
* detectar variables y funciones declaradas pero no utilizadas y viceversa,
* generar la versión en código intermedio utilizando código de tres direcciones, el cual 
fue abordado en clases y se encuentra explicado con mayor profundidad en la bibliografía de la materia, y
* etiquetar los bloques de código intermedio a los cuales podrían aplicarse optimizaciones.

En resumen, dado un código fuente de entrada el programa deberá generar 2 archivos de salida:
* La versión embellecida del código fuente, y
* La versión en código de tres direcciones con las etiquetas de bloque.

# Presentación del Trabajo Final

## Código Fuente

El código fuente generado para este proyecto y la versión digital del informe en PDF 
deberán entregarse a través del enlace correspondiente en el Aula Virtual del curso. En
dicho enlace se deberá subir un único archivo en formato ZIP conteniendo todos los
código fuente que se requieran para la realización del trabajo final y el informe.

## Informe Escrito

Se entregará al profesor un informe escrito (en versión digital formato PDF) donde
se debe describir la problemática abordada en el trabajo final, el desarrollo de la solución
propuesta y una conclusión. El texto deberá ser conciso y con descripciones apropiadas.
No se debe incluir el código fuente, sino los textos necesarios para realizar las explicaciones
pertinentes.
