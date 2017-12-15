#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	// VARIABLES
	pid_t pid; // PID.

	// DESARROLLO
	pid = fork(); // Se crea un proceso hijo y se guarda el PID.

	if (pid == -1) { // ERROR.
		printf("Error. No se ha podido crear el proceso hijo...");
		exit(-1);

	} else if (pid == 0) { // HIJO.
		printf("Soy el proceso hijo.\n\tMi PID es: %d\n\tEl PID de mi padre es: %d\n", getpid(), getppid());

	} else { // PADRE.
		wait(NULL); // Se espera al hijo.
		printf("Soy el proceso padre.\n\tMi PID es %d\n\tEl PID de mi padre es: %d\n\tMi hijo: %d, terminó.\n", getpid(), getppid(), pid);
	}

	return 0;
}
