#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	// VARIABLES
	pid_t pid, pid2, hijoPid2;

	// DESARROLLO
	pid = fork(); // Se crea un proceso hijo y se guarda el PID.

	if (pid == -1) { // ERROR.
		printf("Error. No se ha podido crear el proceso hijo...");
		exit(-1);

	} else if (pid == 0) { // HIJO.
		printf("Soy el proceso hijo.\n\tMi PID es: %d, el de mi padre es: %d.\n", getpid(), getppid());

	} else { // PADRE.
		pid2 = fork(); // Se crea un segundo proceso hijo y se guarda el PID.

		if (pid2 == -1) { // ERROR.
			printf("Error. No se ha podido crear el proceso hijo...");
			exit(-1);

		} else if (pid2 == 0) { // HIJO 2.
			printf("Soy el proceso hijo 2.\n\tMi PID es: %d, el de mi padre es: %d.\n", getpid(), getppid());
		}

		else { // PADRE.
			hijoPid2 = wait(NULL); // Se espera al proceso hijo 2.
			printf("Soy el proceso padre.\n\tMi PID es: %d, el de mi padre es: %d.\n\tMi hijo: %d terminó.\n",getpid(), getppid(), hijoPid2);
		}
	}

	return 0;
}
