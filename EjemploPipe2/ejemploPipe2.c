/*
 * El proceso padre escribe información en un pipe y ésta es leída por el proceso hijo.
 */

#include <stdio.h> // Cabecera estándar E/S.
#include <stdlib.h> // system().
#include <unistd.h> // execl().
#include <string.h> // Manipulación de memoria.
#include <sys/types.h> // Tipos de datos.
#include <sys/wait.h> // wait().

int main(void) {
	// VARIABLES
	int fd[2]; // Tubería.
	pid_t pid; // PID.
	char saludoHijo[] = "Buenos días hijo."; // Mensaje.
	int tamanhoSaludo = strlen(saludoHijo); // Cantidad en bytes.
	char buffer[80]; // Buffer de memoria.

	// DESARROLLO
	pipe(fd); // Se crea la tubería.
	pid = fork(); // Se crea el proceso hijo, guardando su PID.

	switch (pid) {
	case -1: // ERROR.
		printf("No se ha podido crear el proceso hijo...");
		exit(-1);
		break;

	case 0: // HIJO: Recibe los datos.
		close(fd[1]); // Se cierra la lectura.
		read(fd[0], buffer, sizeof(buffer)); // Se escribe el mensaje.
		printf("El HIJO HA RECIBIDO EL MENSAJE DEL PADRE: %s", buffer);
		break;

	default: // PADRE: Envía los datos.
		close(fd[0]); //cierra el descriptor de entrada (escritura)
		write(fd[1], saludoHijo, tamanhoSaludo); //descriptor de entrada para escribir en el pipe
		printf("El PADRE HA ENVIADO UN MENSAJE AL HIJO...\n");
		wait(NULL); //Espera al proceso hijo
		break;
	}

	return 0;
}
