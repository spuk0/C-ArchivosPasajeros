#include <stdio.h>
#include <stdlib.h> /*system*/
#include <string.h>
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

/*menu*/
void menuPrincipal();
void menuVector();
void menuPasajEfectivo();
void menuRosarinos();
void menuPasajMayor();
void menuPasajTarjeta();

void inicializarProcesoLectura();

/*Punto "a" */
void vector();
void contadorPasajeros();
void generarVector();
void cerrarArchivo();

/*Punto "b" */
void pasajerosEfectivo();

/*Punto c*/
float calculoPorcentajeRosarinos(int, int);

/*Punto d*/
void procesarCodigosDestino();

/*Punto e*/
void listarPasajerosTarjetas();

int main(){
	inicializarProcesoLectura();
	menuPrincipal();
	
	return 0;
}

void menuPrincipal(){
	char repite = 1;
	int opcion = -1;
	do {
		system("cls");
		

		printf("\n\t\t\t\tMENU PRINCIPAL\n");
		printf("\n\t\t[1]. Cantidad de pasajeros por codigo de destino\n");
		printf("\t\t[2]. Pasajeros que destinan Villa Carlos Paz y abonan en efectivo\n");
		printf("\t\t[3]. Porcentaje de pasajeros que eligieron el destino Rosario\n");
		printf("\t\t[4]. Codigo de destino que tuvo mayor numero de pasajeros\n");
		printf("\t\t[5]. Lista de datos de los pasajeros que pagaron con tarjeta\n");
		printf("\t\t[6]. Salir\n");
		printf("\n\t\tIngrese su opcion: [ ]\b\b");
		scanf("%d", &opcion);
		
		switch (opcion) {
		
			case 1:
				menuVector();
				break;
				
			case 2:
				menuPasajEfectivo();
				break;
				
			case 3:
				menuRosarinos();
				break;
				
			case 4:
				menuPasajMayor();
				break;
				
			case 5:
				menuPasajTarjeta();
				break;
				
			case 6:
				repite = 0;
				break;
		}
		
	} while (repite);
}

void menuVector(){
	system("cls");
	vector();
	system("pause");
}

void menuPasajEfectivo(){
	system("cls");
	pasajerosEfectivo();
	system("pause");
}

void menuRosarinos(){
	system("cls");
	contadorPasajeros();
	float p;
	p=calculoPorcentajeRosarinos(rosario, total);
	printf("***Los pasajeros que destinan Rosario representan un %.2f porciento del total***\n\n", p);
	system("pause");
}

void menuPasajMayor(){
	system("cls");
	contadorPasajeros();
	generarVector();
	int i;
	for(i=1; i<=max; i++){
		/*Contador para usar en punto d junto al vector*/
		if (pasajerosXDestino[i]>auxMayCod){
			auxMayCod=pasajerosXDestino[i];
		}
	}
	printf("***El destino que tuvo mayor cantidad de pasajeros fue %s, de codigo %d y un total de %d pasajeros***\n\n", auxMayDest, auxCod, auxMayCod);
	system("pause");
}

void menuPasajTarjeta(){
	system("cls");
	listarPasajerosTarjetas();
	system("pause");
}

void inicializarProcesoLectura(){
	archivoColectivo = fopen("Colectivo.dat", "rb"); /*abri archivo, modo lectura*/
	
	bariloche=0;
	rosario=0;
	cataratas=0;
	carlosPaz=0;
	auxMayCod=0;
}

/*Empiezo punto a*/

void vector(){
	contadorPasajeros();
	generarVector();
	/*Encabezado*/
	printf("\t\t***Cantidad de pasajeros por codigo de destino***\n");
	printf("\nBariloche\t|\tRosario\t\t|\tCataratas del Iguazu   |Villa Carlos Paz|\n");
	/*Muestro los valores del vector*/
	int i;
	for (i=1; i<=max; i++){
		printf("%d pasajeros\t\t",pasajerosXDestino[i] );
	}
	printf("\n\n");
}

void contadorPasajeros(){
	
	fread(&regReservas, sizeof(tr_reservas), 1, archivoColectivo); /*leer cierto numero de elementos*/
	while(!feof(archivoColectivo)){ /*detectar elementos del archivo*/
	
		total=total+1;
		
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
	
	
}

void generarVector(){
	/*Asignacion de valor a posiciones del vector*/
	pasajerosXDestino[1]=bariloche; /*En la posicion 1, el vector vale lo que vale bariloche*/
	pasajerosXDestino[2]=rosario;
	pasajerosXDestino[3]=cataratas;
	pasajerosXDestino[4]=carlosPaz;
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
	
	printf("***%d pasajeros eligieron Villa Carlos Paz como destino y abonaron en efectivo***\n\n", carlosPazEfectivo);
}

/*Empiezo el punto c*/
float calculoPorcentajeRosarinos (int rosario, int total){
	porcentaje=(rosario*100)/total;
	return porcentaje;
}

/*Empiezo punto e*/
void listarPasajerosTarjetas(){
	tr_reservas regReservas;
	FILE * archivoColectivo;
	
	archivoColectivo = fopen("Colectivo.dat", "rb");
	printf("\t\t\t***Pasajeros que abonaron con tarjeta***");
	printf("\n\nPasajero Codigo\t\tNombre y apellido\t\tCodigo Destino\t\t\tImporte\n\n");
	
	fread(&regReservas, sizeof(tr_reservas), 1, archivoColectivo);
	while(!feof(archivoColectivo)){
		if(regReservas.tipoPago=='t'){
			printf("%d\t\t\t%s\t\t\t\t%d\t\t\t%.2f\n", regReservas.numPasaj, regReservas.nameApe, regReservas.codDestiny, regReservas.importe);
		}
			fread(&regReservas, sizeof(tr_reservas), 1, archivoColectivo);
	}
	cerrarArchivo();
}


void cerrarArchivo(){
	fclose(archivoColectivo);
	printf("\n\n");
}
