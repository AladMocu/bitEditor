/*
	FUNDAMENTOS DE INFRAESTRUCTURA TECNOL�GICA
	Ramón Aljandro Arias Rivera - 20171814
	Nicolás Meléndez
	Albert Adolfo Molano Cubillos - 201713848
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                   \
	(byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'),                      \
		(byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'),                  \
		(byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'),                  \
		(byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')

void escribir(unsigned char *V, unsigned char *s, int p);
void leer(unsigned char *V, unsigned char *s, int p, int l);
unsigned char calcularMascara(int p);
int main(int argc, char *argv[]) {
	// Variables
	int op;
	int l, p;
	unsigned char *V;
	unsigned char *s;
	unsigned char *a;

	// Inicialización
	V = (unsigned char *)calloc(100, sizeof(char));
	s = (unsigned char *)calloc(17, sizeof(char));
	a = (unsigned char *)calloc(7, sizeof(char));
	// Mensaje inicial
	printf("PROYECTO 1 - INFRATEC.");

	// Loop hasta terminar
	op = 3;
	while (op != 0) {
		// Se pregunta al usuario cual opcion desea realizar
		printf(
			"\n\n* Indique la modalidad\n\t0: Terminar\n\t1: Escribir\n\t2: "
			"Leer\n\n");
		printf("Modalidad: ");
		scanf("%d", &op);

		// Escribir
		if (op == 1) {
			printf("Acci? %d: Escribir\n\n", op);

			// Se reciben los valores de s y p
			printf("Escriba s: ");
			scanf("%s", s);

			printf("Se leyeron los siguientes bits: %s\n", s);
			printf("Escriba p: ");
			scanf("%d", &p);

			// Se escribe s desde el bit p de V
			escribir(V, s, p);
			unsigned char *a;

			printf("\nSe escribia s desde el bit p de V.\n");
			//			printf("Se leyeron los siguientes bits: %s\n", V);
		}
		// Leer
		else if (op == 2) {
			printf("Acci? %d: Leer\n\n", op);

			// Se reciben los valores de l y p
			printf("Escriba l: ");
			scanf("%d", &l);
			printf("Escriba p: ");
			scanf("%d", &p);

			// Se leen l bits de V desde la posición p y se escriben como chars
			// en s
			s = (unsigned char *)calloc(17, sizeof(char));
			leer(V, s, p, l);
			printf("Se leyeron los siguientes bits: %s\n", s);

		}
		else if (op != 0) {
			printf("Opci? invalida.\n");
		}
	}
	printf("\nPrograma terminado.\n");
	return 0;
}
/*
	Procedimiento que escribe s empezando en el bit p de V
*/
void escribir(unsigned char *V, unsigned char *s, int p) {
	unsigned char mask = 0b10000000;// creo una mascara necesaria para las operaciones bitwise
	char primera = 1; // defino un indicador para saber si estoy en el primer byte (el cual tendria desplazamiento)
	int x = strlen((char *)s); //obtengo la longitud de la entrada
	for (int i = 0; i < x; i++) {	//convierto la entrada en su valor binario desde el valor del caracter
		s[i] -= 48;
	}
	int pos = 0; // creo un segundo identificador
	for (int j = p / 8, k = 0; k < 3; j++, k++) {
		mask = 0b10000000;// reinicio la mascara en caso de corrupcion
		int cap; //defino un entero relacionado a la posicion inicial dento del bit
		if (primera == 1) { //en caso de estar en el primer byte calculo el desplazamiento
			cap = (p % 8);
		} else { //si no es asi inicio en el comienzo del byte
			cap = 0;
		}
		for (int i = cap; i < 8; i++) { // empiezo a trabajar en el byte desplazado lo calculado anteriormente
			if (pos == x) { //si llegue a la longitud no continuo
				break;
			}
			char tMask = mask >> i; //deplazo la mascara a la posicion requerida
			V[j] &= (tMask ^ 0b11111111); // limpio el bit a trabajar
			char y = s[pos] == 0 ? 0 : 0b11111111; //defino el estado que debe tomar el bit 
			V[j] |= ((tMask)&y);   //ubico el estado usando la mascara
			primera = 0; // defino que ya no es la primera vez que ingreso
			pos += 1; //aumento los indicadores
		}
	}
}

/*
	Procedimiento que lee l bits de V desde la posición p y los escribe
	como chars en s
*/
void leer(unsigned char *V, unsigned char *s, int p, int l) {
	unsigned char mask = 0b10000000; //defino la mascara
	char primera = 1; //creo un identificador
	int pos2 = p / 8; //defino la posicion en el vector del primer byte a leer
	int pos = 0; //creo un indicadores
	for (int j = p / 8, k = 0; k < 4; j++, k++) {//defino un for que aumenta el byte en trabajo, revisando los 4 bytes siguientes
		mask = 0b10000000; //reinicio la mascara e caso de corrupcion
		int cap;//defino un indicador de desplazamiento
		if (primera == 1) {// si es la primera entrada calculo el desplazamiento en el byte
			cap = (p % 8);
		} else { //si no defino el punto de inicio como 0 
			cap = 0;
		}
		for (int i = cap; i < 8; i++) {//mientras este dentro del byte
			if (pos == l) {//si llegue a la longitud de lectura salgo
				break;
			}
			char tMask = mask >> i; //desplazo la mascara
			s[pos] = (V[pos2] & tMask) != 0 ? 49 : 48; // defino si el valor debe ser '0' || '1'
			primera = 0;//indico que no es la primera vez que dentro
			pos += 1;//aumento la posicion en s
		}
		pos2 += 1;//si cumpli el byte aumento un byte
	}
}
