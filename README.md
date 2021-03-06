[![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://classroom.github.com/online_ide?assignment_repo_id=294859&assignment_repo_type=GroupAssignmentRepo)
# Actividad *6*: *Sockets y Señales*  

##### Estudiantes:  
*Carla Pérez Gavilán del Castillo* - *A01023033* - *CSF*  
*Andrés Barragán Salas* - *A01026567* - *CSF*  


##### Profesor:  
*Vicente Cubells Nonell*

## Instrucciones
Resuelva el ejercicio que aparece a continuación:

Se desea diseñar un sistema para controlar la sincronización de semáforos en un cruce de dos vías principales en la ciudad. Para que todo funcione correctamente y no ocurran accidentes, solo habrá un semáforo en verde a la vez.

* En el cruce existirán 4 semáforos, uno en cada esquina, que se comunicarán entre sí para cederse el turno de ponerse en verde.
* Cada semáforo estará en verde 30 segundos y posteriormente se podrá en rojo y le cederá el turno al semáforo que se encuentre a su derecha, enviándole una señal SIGUSR1. Mientras un semáforo no reciba ésta señal deberá permanecer en rojo.
* Se desea contar con una consola de administración centralizada que se encuentra en un centro de monitoreo remoto.
* Cada semáforo al cambiar de estado, le enviará a la consola su nuevo estado y ésta mostrará en la pantalla el estado actual de cada semáforo.
* Como medida de seguridad, desde la consola se puede enviar un mensaje a todos los semáforos para ponerlos en rojo o en intermitente (de 00:00 a 6:00) según el siguiente criterio:
  * Cuando la consola recibe un Ctrl+Z le envía el mensaje de ponerse en rojo.
  * Cuando recibe un Ctrl+C le envía el de ponerse en intermitente.
  * Cuando los semáforos reciben los mensajes anteriores, cambian de estado inmediatamente sin importar cómo se encontraban en ese momento.
  * El mismo mensaje se envía para regresar los semáforos al estado en que se encontraban. Por ejemplo, si se manda el mensaje de ponerse en rojo una vez, todos los semáforos almacenarán su estado actual y de pondrán en rojo; cuando vuelvan a recibir el mismo mensaje, restaurarán su estado al mismo punto en que se encontraban inicialmente.
* La consola siempre que reciba un cambio de estado de un semáforo, mostrará la información en la pantalla.
* Los semáforos solo deben responder a la señal SIGUSR1 enviada por otro semáforo.
* La consola de monitoreo solo debe responder a las señales Ctrl+C y Ctrl+Z.

## Uso
Para ejecutar correctamente el ejercicio, primero se debe ejecutar el programa de la consola central, seguido por cuatro ejecuciones independientes para cada programa de semaforo.  

      gcc main.c -o consola  
      ./consola 127.0.0.1  

      gcc semaforo.c -o semaforo  
      ./semaforo 127.0.0.1  
