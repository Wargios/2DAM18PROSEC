/*
 * Ejecuta el comando “ls –l” del intérprete de comandos de Linux y busca el ejecutable en la ruta “/bin/ls”.
 */

#include <stdio.h> // Cabecera estándar E/S.
#include <unistd.h> // execl().

void main() {
	printf("Ejemplo de uso de execl()\n");
	printf("Los archivos del directorio son:\n");
	execl("/bin/ls", "ls", "-l", (char *) NULL); // Toma el programa a ejecutar en una lista de cadenas terminada en null.
	printf("¡Da igual lo que pongamos aquí que esto NO se ejecuta!\n");
	// Porque el proceso deja de ejecutar las instrucciones del script y comienza a ejecutar instrucciones del
	// nuevo programa (ls –l).
}
