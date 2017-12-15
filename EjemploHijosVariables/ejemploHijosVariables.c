#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	// VARIABLES
	pid_t pid, pid2, pid3; // PIDs.
	int valor = 0;

	// DESARROLLO
	pid = fork(); // Se crea un proceso hijo y se guarda el PID.

	if (pid == -1) { // ERROR.
		printf("Error. No se ha podido crear el proceso hijo...");
		exit(-1);
	}

	if (pid == 0) { // HIJO.
		int variable = 1;
		printf("Soy el proceso hijo 1.\n\tMi PID es: %d, el de mi padre es: %d.\n", getpid(), getppid());
		printf("\tEl valor de la variable es: %d.\n", variable);

	} else { // PADRE.
		wait(NULL); // Se espera al proceso hijo 1.
		pid2 = fork(); // Se crea un proceso hijo y se guarda el PID.

		if (pid2 == -1) { // ERROR.
			printf("Error. No se ha podido crear el proceso hijo...");
			exit(-1);
		}

		if (pid2 == 0) { // HIJO 2.
			valor = valor - 7;
			printf("Soy el proceso hijo 2.\n\tMi PID es: %d, el de mi padre es: %d.\n", getpid(), getppid());
			printf("\tEl valor es: %d.\n", valor);

		} else { // PADRE.
			wait(NULL); // Se espera al proceso hijo 2.
			pid3 = fork(); // Se crea un proceso hijo y se guarda el PID.

			if (pid3 == -1) { // ERROR.
				printf("Error. No se ha podido crear el proceso hijo...");
				exit(-1);
			}

			if (pid3 == 0) { // HIJO 3.
				valor = valor - 7;
				printf("Soy el proceso hijo 3.\n\tMi PID es: %d, el de mi padre es: %d.\n", getpid(), getppid());
				printf("\tEl valor es: %d.\n", valor);

			} else { // PADRE.
				wait(NULL); // Se espera al proceso hijo 3.
				printf("Soy el proceso padre.\n\tMi PID es: %d, el de mi padre es: %d.\n\tMi hijo 1: %d, terminó.\n\tMi hijo 2: %d, terminó.\n\tMi hijo 3: %d, terminó.\n", getpid(), getppid(), pid, pid2, pid3);
				printf("\tEl valor es: %d.\n", valor);
			}
		}
	}

	return 0;
}
