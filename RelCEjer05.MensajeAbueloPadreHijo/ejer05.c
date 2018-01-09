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

int main() {
	int fd[2]; // Tubería.
	char saludoHijo[] = "Buenos días padre."; // Mensaje.
	int tamanhoSaludo = strlen(saludoHijo); // Cantidad de bytes.
	char buffer[tamanhoSaludo]; // Buffer de memoria.

	pid_t pid_nieto, pid_hijo; // PID.

	pid_hijo = fork(); // Se crea el proceso hijo, guardando su PID.
	pipe(fd); //

	switch (pid_hijo) {

	case -1:
		printf(" Fallo en fork \n");
		exit(-1);
		break;

	case 0: //---------------------HIJO (crea nieto)
		pid_nieto = fork(); // Se crea el proceso nieto, guardando su PID.

		switch (pid_nieto) {

		case -1:
			printf(" Fallo en fork \n");
			exit(-1);
			break;

		case 0: //------------------------NIETO
//			printf(
//					"Soy el proceso nieto.\n\tMi PID es: %d, el de mi padre es: %d.\n",
//					getpid(), getppid());

			break;

		default: //------------------------HIJO
			wait(NULL); // Se espera al proceso hijo.
			printf(
					"Soy el proceso hijo.\n\tMi PID es: %d, el de mi padre es: %d.\n",
					getpid(), getppid());

			break;
		}
		break;

	default: //------------------------PADRE
		wait(NULL); // Se espera al proceso hijo.
		printf(
				"Soy el proceso padre.\n\tMi PID es: %d, el de mi padre es: %d.\n",
				getpid(), getppid());

		break;

	}
	return 0;
}
/*
 *
 */
