# Actividad *6*: *Sockets y Señales*  

##### Estudiantes:  
*Carla Pérez Gavilán del Castillo* - *A01023033* - *CSF*  
*Andrés Barragán Salas* - *A01026567* - *CSF*  


##### Profesor:  
*Vicente Cubells Nonell*

## Instrucciones

Escriba un programa en C que cumpla con los siguientes requisitos:

* Inicialmente se bloquearán todas las señales excepto la señal SIGALARM.
*  Mediante una función se debe comprobar si en el directorio actual existe un subdirectorio llamado “datos”. Si éste no existe, se deberá crear; en caso contrario, se borrarán todos los archivos que contenga.
* El programa principal se encargará de instalar un gestor para la señal SIGALRM. 
* A continuación, mediante un ciclo realizará  iteraciones, en cada una de las cuales:
   - Generará un nombre de archivo distinto (el primero de ellos “a0” , el siguiente “a1” y, así sucesivamente), abrirá dicho archivo dentro del subdirectorio “datos” (es obligatorio utilizar descriptores de archivos), establecerá un temporizador a t segundos, y, finalmente, comenzará a escribir en el archivo recién creado el carácter “x” mientras una variable global (de nombre “grabar”) valga 1. 
   - Cuando el temporizador expire, se debe establecer la variable “grabar” a 0 y escribir en el archivo todas las señales que ha recibido el proceso y se encuentran pendiente por procesar y posteriormente cerrar el archivo. 
    - Por último, listar en pantalla los nombres de los archivo creados y el tamaño de cada uno. 
* El número total de archivo a crear, así como el número de segundos que establece el temporizador, se pasarán como argumentos al programa.
    - -n : número de archivos 
    - -t : segundos del temporizador

## Uso
1. Debe ejecutar el programa dentro del directorio de donde desea correrlo (es decir, donde se encuentre el directorio "datos" o donde desee crearlo)
2. Ejecutar el programa en consola de la siguiente forma: 
 
      gcc main.c -o conjunto  
      ./conjunto -n # -t #

_Nota: el caracter # puede sustituirse por el número de archivos y segundos del temporizador._ 
