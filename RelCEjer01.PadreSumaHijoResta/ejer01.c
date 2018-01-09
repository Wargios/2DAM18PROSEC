/**
 *  Ejercicio 1
 Realiza un programa en C que cree un proceso (tendremos 2 procesos uno padre y otro hijo).
 El programa definirá una variable entera y le dará el valor 6. El proceso padre incrementará
 dicho valor en 5 y el hijo restará 5. Se deben mostrar los valores en pantalla.

 */

#include <stdio.h> // Cabecera estándar E/S.
#include <stdlib.h> // system().
#include <unistd.h> // execl().
#include <string.h> // Manipulación de memoria.
#include <sys/types.h> // Tipos de datos.
#include <sys/wait.h> // wait().

int main() {
	pid_t pid;
	int variable;
	variable = 6;
	pid = fork();

	switch (pid) {

	case -1:
		printf(" Fallo en fork \n");
		exit(-1);
		break;

	case 0:
		printf(" Soy el proceso hijo \n");
		variable -= 5;
		break;

	default:
		printf("Soy el proceso padre \n");
		variable += 5;
		break;
	}
	printf("Variable = %d \n",variable);
	return 0;
}

