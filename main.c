/*  Equipo 3:
    Andrés Barragán Salas               A01026567
    Carla Pérez Gavilán del Castillo    A01023033

    Actividad 6: Sockets y Señales - Consola de Monitoreo
*/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TCP_PORT 8000
#define NUM_SEMAFOROS 4

int cliente_semaforo; //Accesso global a un semaforo cliente dado
int interrupcion; //Interrupción actual de consola ([o]Ninguna, [1]Interrupción Rojo, [2]Interrupción Intermitente)

// Manejadores de funciones
void stopInterruption(int signal);
void intermitentInterruption(int signal);
void consoleInterruption(int signal);

// Declaración de funciones
void printCurrentState(int i);

int main(int argc, const char * argv[])
{
    //Ignorar señales
    signal(SIGTSTP, consoleInterruption);
    signal(SIGINT, consoleInterruption);

    struct sockaddr_in direccion;
    char buffer[1000];
    
    int servidor;
    
    ssize_t leidos, escritos;
    int continuar = 1;
    pid_t pid;
    
    if (argc != 2) {
        printf("Use: %s IP_Servidor \n", argv[0]);
        exit(-1);
    }
    
    // Crear el socket
    servidor = socket(PF_INET, SOCK_STREAM, 0);
    // Enlace con el socket
    inet_aton(argv[1], &direccion.sin_addr);
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    
    bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));
    
    // Escuhar
    listen(servidor, NUM_SEMAFOROS);
    
    escritos = sizeof(direccion);
    
    // Almacenar la información de los semaforos para poder comunicarlos
    int cliente[NUM_SEMAFOROS];
    char semaforo[NUM_SEMAFOROS][50];
    ssize_t pidInputSizes[NUM_SEMAFOROS];
    // Aceptar conexiones para la cantidad requerida de semaforos
    for (int i = 0; i<NUM_SEMAFOROS; ++i) {
        cliente[i] = accept(servidor, (struct sockaddr *) &direccion, &escritos);
        printf("Aceptando conexiones en %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
        
        pid = fork();
        
        if (pid == 0) {
            // Opciones para gestionar señales
            cliente_semaforo = cliente[i]; 
            signal(SIGTSTP, stopInterruption);
            signal(SIGINT, intermitentInterruption);

            close(servidor);
            if (cliente_semaforo >= 0) {
                // Escuchar los cambios de  estado de los semaforos
                while(leidos = read(cliente[i], &buffer, sizeof(buffer))) {
                    printCurrentState(i); //Imprimir el estado actuald de los semaforos
                }
            }
            
            close(cliente_semaforo);
        }
        else {
            // Leer los PIDs de los semaforos y almacenarlos en el proceso principal
            pidInputSizes[i] = read(cliente[i], &semaforo[i], sizeof(semaforo[i]));
        }
    }

    if (pid > 0) {
        //Comunicar a los semaforos el PID del semaforo con quien se deben comunicar
        for (int i = 0; i < NUM_SEMAFOROS; ++i) {
            int nextClient = (i + 1) % NUM_SEMAFOROS;
            write(cliente[i], &semaforo[nextClient], pidInputSizes[nextClient]);
        }
        //Iniciar el ciclo de los semaforos
        char init_message[] = "START"; 
        write(cliente[0], &init_message, sizeof(init_message));

        while (wait(NULL) != -1);
        
        // Cerrar sockets
        close(servidor);
        
    }
    return 0;
}

/*  Manejador de señales para indicar los semaforos un cambio total a ROJO
    @param signal: id de señal recibida
*/
void stopInterruption(int signal) {
    char interruption[] = "STOP"; 
    write(cliente_semaforo, &interruption, sizeof(interruption));
}

/*  Manejador de señales para indicar al semaforos un cambio total a INTERMITENTE
    @param signal: id de señal recibida
*/
void intermitentInterruption(int signal) {
    char interruption[] = "INTERMITENT"; 
    write(cliente_semaforo, &interruption, sizeof(interruption));
}

/*  Metodo para imprimir el estado de los semaforos cuando un semaforo dado cambia su estado a verde
    @param trafficLight: número de semáforo que cambió su estado a VERDE
*/
void printCurrentState(int trafficLight) {
    printf("Cambio de estado\n");
    printf("----------------\n");
    for (int i=0; i<NUM_SEMAFOROS; ++i) {
        if (i == trafficLight)
            printf("Semaforo %d: VERDE\n", i+1);
        else 
            printf("Semaforo %d: ROJO\n", i+1);
    }
    printf("\n");
}

/*  Manejador de señales para indicar por consola que una señal de interrupción fue recibida
    @param signal: id de señal recibida
*/
void consoleInterruption(int signal) {
    char state[15];

    // Manejar los tipos de señales cuando son mandados por primera y segunda ocasión
    if (signal == 20 && interrupcion != 1) {
        interrupcion = 1;
        strcpy(state, "ROJO");
    } else if (signal == 2 && interrupcion != 2) {
        interrupcion = 2;
        strcpy(state, "INTERMITENTE");
    } else {
        interrupcion = 0;
        printf("\nReanudando\n\n");
        return;
    }

    printf("\nInterrupción\n");
    printf("------------\n");
    for (int i=0; i<NUM_SEMAFOROS; ++i) {
        printf("Semaforo %d: %s\n", i+1, state);
    }
}
