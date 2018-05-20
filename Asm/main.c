/*
	FUNDAMENTOS DE INFRAESTRUCTURA TECNOL�GICA
	Ramón Aljandro Arias Rivera - 20171814
	Nicolás Meléndez
	Albert Adolfo Molano Cubillos - 201713848
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define BYTE_TO_BINARYpATTERN "%c%c%c%c%c%c%c%c"
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
		// Invalido
		else if (op != 0) {
			printf("Opci? invalida.\n");
		}
	}

	// Terminar
	printf("\nPrograma terminado.\n");
	return 0;
}
/*
	Procedimiento que escribe s empezando en el bit p de V
*/
void escribir(unsigned char *V, unsigned char *s, int p) {
	
	
	_asm {

	
		mov	BYTE PTR [ebp-1], 128; 00000080H
	
		mov	BYTE PTR [ebp-3], 1
		mov	eax, s

		push	eax

		call	_strlen

		mov	DWORD PTR [ebp-32], eax

		mov	DWORD PTR [ebp-12], 0
		jmp	SHORT  L4_main
		 L2_main:
		mov	ecx, DWORD PTR [ebp-12]
		add	ecx, 1
		mov	DWORD PTR [ebp-12], ecx
		 L4_main:
		mov	edx, DWORD PTR [ebp-12]
		cmp	edx, DWORD PTR [ebp-32]
		jge	SHORT  L3_main
		mov	eax, DWORD PTR s
		add	eax, DWORD PTR [ebp-12]
		movzx	ecx, BYTE PTR[eax]
		sub	ecx, 48; 00000030H
		mov	edx, DWORD PTR s
		add	edx, DWORD PTR [ebp-12]
		mov	BYTE PTR[edx], cl

		jmp	SHORT  L2_main
		 L3_main:
		
		mov	DWORD PTR [ebp-20], 0

		mov	eax, DWORD PTR p
		cdq
		and	edx, 7
		add	eax, edx
		sar	eax, 3
		mov	DWORD PTR [ebp-8], eax
		mov	DWORD PTR [ebp-24], 0
		jmp	SHORT  L7_main
		L5_main:
		mov	eax, DWORD PTR [ebp-8]
		add	eax, 1
		mov	DWORD PTR [ebp-8], eax
		mov	ecx, DWORD PTR [ebp-24]
		add	ecx, 1
		mov	DWORD PTR [ebp-24], ecx
		 L7_main:
		cmp	DWORD PTR [ebp-24], 3
		jge	 L1_main

		mov	BYTE PTR [ebp-1], 128; 00000080H

		movsx	edx, BYTE PTR [ebp-3]
		cmp	edx, 1
		jne	SHORT  L11_main

		mov	eax, DWORD PTR p
		and	eax, -2147483641; 80000007H
		jns	SHORT  L17_main
		dec	eax
		or eax, -8; fffffff8H
		inc	eax
		 L17_main:
		mov	DWORD PTR [ebp-28], eax

		jmp	SHORT  L12_main
		 L11_main:

		mov	DWORD PTR [ebp-28], 0
		 L12_main:

		mov	ecx, DWORD PTR [ebp-28]
		mov	DWORD PTR [ebp-16], ecx
		jmp	SHORT  L10_main
		 L8_main:
		mov	edx, DWORD PTR [ebp-16]
		add	edx, 1
		mov	DWORD PTR [ebp-16], edx
		 L10_main:
		cmp	DWORD PTR [ebp-16], 8
		jge	 L9_main

		mov	eax, DWORD PTR [ebp-20]
		cmp	eax, DWORD PTR [ebp-32]
		jne	SHORT  L13_main

			
		jmp	 L9_main
		 L13_main:


		movzx	edx, BYTE PTR [ebp-1]
		mov	ecx, DWORD PTR [ebp-16]
		sar	edx, cl
		mov	BYTE PTR [ebp-2], dl

			
		movsx	eax, BYTE PTR [ebp-2]
		xor eax, 255; 000000ffH
		mov	ecx, DWORD PTR V
		add	ecx, DWORD PTR [ebp-8]
		movzx	edx, BYTE PTR[ecx]
		and edx, eax
		mov	eax, DWORD PTR V
		add	eax, DWORD PTR [ebp-8]
		mov	BYTE PTR[eax], dl

		mov	ecx, DWORD PTR s
		add	ecx, DWORD PTR [ebp-20]
		movzx	edx, BYTE PTR[ecx]
		test	edx, edx
		jne	SHORT  L15_main
		mov	DWORD PTR [ebp-36], 0
		jmp	SHORT  L16_main
		 L15_main:
		mov	DWORD PTR [ebp-36], 255; 000000ffH
		 L16_main:
		mov	al, BYTE PTR [ebp-36]
		mov	BYTE PTR [ebp-4], al

		movsx	ecx, BYTE PTR [ebp-2]
		movsx	edx, BYTE PTR [ebp-4]
		and ecx, edx
		mov	eax, DWORD PTR V
		add	eax, DWORD PTR [ebp-8]
		movzx	edx, BYTE PTR[eax]
		or edx, ecx
		mov	eax, DWORD PTR V
		add	eax, DWORD PTR [ebp-8]
		mov	BYTE PTR[eax], dl
		mov	BYTE PTR [ebp-3], 0
		mov	ecx, DWORD PTR [ebp-20]
		add	ecx, 1
		mov	DWORD PTR [ebp-20], ecx
		jmp	 L8_main
		 L9_main:
		jmp	 L5_main
		 L1_main:
		xor eax, eax
		mov	esp, ebp
		pop	ebp
		ret

			_strlen :

		push  ecx; save and clear out counter
			xor   ecx, ecx

			_strlen_next :

		cmp[edi], 0
			jz    _strlen_null

			inc   ecx
			inc   edi
			jmp   _strlen_next

			_strlen_null :

		mov   eax, ecx

			pop   ecx
			ret 0

	}


}

/*
	Procedimiento que lee l bits de V desde la posición p y los escribe
	como chars en s
*/
void leer(unsigned char *V, unsigned char *s, int p, int l) {
	

	_asm
	{
	mov	[ebp-1], 128		; 00000080H

	mov [ebp-2], 1

	mov	eax, p
	cdq
	and	edx, 7
	add	eax, edx
	sar	eax, 3
	mov	[ebp-16], eax

	mov	DWORD PTR [ebp-12], 0
	mov	eax, [ebp-16]
	mov	DWORD PTR [ebp-24], eax
	mov	DWORD PTR [ebp-20], 0
	jmp	SHORT  LN4_main
 LN2_main:
	mov	ecx, DWORD PTR [ebp-24]
	add	ecx, 1
	mov	DWORD PTR [ebp-24], ecx
	mov	edx, DWORD PTR [ebp-20]
	add	edx, 1
	mov	DWORD PTR [ebp-20], edx
 LN4_main:
	cmp	DWORD PTR [ebp-20], 4
	jge	 LN1_main
	mov	BYTE PTR [ebp-1], 128		; 00000080H
	movsx	eax, BYTE PTR[ebp-2]
	cmp	eax, 1
	jne	SHORT  LN8_main
	mov	ecx, DWORD PTR p
	and	ecx, -2147483641			; 80000007H
	jns	SHORT  LN14_main
	dec	ecx
	or	ecx, -8					; fffffff8H
	inc	ecx
 LN14_main:
	mov	DWORD PTR [ebp-28], ecx

		jmp	SHORT  LN9_main
 LN8_main:

	mov	DWORD PTR [ebp-28], 0
 LN9_main:

		mov	edx, DWORD PTR [ebp-28]
	mov	DWORD PTR [ebp-8], edx
	jmp	SHORT  LN7_main
 LN5_main:
	mov	eax, DWORD PTR [ebp-8]
	add	eax, 1
	mov	DWORD PTR [ebp-8], eax
 LN7_main:
	cmp	DWORD PTR [ebp-8], 8
	jge	SHORT  LN6_main

		mov	ecx, DWORD PTR [ebp-12]
	cmp	ecx, DWORD PTR l
	jne	SHORT  LN10_main

		jmp	SHORT  LN6_main
 LN10_main:

	movzx	edx, BYTE PTR [ebp-1]
	mov	ecx, DWORD PTR [ebp-8]
	sar	edx, cl
	mov	BYTE PTR [ebp-3], dl

		mov	eax, DWORD PTR V
	add	eax, [ebp-16]
	movzx	ecx, BYTE PTR [eax]
	movsx	edx, BYTE PTR [ebp-3]
	and	ecx, edx
	je	SHORT  LN12_main
	mov	DWORD PTR [ebp-32], 49			; 00000031H
	jmp	SHORT  LN13_main
 LN12_main:
	mov	DWORD PTR [ebp-32], 48			; 00000030H
 LN13_main:
	mov	eax, DWORD PTR s
	add	eax, DWORD PTR [ebp-12]
	mov	cl, BYTE PTR [ebp-32]
	mov	BYTE PTR [eax], cl

		mov	BYTE PTR[ebp-2], 0

		mov	edx, DWORD PTR [ebp-12]
	add	edx, 1
	mov	DWORD PTR [ebp-12], edx

		jmp	SHORT  LN5_main
 LN6_main:

	mov	eax, [ebp-16]
	add	eax, 1
	mov	[ebp-16], eax
	jmp	 LN2_main
 LN1_main:

	xor	eax, eax
	mov	esp, ebp
	pop ebp
	ret 0
	}
}
