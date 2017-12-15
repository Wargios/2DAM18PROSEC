#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	// VARIABLES
	int pid; // PID.

	// DESARROLO
	pid = fork(); // Se crea un proceso hijo y se guarda el PID.

	switch (pid) {
	case -1: // ERROR.
		printf("No se ha podido crear el proceso hijo\n");
		break;

	case 0: // HIJO.
		for (int contador = 0; contador <= 10; contador++) {
			printf("Soy el hijo.\n");
		}
		break;

	default: // PADRE.
		for (int contador = 0; contador <= 10; contador++) {
			printf("Soy el padre.\n");
		}
		wait(NULL); // Se espera al proceso hijo.
		printf("Mi hijo ya ha terminado.\n");
		break;
	}

	return 0;
}
