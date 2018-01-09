/**
 *  Ejercicio 2
 Realiza un programa en C que cree un pipe en el que el PADRE envíe un mensaje al HIJO,
 es decir la información fluya del padre al hijo.
 */

#include <stdio.h> // Cabecera estándar E/S.
#include <stdlib.h> // system().
#include <unistd.h> // execl().
#include <string.h> // Manipulación de memoria.
#include <sys/types.h> // Tipos de datos.
#include <sys/wait.h> // wait().

int main() {
	int fd[2]; // Tubería.
	pid_t pid; // PID.
	char saludoHijo[] = "Buenos días padre."; // Mensaje.
	int tamanhoSaludo = strlen(saludoHijo); // Cantidad de bytes.
	char buffer[tamanhoSaludo]; // Buffer de memoria.

	pipe(fd); // Se crea la tubería.
	pid = fork(); // Se crea el proceso hijo, guardando su PID.

	switch (pid) {

	case -1:
		printf(" Fallo en fork \n");
		exit(-1);
		break;

	case 0:
		close(fd[0]); // Se cierra la lectura.
		write(fd[1], saludoHijo, tamanhoSaludo); // Se escribe el mensaje.
		printf("El HIJO HA ENVIADO UN MENSAJE AL PADRE...\n");
		break;

	default:
		wait(NULL); // Se espera al proceso hijo.
		close(fd[1]); // Se cierra la escritura.
		read(fd[0], buffer, tamanhoSaludo); // Se lee el mensaje.
		printf("EL PADRE HA RECIBIDO EL MENSAJE DEL HIJO: %s\n", buffer);
		break;
	}

	return 0;
}

