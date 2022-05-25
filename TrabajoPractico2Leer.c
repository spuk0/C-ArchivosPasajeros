#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define max 4

typedef char string [30];
typedef int tArregloInt [max]; /*vector, declaracion variable*/
typedef struct{
	int numPasaj;
	string nameApe;
	int codDestiny;
	char tipoPago;
	float importe;
}tr_reservas;

tr_reservas regReservas;
FILE *archivoColectivo;
int bariloche, rosario, cataratas, carlosPaz, total;
int carlosPazEfectivo, totalPasajeros;
float porcentaje;
short auxMayCod;
int auxCod;
string auxMayDest= " ";

tArregloInt pasajerosXDestino;

void inicializarProcesoLectura();

/*Punto "a" */
void vector();
void contadorPasajeros();
void generarVector();
void cerrarArchivo();

/*Punto "b" */
void pasajerosEfectivo();

/*Punto c*/
float calculoPorcentajeRosarinos();
void mostrarPorcentajeRosarinos();

/*Punto d*/
void procesarCodigosDestino();

/*Punto e*/
void listarPasajerosTarjetas();

int main(){
	
	inicializarProcesoLectura();
	printf("Cantidad de pasajeros por codigo de destino:\n\n");
	vector(pasajerosXDestino);
	
	pasajerosEfectivo();
	
	mostrarPorcentajeRosarinos();
	
	printf("\n\nEl destino que tuvo mayor cantidad de pasajeros fue %s, de codigo %d y un total de %d pasajeros", auxMayDest, auxCod, auxMayCod);
	
	listarPasajerosTarjetas();
	
}

void inicializarProcesoLectura(){
	archivoColectivo = fopen("Colectivo.dat", "rb"); /*abri archivo, modo lectura*/
	
	bariloche=0;
	rosario=0;
	cataratas=0;
	carlosPaz=0;
	
	auxMayCod=0;
}

void cerrarArchivo(){
	fclose(archivoColectivo);
	printf("\n\n");
}
	
void vector(pasajerosXDestiny){
	contadorPasajeros();
	generarVector(pasajerosXDestiny);
	
}

void contadorPasajeros(){
	
	fread(&regReservas, sizeof(tr_reservas), 1, archivoColectivo); /*leer cierto numero de elementos*/
	while(!feof(archivoColectivo)){ /*detectar elementos del archivo*/
			switch (regReservas.codDestiny){
				case 1:
					bariloche=bariloche+1; /*Cuento para tener la variable bariloche a mi disposicion*/
					fread(&regReservas, sizeof(tr_reservas), 1, archivoColectivo);
					auxCod=1;
					strcpy(auxMayDest, "Bariloche" );
					break;
				case 2:
					rosario=rosario+1; /*Cuento para tener la variable rosario a mi disposicion*/
					fread(&regReservas, sizeof(tr_reservas), 1, archivoColectivo);
					auxCod=2;
					strcpy(auxMayDest, "Rosario" );
					break;
				case 3:
					cataratas=cataratas+1; /*Cuento para tener la variable cataratas a mi disposicion*/
					fread(&regReservas, sizeof(tr_reservas), 1, archivoColectivo);
					auxCod=3;
					strcpy(auxMayDest, "Cataratas del Iguazu" );
					break;
				case 4:
					carlosPaz=carlosPaz+1; /*Cuento para tener la variable carlos paz a mi disposicion*/
					fread(&regReservas, sizeof(tr_reservas), 1, archivoColectivo);
					auxCod=4;
					strcpy(auxMayDest, "Villa Carlos Paz" );
					break;
			}
	
	}
	
	total=bariloche+rosario+cataratas+carlosPaz;
	
}

void generarVector(pasajerosXDesty){
	/*Asignacion de valor a posiciones del vector*/
	pasajerosXDestino[1]=bariloche; /*En la posicion 1, el vector vale lo que vale bariloche*/
	pasajerosXDestino[2]=rosario;
	pasajerosXDestino[3]=cataratas;
	pasajerosXDestino[4]=carlosPaz;
	
	
	
	/*Encabezado*/
	printf("\nBariloche\t|\tRosario\t\t|\tCataratas del Iguazu   |Villa Carlos Paz|\n");
	
	/*Muestro los valores del vector*/
	int i;
	for (i=1; i<=max; i++){
		printf("%d pasajeros\t\t",pasajerosXDestino[i] );
	/*punto d*/
		if (pasajerosXDestino[i]>auxMayCod){
			auxMayCod=pasajerosXDestino[i];
		}
	}
}

/*Empiezo punto b*/

void pasajerosEfectivo(){
	archivoColectivo = fopen("Colectivo.dat", "rb");
	carlosPazEfectivo=0;
	
	fread(&regReservas, sizeof(tr_reservas), 1, archivoColectivo); /*leer cierto numero de elementos*/
	while(!feof(archivoColectivo)){ /*detectar elementos del archivo*/
	
	if(regReservas.codDestiny==4&& regReservas.tipoPago=='e'){
		
		carlosPazEfectivo=carlosPazEfectivo+1;
	}
	
	fread(&regReservas, sizeof(tr_reservas), 1, archivoColectivo);
}
	
	printf("\n\n%d pasajeros eligieron Villa Carlos Paz como destino y abonaron en efectivo", carlosPazEfectivo);
}

/*Empiezo el punto c*/
float calculoPorcentajeRosarinos (){
	porcentaje=(rosario*100)/total;
	return porcentaje;
}
void mostrarPorcentajeRosarinos(){
	printf("\n\nEl porcentaje de pasajeros que optaron por el destino Rosario es %.2f porciento", calculoPorcentajeRosarinos());
}

/*Empiezo punto e*/
void listarPasajerosTarjetas(){
	tr_reservas regReservas;
	FILE * archivoColectivo;
	
	archivoColectivo = fopen("Colectivo.dat", "rb");
	printf("\n\n\nPasajeros que abonaron con tarjeta:");
	printf("\nPasajero Codigo\t\tNombre y apellido\tCodigo Destino\n\n");
	
	fread(&regReservas, sizeof(tr_reservas), 1, archivoColectivo);
	while(!feof(archivoColectivo)){
		if(regReservas.tipoPago=='t'){
			printf("%d\t\t\t%s\t\t\t%d\n", regReservas.numPasaj, regReservas.nameApe, regReservas.codDestiny);
		}
			fread(&regReservas, sizeof(tr_reservas), 1, archivoColectivo);
	}
	cerrarArchivo();
}
