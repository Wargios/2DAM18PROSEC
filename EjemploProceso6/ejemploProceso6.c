#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	// VARIABLES
	int entero = 6;
	pid_t pid; // PIDs.

	// DESARROLLO.
	pid = fork(); // Se crea un proceso hijo y se guarda el PID.

	if (pid == -1) { // ERROR.
		printf("Error. No se ha podido crear el proceso hijo...");
		exit(-1);
	}

	if (pid == 0) { // HIJO.
		printf("Soy el proceso hijo.\n\tMi PID es: %d, el de mi padre es: %d.\n", getpid(), getppid());
		entero = entero - 5;
		printf("\tLa variable entero tiene el valor: %d.\n", entero);

	} else { // PADRE.
		wait(NULL); // Se espera al proceso hijo.
		printf("Soy el proceso padre.\n\tMi PID es: %d, el de mi padre es: %d.\n\tMi hijo: %d, terminó.\n", getpid(), getppid(), pid);
		entero = entero + 5;
		printf("\tLa variable entero iene el valor: %d.\n", entero);

	}

	return 0;
}
