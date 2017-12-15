/*
 * Abuelo > Padre > Nieto.
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	// VARIABLES
	pid_t pid, pidPadre, pidNieto, pid2; // PIDs.

	// DESARROLLO
	pid = fork(); // Se crea un proceso hijo, en este caso el padre, y se guarda el PID.

	if (pid == -1) { // ERROR.
		printf("No se ha podido crear el proceso hijo...");
		exit(-1);
	}

	if (pid == 0) { // PADRE.
		pid2 = fork(); // Se crea un proceso hijo, en este caso el nieto, y se guarda el PID.

		switch (pid2) {
		case -1: // ERROR.
			printf("Error. No se ha podido crear el proceso hijo...");
			exit(-1);
			break;

		case 0: // NIETO.
			printf("Soy el proceso NIETO.\n\tMi PID es: %d, el de mi padre, el PADRE, es: %d.\n", getpid(), getppid());
			break;

		default: // PADRE.
			pidNieto = wait(NULL);
			printf("Soy el proceso PADRE.\n\tMi PID es: %d, el de mi padre, el ABUELO, es: %d.\n\tMi hijo, el NIETO: %d, terminó.\n", getpid(), getppid(), pidNieto);
		}

	} else { // ABUELO.
		pidPadre = wait(NULL); // Se espera al proceso hijo, en este caso el PADRE.
		printf("Soy el proceso ABUELO.\n\tMi PID es: %d.\n\tMi hijo, el PADRE: %d, terminó.\n", getpid(), pidPadre);
	}

	return 0;
}
