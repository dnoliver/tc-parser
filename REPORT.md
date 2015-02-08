#INFORME

##PROBLEMATICA ABORDADA

Aplicacion practica de los contenidos teoricos adquiridos durante el cursado de la asignatura 
"Tecnicas de Compiladores", con el fin de extender y reforzar los conocimientos en cuanto a la construccion de 
compiladores de codigo, y las fases asociadas al proceso de compilacion. 

Mediante una aplicacion practica de un compilador de lenguaje C, se buscara aplicar 3 etapas fundamentales en el 
proceso de compilacion de un programa basico en lenguaje C:

* Analisis Lexico
* Analisis Sintactico
* Analisis Semantico
* Generacion de codigo intermedio

##SOLUCION PROPUESTA

Para el diseño y desarrollo del compilador, el equipo de desarrollo se baso en las siguientes premisas:

* utilizar herramientas que agilizan la implementacion de las distintas etapas de compilacion
* implementar soluciones conocidas a los distintos problemas inherentes a la construccion de compiladores
* reutilizar recursos utiles disponibles en la web
* verificar los incrementos implementados mediante casos de test automaticos
* reutilizacion de codigo mediante implementacion de patrones de diseño

###Analisis Lexico

Un analizador léxico y/o analizador lexicográfico (en inglés scanner) es la primera fase 
de un compilador consistente en un programa que recibe como entrada el código fuente de otro programa 
(secuencia de caracteres) y produce una salida compuesta de tokens (componentes léxicos) o símbolos. 
Estos tokens sirven para una posterior etapa del proceso de traducción, siendo la entrada para el 
analizador sintáctico (en inglés parser).

La especificación de un lenguaje de programación a menudo incluye un conjunto de reglas que 
definen el léxico. Estas reglas consisten comúnmente en expresiones regulares que indican el conjunto 
de posibles secuencias de caracteres que definen un token o lexema.

Esta etapa está basada usualmente en una máquina de estados finitos. Esta máquina contiene la 
información de las posibles secuencias de caracteres que puede conformar cualquier token que 
sea parte del lenguaje (las instancias individuales de estas secuencias de caracteres son denominados lexemas). 
Por ejemplo, un token de naturaleza entero puede contener cualquier secuencia de caracteres numéricos. 

[Wikipedia:Analizador Lexico](http://es.wikipedia.org/wiki/Analizador_l%C3%A9xico)

Para la construccion del analizador lexico, se utiliza Flex. Flex es una herramienta para generar escáneres. 
Un escáner, a veces llamado un tokenizer, es un programa 
que reconoce patrones léxicos en el texto. El programa flex lee los archivos de entrada 
especificados por el usuario, o la entrada estándar si no se dan los nombres de archivo, 
para una descripción del escáner a generar. La descripción es en forma de pares de expresiones regulares y código C,
denominadas reglas. Flex genera un archivo fuente en C llamado `lex.yy.c`, que define la función `yylex()`. 
El archivo `lex.yy.c` puede ser compilado y vinculado a producir un ejecutable.
Cuando se ejecuta el archivo ejecutable, este analiza su entrada para las apariciones de texto que coinciden 
con las expresiones regulares para cada regla. Cada vez que encuentra una coincidencia, 
se ejecuta el código C correspondiente.

[SourceForge:Flex] (http://flex.sourceforge.net/)

La descripcion del escaner se encuentra en el archivo [/c/ansi-c.l] [scanner-file], el cual se implemento a partir
de una solucion propuesta por Jutta Degener, disponible en  [http://www.lysator.liu.se/c/ANSI-C-grammar-l.html](http://www.lysator.liu.se/c/ANSI-C-grammar-l.html).

###Analisis Sintactico

Un analizador sintáctico (o parser) es una de las partes de un compilador que transforma su entrada 
en un árbol de derivación.
El análisis sintáctico convierte el texto de entrada en otras estructuras (comúnmente árboles), 
que son más útiles para el posterior análisis y capturan la jerarquía implícita de la entrada. 
Un analizador léxico crea tokens de una secuencia de caracteres de entrada y son estos tokens 
los que son procesados por el analizador sintáctico para construir la estructura de datos, 
por ejemplo un árbol de análisis o árboles de sintaxis abstracta.
El análisis sintáctico también es un estado inicial del análisis de frases de lenguaje natural. 
Es usado para generar diagramas de lenguajes que usan flexión gramatical, 
como los idiomas romances o el latín. Los lenguajes habitualmente reconocidos por 
los analizadores sintácticos son los lenguajes libres de contexto. Cabe notar que existe 
una justificación formal que establece que los lenguajes libres de contexto son aquellos 
reconocibles por un autómata de pila, de modo que todo analizador sintáctico que reconozca 
un lenguaje libre de contexto es equivalente en capacidad computacional a un autómata de pila.

[Wikipedia:Analizador Sintactico](http://es.wikipedia.org/wiki/Analizador_sint%C3%A1ctico)

Para la construccion del analizador sintactico, se utiliza Bison. Bison es un generador de parsers de 
propósito general que convierte una gramática libre de contexto en un parser LR determinista o 
en un parser LR generalizado (GLR), empleando tablas LALR(1).

[GNU Software:Bison](http://www.gnu.org/software/bison/)

La descripcion del escaner se encuentra en el archivo [/c/ansi-c.y] [parser-file], el cual se implemento a partir
de una solucion propuesta por Jutta Degener, disponible en  [http://www.lysator.liu.se/c/ANSI-C-grammar-y.html](http://www.lysator.liu.se/c/ANSI-C-grammar-y.html).

En este punto, el programa procesado es almacenado en un [Arbol Sintactico Abstracto](http://es.wikipedia.org/wiki/%C3%81rbol_de_sintaxis_abstracta),
el cual se utiliza para las etapas de compilacion posteriores. Para la construccion del AST, se diseño una 
jerarquia de clases que representan diferentes nodos del arbol AST, en la que cada nodo corresponde a una regla 
gramatical del lenguaje. Se muestra un ejemplo de un AST generado por el parser, a partir de una sentencia simple entrada:

```
/** programa de entrada */
int x;

/** AST generado */
<?xml version="1.0"?>
<TranslationUnit>
  <StatementList>
    <Declaration>
      <DeclarationSpecifierList>
        <TypeSpecifier>int</TypeSpecifier>
      </DeclarationSpecifierList>
      <InitDeclaratorList>
        <InitDeclarator>
          <IdentifierDeclarator>x</IdentifierDeclarator>
        </InitDeclarator>
      </InitDeclaratorList>
    </Declaration>
  </StatementList>
</TranslationUnit>
```

###Analisis Semantico

El análisis semántico es la tarea de asegurar
que las declaraciones y sentencias de un
programa son semánticamente correcta, es decir, que
su significado es claro y consistente con la definicion del lenguaje.

[PDF:Compilers Construction](http://home.adelphi.edu/~siegfried/cs372/372l8.pdf)

En la fase de analisis semantico, se implementaron las siguientes validaciones:

* verificacion de variables utilizadas sin previa declaracion.
* verificacion de la estructura de la operaciones aritmeticas y logicas
* verificacion de variables declaradas mas de una vez en un mismo contexto

###Jerarquia de classes

!["UML Diagram"][statement-uml]

!["UML Diagram"][declaration-uml]

!["UML Diagram"][controls-uml]

!["UML Diagram"][expression-uml]

###Generacion de codigo

Para la fase de generacion de codigo, se implementa la construccion de 3 artefactos:

* tabla de simbolos
* codigo embellecido
* codigo de tres direcciones

La solucion implementada esta basada en un ejemplo disponible en  [http://gnuu.org/2009/09/18/writing-your-own-toy-compiler](http://gnuu.org/2009/09/18/writing-your-own-toy-compiler),
el cual implementa un pequeño compilador y generacion de codigo para Low Level Virtual Machine (LLVM).
Por ello, la generacion de cualquiera de los artefactos se realiza mediante el recorrido del AST, ejectuando 
la operacion correspondiente en cada uno de los nodos del arbol.

Una descripcion de como es el proceso de generacion de codigo se muestra a continuacion, en pseudocodigo

```
function doNodeOperation(context) {
  /* do the operation in childs nodes */
  For (i = 0; i <= this.childsNodes.lenght; i++) {
      this.childsNodes[i]->doNodeOperation(context);
      ...
      ...
  }
  
  /* do the operation in current node */
  ...
  ...
}
```

####Generacion de tabla de simbolos

Para la generacion de la tabla de simbolos, se tiene en cuenta los distintos contextos de ejecuccion. Existe un 
contexto global del programa, y contextos locales a cada definicion de funciones. Las declaraciones de variables 
o funciones se registran en la tabla de simbolos correspondiente al contexto actual de ejecucion. 

Ademas, la tabla de simbolos de cada contexto almacena la cantidad de invocaciones realizadas sobre ese simbolo. 
Para ello, primero se verifica si el simbolo existe en el contexto local o global, y se registra una invocacion 
del simbolo. En caso de no existir en ninguno de los dos contextos, el simbolo se considera no declarado, y 
se muestra un error.

Se muestra la tabla de simbolos generada por un programa simple, a modo de ejemplo. El contexto de ejecucion 0 
corresponde al contexto global del programa, el contexto de ejecucion 1 es el contexto interno de la 
function `void main();`. Como podemos ver, el identificador `main` esta declarado en el contexto global, 
mientras que `a` esta declarado en el contexto de la function `main`.

```
/** programa de entrada */
void main()
{
    int a;
    a = 23;
    if (a == 23)
      a = 10;
    else
      a = 19;
}

/** tabla de simbolos generada */
<?xml version="1.0"?>
<Contexts>
  <SymbolTable context="0">
    <Symbol>
      <Identifier>main</Identifier>
      <Invocations>0</Invocations>
    </Symbol>
  </SymbolTable>
  <SymbolTable context="1">
    <Symbol>
      <Identifier>a</Identifier>
      <Invocations>4</Invocations>
    </Symbol>
  </SymbolTable>
</Contexts>
```

####Generacion de codigo embellecido

Para la generacion de codigo embellecido, se recorre el AST desde el nodo raiz. Cada nodo del arbol es responsable 
de generar su representacion en codigo embellecido, teniendo en cuenta la correcta indentacion y salto de linea. 
A continuacion se muestra un ejemplo del codigo embellecido de salida generado a partir de un programa en C:

```
/** programa de entrada */
long factorial(int n) { return n == 0? 1 : (n * factorial(n-1));} int main(){ in
t n = 3; long f; f = factorial(n); return 0;}

/** codigo embellecido generado */
long factorial(int n)
{
        return n == 0 ? 1 : (n * factorial(n - 1));
}
int main()
{
        int n = 3;
        long f;
        f = factorial(n);
        return 0;
}
```

####Generacion de codigo de tres direcciones

Para la generacion de codigo de tres direcciones, se necesito implementar las siguientes operaciones:

* generacion de variables temporales
* generacion de etiquetas (labels)

La estrategia utilizada es la misma descripta anteriormente: el arbol AST se recorre desde el nodo raiz, y cada 
nodo del arbol es responsable de generar codigo de tres dirrecciones propio y de sus nodos hijos. 
Vemos un ejemplo de generacion de codigo de tres direcciones, a continuacion:

```
/** programa de entrada*/
void main()
{
        int b;
        int a;
        b = 3;
        a = 12;
        a = (b + 2) - (a * 3) / 6;
}

/** codigo de tres direcciones generado */
main:
  BeginFunc
  t0 = 3
  b = t0
  t1 = 12
  a = t1
  t2 = 2
  t3 = b + t2
  t4 = 3
  t5 = a * t4
  t6 = 6
  t7 = t5 / t6
  t8 = t3 - t7
  a = t8
EndFunc
```

##CONCLUSION

Como resultado de la construccion de un pequeño compilador de codigo C, y la implementacion de las diferentes 
fases de compilacion, tenemos las siguientes conclusiones:

* Es fundamental un buen el diseño y comprension de la gramatica del lenguaje, asi como el conocimiento de las
ventajas que provee la utilizacion de Bison para la creacion de el parser. Dado que un error en la definicion 
de la gramatica puede causar la necesidad de reimplementar gran parte del software, ademas, el desconocimiento de
las capacidades provistas por Bison hace que se planteen soluciones alternativas y se desaproveche el poder de la
herramienta. 

* El diseño orientado a objetos, patrones de diseño, y soluciones conocidas a los problemas de implementacion 
de un compilador agilizan la construccion del mismo. Ademas, permiten que la extension y evolucion del compilador 
se haga de una forma mas ordenada y uniforme. Como contraposicion, la gran cantidad de clases que implementamos 
para soportar el Arbol Sintactico Abstracto, hace que un pequeño cambio en la definicion de un metodo que debe ser
implementado por todos los nodos, deba ser propagado por toda la jerarquia de clases.

* Dado el desconocimiento de los desarrolladores, la implementacion de codigo de tres direcciones fue una area
dificil. Durante el periodo de investigacion, no encontramos una descripcion de como implementar codigo de 
tres direccion que se ajuste a nuestras necesidades. Las soluciones encotradas se pueden clasificar en dos grupos:
soluciones simplistas, aplicables solo a algunos casos de ejemplo, y soluciones complejas, como GENERIC o GIMPLE,
implementadas por GNU. A causa de ello, la implementacion realiza fue construida a partir de varias referencias.
Un ejemplo claro de esta situacion es la implementacion del codigo de tres direcciones para el operador ternario
`A? B : C;`, para la cual no se encontro ninguna solucion propuesta, y se hizo una implementacion propia.

[scanner-file]: /source/ansi-c.l  "Scanner definition"
[parser-file]: /source/ansi-c.y  "Parser definition"
[statement-uml]: /media/Statement.png "Statement"
[expression-uml]: /media/Expression.png "Expression"
[controls-uml]: /media/ControlStatements.png "Controls Statements"
[declaration-uml]: /media/Declaration.png "Declaration Statements"
