/*
 * Padre con 3 hijos.
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
			printf("Soy el proceso padre con PID: %d.\n", getpid());
			sleep(2);

		} else {
			printf("Soy el hijo: %d, mi padre es: %d.\n", getpid(), getppid());
			sleep(2);
			exit(0);
		}
	}

	return 0;
}
