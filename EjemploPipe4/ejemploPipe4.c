#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
	// VARIABLES
	int fd[2]; // Tubería.
	pid_t pid; // PID.
	char saludoHijo[] = "Buenos días padre.\0"; // Mensaje hijo.
	char saludoPadre[] = "Buenos días hijo.\0"; // Mensaje padre.
	char buffer[80]; // Buffers de memoria.
	//int tamanhoSaludo = strlen(buffer); // Cantidad de bytes.

	// DESARROLLO
	pipe(fd); // Se crea la tubería.
	pid = fork(); // Se crea el proceso hijo, guardando su PID.

	switch (pid) {
	case -1: // ERROR.
		printf("Error. No se ha podido crear el proceso hijo...");
		exit(-1);
		break;

	case 0: // HIJO
		// Se reciben los datos del padre.
		//close(fd[1]); // Se cierra la escritura.
		read(fd[0], buffer, sizeof(buffer)); // Se leen los datos.
		printf("\tEL HIJO HA RECIBIDO UN MENSAJE DEL PADRE: %s\n", buffer);

		// Se envían los datos al padre.
		//close(fd[0]); // Se cierra la lectura.
		write(fd[1], saludoHijo, strlen(saludoHijo)); // Se escriben los datos.
		printf("\tEL HIJO HA ENVIADO UN MENSAJE AL PADRE...\n");
		break;

	default: // PADRE.
		// Envía los datos al hijo.
		//close(fd[0]); // Se cierra la lectura.
		write(fd[1], saludoPadre, sizeof(saludoPadre)); // Se escriben los datos.
		printf("EL PADRE HA ENVIADO UN MENSAJE AL HIJO...\n");
		wait(NULL); // Se espera al HIJO.
		//sleep(2);

		// Recibe los datos del hijo.
		//close(fd[1]); // Se cierra la escritura.
		read(fd[0], buffer, sizeof(buffer)); // Se leen los datos.
		printf("EL PADRE HA RECIBIDO UN MENSAJE DEL HIJO: %s\n", buffer);
		break;
	}

	return 0;
}
