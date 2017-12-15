/*
 * Lista el contenido del directorio actual y lo envía a un fichero, abre el editor gedit con el fichero generado
 * y ejecuta un comando que NO existe en el intérprete de comandos Linux.
 */

#include <stdio.h>  // Cabecera estándar E/S.
#include <stdlib.h> // system().

void main() {
	printf("Ejemplo de uso de system()");
	printf("\n\tListado del directorio actual y envío a un fichero: %d", system("ls > ficSalida "));
	printf("\n\tAbrimos con el gedit el fichero: %d", system("gedit ficsalida"));
	printf("\n\tEste comando es erróneo: %d", system("ged"));
	printf("\nFin programa del programa.\n");
}

/*
 * Esta función NO SE DEBE usar desde un programa con privilegios de administrador porque podría pasar que se
 * emplearan valores extraños para algunas variables de entorno y podrían comprometer la integridad del sistema.
 * En este caso se usa alguna de las funciones de exec().
 */
