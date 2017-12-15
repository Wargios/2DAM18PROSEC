/*
 * Jerarquía:
 *  1. ABUELO.
 *  2. PADRE.
 *  3. NIETO.
 *
 *  ABUELO envía mensaje a PADRE (tubería 1)
 *  	PADRE recibe mensaje de ABUELO (tubería 1)
 *  	PADRE envía mensaje a NIETO (tubería 2)
 *  		NIETO recibe mensaje de PADRE (tubería 2)
 *  		NIETO envía mensaje a PADRE (tubería 1)
 *  	PADRE recibe mensaje de NIETO (tubería 1)
 *  	PADRE envía mensaje a ABUELO (tubería 2)
 *  ABUELO recibe mensaje de PADRE (tubería 2)
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
	// VARIABLES
	pid_t pid, pid2; // PIDs de los procesos.
	int fd1[2]; // Tubería 1.
	int fd2[2]; // Tubería 2.
	char saludoAbuelo[] = "Saludos del abuelo."; // Mensaje abuelo.
	char saludoPadre[] = "Saludos del padre."; // Mensaje padre.
	char saludoNieto[] = "Saludos del nieto."; // Mensaje nieto.
	char buffer[80]; // Buffer de memoria.

	// DESARROLLO
	pipe(fd1); // Se crea la tubería 1.
	pipe(fd2); // Se crea la tubería 2.

	pid = fork(); // Se crea un primer proceso hijo.

	switch (pid) {
	case -1: // ERROR.
		printf("No se ha podido crear el proceso hijo...");
		exit(-1);
		break;

	case 0: // Primer hijo > PADRE (porque es el hijo del proceso original, el ABUELO).
		pid2 = fork(); // Se crea un segundo proceso hijo, el hijo del hijo, el nieto.

		switch (pid2) {
		case -1: // ERROR.
			printf("No se ha podido crear el proceso hijo del hijo.");
			exit(-1);
			break;

		case 0: // Segundo hijo > NIETO (porque es el hijo del proceso hijo del original, el PADRE).
			// Recibe los datos de su padre, el PADRE.
			close(fd2[1]); // Se cierra la escritura (tubería 2).
			read(fd2[0], buffer, sizeof(buffer)); // Se lee el mensaje (tubería 2).
			printf("\t\tNIETO HA RECIBIDO UN MENSAJE DE PADRE: %s\n", buffer);

			// Envía datos a su padre, el PADRE.
			close(fd1[0]); // Se cierra la lectura (tubería 1).
			write(fd1[1], saludoNieto, strlen(saludoNieto)); // Se escribe el mensaje (tubería 1).
			printf("\t\tNIETO HA ENVIADO UN MENSAJE A PADRE...\n");
			break;

		default: // PADRE.
			// Recibe los datos de su padre, el ABUELO.
			close(fd1[1]); // Se cierra la escritura (tubería 1).
			read(fd1[0], buffer, sizeof(buffer)); // Se lee el mensaje (tubería 1).
			printf("\tPADRE HA RECIBIDO UN MENSAJE DE ABUELO: %s\n", buffer);

			// Envía datos a su hijo, el NIETO.
			close(fd2[0]); // Se cierra la lectura (tubería 2).
			write(fd2[1], saludoPadre, strlen(saludoPadre)); // Se escribe el mensaje (tubería 2).
			printf("\tPADRE HA ENVIADO UN MENSAJE A NIETO...\n");
			wait(NULL);

			// Recibe los datos de su hijo, el NIETO.
			close(fd1[1]); // Se cierra la escritura.
			read(fd1[0], buffer, sizeof(buffer)); // Se lee el mensaje (tubería 1).
			printf("\tPADRE HA RECIBIDO UN MENSAJE DE NIETO: %s\n", buffer);

			// Envía datos a su padre, el ABUELO.
			close(fd2[0]); // Se cierra la lectura (tubería 2).
			write(fd2[1], saludoPadre, strlen(saludoPadre)); // Se escribe el mensaje (tubería 2).
			printf("\tPADRE HA ENVIADO UN MENSAJE A ABUELO...\n");
			break;
		}
		break;

	default: // ABUELO.
		// Envía datos a su hijo, el PADRE.
		close(fd1[0]); // Se cierra la lectura (tubería 1).
		write(fd1[1], saludoAbuelo, strlen(saludoAbuelo)); // Se escribe el mensaje (tubería 1).
		printf("ABUELO HA ENVIADO UN MENSAJE A PADRE...\n");
		wait(NULL);

		// Recibe datos del NIETO.
		close(fd2[1]); // Se cierra la escritura (tubería 2).
		read(fd2[0], buffer, sizeof(buffer)); // Se lee el mensaje (tubería 2).
		printf("ABUELO HA RECIBIDO UN MENSAJE DE PADRE: %s\n", buffer);
		break;
	}

	return 0;
}
