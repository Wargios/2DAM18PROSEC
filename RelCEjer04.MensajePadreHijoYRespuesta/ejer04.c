/**
 *  Ejercicio 2
 Realiza un programa en C que cree un pipe en el que el PADRE envíe un mensaje al HIJO,
 es decir la información fluya del padre al hijo.
 */

#include <stdio.h> // Cabecera estándar E/S.
#include <stdlib.h> // system().
#include <unistd.h> // execl().
#include <string.h> // Manipulación de memoria.
#include <sys/types.h> // Tipos de datos.
#include <sys/wait.h> // wait().
#include <time.h>       /* time */

int main() {
	int fd[2]; // Tubería.
//	int rnd1 = rand() % 100;
//	srand(time(NULL));
//	int rnd2 = rand() % 100;

	char msgPadre[] = "Hola hijo."; // Mensaje.

	char msgHijo[] = "Adiós padre."; // Mensaje.

	char buffer[80];

	pid_t pid; // PID.

	pid = fork(); // Se crea el proceso hijo, guardando su PID.
	pipe(fd); //

	switch (pid) {

	case -1:
		printf(" Fallo en fork \n");
		exit(-1);
		break;

	case 0: //---------------------HIJO

		close(fd[1]); // Se cierra la escritura.
		read(fd[0], buffer, sizeof(buffer)); // Se lee el mensaje.
		printf("EL HIJO HA RECIBIDO EL MENSAJE DEL PADRE: %s\n", buffer);

		close(fd[0]); // Se cierra la lectura.
		//open(fd[1]); // abre escritura
		write(fd[1], msgHijo, sizeof(msgHijo)); // escribe mensaje a padre
		printf("EL HIJO HA ENVIADO UN MENSAJE AL PADRE...\n");
		break;

	default: //------------------------PADRE

		close(fd[0]); // Se cierra la lectura.
		write(fd[1], msgPadre, sizeof(msgPadre)); // Se escribe el mensaje.
		printf("EL PADRE HA ENVIADO UN MENSAJE AL HIJO...\n");
		wait(NULL); // Se espera al proceso hijo.

		close(fd[1]); // Se cierra la escritura.
		read(fd[0], buffer, sizeof(buffer)); // Se lee el mensaje.
		printf("EL PADRE HA RECIBIDO EL MENSAJE DEL HIJO: %s\n", buffer);

		break;

	}
	return 0;
}
/*
 *
 */
