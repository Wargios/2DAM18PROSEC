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

	pid_t pid, pid2, pid3; // PID.

	pid = fork(); // Se crea el proceso hijo, guardando su PID.

	switch (pid) {

	case -1:
		printf(" Fallo en fork \n");
		exit(-1);
		break;

	case 0:
		printf(
				"Soy el proceso hijo 1.\n\tMi PID es: %d, el de mi padre es: %d.\n",
				getpid(), getppid());
		break;

	default:
		wait(NULL);
		pid2 = fork(); // Se crea un segundo proceso hijo y se guarda el PID.

		switch (pid2) {

		case -1:
			printf(" Fallo en fork \n");
			exit(-1);
			break;

		case 0:
			printf(
					"Soy el proceso hijo 2.\n\tMi PID es: %d, el de mi padre es: %d.\n",
					getpid(), getppid());
			break;

		default:
			wait(NULL); // Se espera al proceso hijo 2.
			pid3 = fork();

			switch (pid3) {

			case -1:
				printf(" Fallo en fork \n");
				exit(-1);
				break;

			case 0:
				printf(
						"Soy el proceso hijo 3.\n\tMi PID es: %d, el de mi padre es: %d.\n",
						getpid(), getppid());
				break;

			default:

				wait(NULL); // Se espera al proceso hijo 3.
				printf(
						"Soy el proceso padre.\n\tMi PID es: %d, el de mi padre es: %d.\n",
						getpid(), getppid());

				break;

			}

			return 0;
		}
	}
}
