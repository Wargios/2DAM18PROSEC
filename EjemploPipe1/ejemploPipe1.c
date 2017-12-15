/*
 * El proceso hijo escribe información en un pipe y ésta es leída por el proceso padre.
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
	char saludoHijo[] = "Buenos días padre."; // Mensaje.
	int tamanhoSaludo = strlen(saludoHijo); // Cantidad de bytes.
	char buffer[tamanhoSaludo]; // Buffer de memoria.

	// DESARROLLO
	pipe(fd); // Se crea la tubería.
	pid = fork(); // Se crea el proceso hijo, guardando su PID.

	switch (pid) {
	case -1: // ERROR.
		printf("Error. No se ha podido crear el proceso hijo...");
		exit(-1);
		break;

	case 0: // HIJO: Envía los datos.
		close(fd[0]); // Se cierra la lectura.
		write(fd[1], saludoHijo, tamanhoSaludo); // Se escribe el mensaje.
		printf("El HIJO HA ENVIADO UN MENSAJE AL PADRE...");
		break;

	default: // PADRE: Recibe los datos.
		wait(NULL); // Se espera al proceso hijo.
		close(fd[1]); // Se cierra la escritura.
		read(fd[0], buffer, tamanhoSaludo); // Se lee el mensaje.
		printf("\nEL PADRE HA RECIBIDO EL MENSAJE DEL HIJO: %s", buffer);
		break;
	}

	return 0;
}
