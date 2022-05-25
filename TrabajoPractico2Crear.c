#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define max 4

typedef char string [30];
typedef struct{
	int numPasaj;
	string nameApe;
	int codDestiny;
	char tipoPago;
	float importe;
}tr_reservas;

tr_reservas regReservas;
FILE *archivoColectivo;

char opcion = 's';

void crearArchivo();
void escribirReservas();

int main(){
	crearArchivo();
	
	return 0;
}

void crearArchivo (){
	/*Limpio pantalla sin borrar datos almacenados*/
	system("cls");
	/* Abrir archivo en el modo escribir */
	archivoColectivo = fopen("Colectivo.dat", "wb");
	
	while (opcion == 's'){		
		escribirReservas();
		/* Grabar los datos en el archivo */
		fwrite(&regReservas, sizeof(tr_reservas), 1, archivoColectivo);
		printf("\nHecho!");
		printf("\n\nDesea ingresar otra reserva? s/n:");
		scanf("%c", &opcion);
	}
	
	
	/* Cerrar archivo */
	fclose(archivoColectivo);
}

void escribirReservas(){
	fflush(stdin);
	printf("Numero de pasajero: ");
	scanf("%d", &regReservas.numPasaj);
	fflush(stdin);
	printf("Nombre y apellido: ");
	scanf("%[^\n]s", &regReservas.nameApe);
	printf("Codigo de destino (1-Bariloche, 2-Rosario, 3-Cataratas del Iguazu, 4-Villa Carlos Paz): ");
	scanf("%d", &regReservas.codDestiny);
	fflush(stdin);
	printf("Tipo de pago (e-efectivo, t-tarjeta): ");
	scanf("%c", &regReservas.tipoPago);
	printf("Importe: ");
	scanf("%f", &regReservas.importe);	
	fflush(stdin);
	
}
