/*
 * Padre con 3 hijos, y cada hijo tiene 2.
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
	// VARIABLES
	pid_t pid; // PID.

	// DESARROLLO
	for (int contador = 1; contador <= 3; contador++) {
		pid = fork(); // Se crea un proceso hijo y se guarda el PID.

		if (pid) {
			printf("Soy el abuelo: %d.\n", getpid());
			sleep(2);

		} else {
			printf("\tSoy el padre %d: %d, mi padre es %d.\n", contador, getpid(), getppid());
			sleep(2);

			for (int contador2 = 1; contador2 <= 2; contador2++) {
				pid = fork(); // Se crea un proceso hijo y se guarda el PID.

				if (pid) {
					sleep(2);

				} else {
					printf("\t\tSoy el hijo %d: %d, mi padre %d es: %d.\n", contador2, getpid(), contador, getppid());
					sleep(2);
					exit(0);
				}
			}

			exit(0);
		}
	}

	return 0;
}
