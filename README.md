# Assignment 3 - dps-lab-1
En la realización de este laboratorio se ha utilizado GCC en la versión 10.2.0 corriendo en un Debian 10 en la versión testing, llamada Bullseye. Aún así no creo que haya problema corriendolo en otras versiones.
### Enumerar las reglas y recomendaciones que se rompen en este código
- STR30-C: Do not attempt to modify String literals. [Link to CMU wiki](https://wiki.sei.cmu.edu/confluence/display/c/STR30-C.+Do+not+attempt+to+modify+string+literals)
```c
// Código que lo incumple:
char *ptr_char  = "new string literal"; // Línea 67
ptr_char [0] = 'N'; // Línea 101
// Solución:
char ptr_char[]  = "new string literal";
ptr_char [0] = 'N';
```
	
- STR11-C: Do not specify the bound of a character array initialized with a string literal [Link to this rule/recommendation in CMU wiki](https://wiki.sei.cmu.edu/confluence/display/c/STR11-C.+Do+not+specify+the+bound+of+a+character+array+initialized+with+a+string+literal)
```c
// Código que lo incumple (Está comentada la parte que lo incumple):
int size_array1 = strlen("аналитик"); // Línea 68
// char analitic1[size_array1]="аналитик"; // Línea 71
// Una posible solución:
char analitic1[]="аналитик";
// Entendiendo que en el caso de las varibles analitic2 (línea 72) y analitic3 están declaradas con mucho más espacio entrando en una de las excepciones nombradas en la wiki como STR11-C-EX2.
```

- MSC24-C: Do not use deprecated or obsolescent functions [Link to this rule/recommendation in CMU wiki](https://wiki.sei.cmu.edu/confluence/display/c/MSC24-C.+Do+not+use+deprecated+or+obsolescent+functions)
```c
// Código que lo incumple:
printf("Continue? [y] n: "); // Unchecked Obsolescent Functions - Línea 50
gets(response); // Deprecated function - Línea 51
strcpy(key, argv[1]); // Unchecked Obsolescent Functions - Línea 78
strcat(key, " = "); // Unchecked Obsolescent Functions - Línea 79
strcat(key, argv[2]); // Unchecked Obsolescent Functions - Línea 80
printf ("%s",array1); // Unchecked Obsolescent Functions - Línea 87
printf ("\n"); // Unchecked Obsolescent Functions - Línea 88
printf ("%s",array2); // Unchecked Obsolescent Functions - Línea 89
printf ("\n"); // Unchecked Obsolescent Functions - Línea 90
printf ("\n"); // Unchecked Obsolescent Functions - Línea 93
printf ("\n"); // Unchecked Obsolescent Functions - Línea 95
strncpy(array3, array5, sizeof(array3)); // Unchecked Obsolescent Functions - Línea 97
strncpy(array4, array3, strlen(array3)); // Unchecked Obsolescent Functions - Línea 98
// Solución:
printf -> printf_s (in Windows)
gets -> fgets 
strcpy -> strcpy_s (in Windows c11) or snprintf
strcat -> strcat_s (in Windows c11) OR strncat
strncpy -> strncpy_s (in Windows c11) or snprintf
```
	
- STR31-C: Guarantee that storage for strings has sufficient space for character data and the null terminator [Link to this rule/recommendation in CMU wiki](https://wiki.sei.cmu.edu/confluence/display/c/STR31-C.+Guarantee+that+storage+for+strings+has+sufficient+space+for+character+data+and+the+null+terminator).
```c
// Código que lo podría incumplir:
strncpy(array4, array3, strlen(array3)); // Línea 98
// En este caso no habría problema porque son del mismo tamaño entonces el strlen máximo de array3 entraría en array4
```

- STR35-C: Do not copy data from an unbounded source to a fixed-length array  [Link to this rule/recommendation in CWE wiki](https://cwe.mitre.org/data/definitions/120.html)
```c
// Código que lo incumple:
gets(response); // Buffer Copy without Checking Size of Input- Buffer Overflow - Línea 51
strcpy(key, argv[1]); // Buffer Copy without Checking Size of Input- Buffer Overflow - Línea 78
strcat(key, argv[2]); // Buffer Copy without Checking Size of Input- Buffer Overflow - Línea 80
```

- STR32-C: Do not pass a non-null-terminated character sequence to a library function that expects a string. [Link to this rule/recommendation in CMU wiki](https://wiki.sei.cmu.edu/confluence/display/c/STR32-C.+Do+not+pass+a+non-null-terminated+character+sequence+to+a+library+function+that+expects+a+string)
```c
// Código que lo incumple:
strncpy(array3, array5, sizeof(array3)); // Línea 97
array3[sizeof(array3)-1]='\0'; // Línea 103 - En este caso el sizeof recibe un String que no contiene el null terminator.
```

### Arreglar cualquier tipo de error. Añadir un comentario explicando como resolverlo.
* gets_example_func -> Devuelve un 1 siendo una función void. Además de ser una función que no se usa por lo tanto la comento (por no borrarla).
* get_y_or_n -> Cambiamos el gets por fgets.  
* get_dirname -> Rehacemos la función para que devuelva el directorio de trabajo actual. Hacemos uso de la función getcwd y la librería unistd.h
* Añadimos una comprobación de que se necesitan dos argumentos debido a que posteriormente en la línea 78 y 80 los usa sin ningún tipo de comprobación previa.
* Cambiamos los métodos strcpy por strcpy_s en caso de que fuese para Windows dado que para Unix no está implementado. [Link](https://stackoverflow.com/questions/30465024/in-what-library-is-strcat-s). En nuestro caso lo cambiamos por el método snprintf.
* Cambiamos los métodos strcat por strcat_s y printf_s en caso de que fuese para windows dado que Unix no lo tiene implementado en el standard c11. [Link](https://stackoverflow.com/questions/30465024/in-what-library-is-strcat-s). Por lo tanto únicamente cambiaremos los strcat por strncat que nos añade una comprobación del tamaño a añadir y comprobaremos los formatos que utilizan los printf.
* Arreglamos la variable s1.
* Arreglamos la declaración ptr_char que hemos comentado al principo del README.
* Quitamos el fgets sin sentido dado que el método get_y_or_n ya cumple la función y la varible asociada.
* Modificamos los strncpy dado como se describe en [distintos foros](https://joequery.me/code/snprintf-c/), las versiones 'n' de las funciones son más seguras y menos susceptibles a buffer overflows, pero el caso de strncpy es una excepción a esa regla. En este caso esta función no garantiza que tengamos un NULL terminator por lo tanto la cambiamos por [snprintf](https://joequery.me/code/snprintf-c/). También aumentamos el tamaño de los arrays para que no nos salga warning de truncación, aunque realmente no haría falta.
* Finalmente comentamos las variables que no se usen como analitic3, size_array2, size_array1 y ptr_char(incluido una de las últimas sentencias en la que se le cambia un char a esta variable).

### Compilar el archivo usando una herramienta de software para administrar el proceso de compilación usando un método independiente del compilador (Cmake, scons, etc...)
#### Adaptar el proceso para usar diferentes herramientas y parámetros de compilación (gcc vs g++), -Wall, estándares(-std=c99 y -std=c11).. 
#### Comparar entre dos estandares diferentes
En mi caso he hecho uso de cmake (versión 3.16.3) para administrar el proceso de compilación en el que encontramos las dos versiones para las que se compila perfectamente; C11, C99. Para ello, se incluye un fichero CMakeList.txt con las opciones de la compilación y un script run.sh que además de indicar que compilador utilizar (en mi caso gcc) crea la carpeta build, compilando el programa ahí.


### Ejemplo de análisis estáticos
![cppcheck](/imgs/cppcheck.png)
![sparse](/imgs/sparse.png)


### Referencias:
- https://wiki.sei.cmu.edu/confluence/display/c/SEI+CERT+C+Coding+Standard
