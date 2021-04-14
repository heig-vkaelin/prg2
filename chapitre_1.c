//
// Created by Valentin on 23.02.2021.
//

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#define GENERIC_ABS(type) \
type type##_abs(type x)  {  \
  return x > 0 ? x : -x;  \
}

GENERIC_ABS(int)

int ex1_3(void) {
	int n;

	printf("1. %d\n", int_abs(2));
	printf("2. %d\n", int_abs(-2));
	printf("3. %d\n", int_abs('A'));

	n = -2;
	printf("4. %d\n", int_abs(n + 1));

	n = -2;
	printf("5. %d", int_abs(n++));
	printf(" %d\n", n);

	n = -2;
	printf("6. %d", int_abs(++n));
	printf(" %d\n", n);

	n = -2;
	printf("7. %d", abs(++n));
	printf(" %d\n", n);

	return EXIT_SUCCESS;
}

#define INT_SIZE sizeof(int) * 8

typedef unsigned short ushort;

ushort getBit(ushort pos, int n) {
	assert(pos < INT_SIZE);
	return n >> pos & 1;
}

int ex1_5(void) {
	for (ushort pos = 0; pos < INT_SIZE; ++pos) {
		printf("bit %hu = %hu\n", pos, getBit(pos, 10));
	}

	return EXIT_SUCCESS;
}

int *setBit(ushort pos, ushort bitValue, int *n) {
	assert(pos < INT_SIZE);
	assert(bitValue == 0 || bitValue == 1);
	{ // Variante 1
		const int MASK_1 = 1 << pos,
			MASK_2 = bitValue << pos;
		*n = (*n & ~MASK_1) | MASK_2;
	}
//	{ // Variante 2
//		const int MASK = 1 << pos;
//		*n ^= (-bitValue ^ *n) & MASK;
//	}
//	{ // Variante 3
//		const int MASK = 1 << pos;
//		*n = bitValue ? *n | MASK : *n & ~MASK; // Mais utilise ?:
//	}

	return n;
}

int ex1_6(void) {
	int n = 0;
	printf("n = %d\n", n);
	printf("n = %d\n", *setBit(0, 1, &n));
	printf("n = %d\n", *setBit(0, 0, &n));
	printf("n = %d\n", *setBit(1, 1, &n));

	for (ushort pos = 0; pos < INT_SIZE; ++pos) {
		setBit(pos, 1, &n);
	}
	printf("n = %d\n", n);

	int m = -1;
	printf("m = %d\n", *setBit(31, 0, &m));

	return EXIT_SUCCESS;
}

short lowestOderSetBit(int n) {
	short order;
	if (n == 0) {
		order = -1;
	} else {
		for (ushort pos = 0; pos < INT_SIZE; ++pos) {
			// Si le bit courant est à 1
			if (n & 1 << pos) { // ouf if (n >> pos & 1)
				order = (short) pos;
				break;
			}
		}
	}
	return order;
}

int ex1_7(void) {
	for (int n = 0; n <= 10; ++n) {
		printf("lowestOrderSetBit(%d) = %hd\n", n, lowestOderSetBit(n));
	}

	return EXIT_SUCCESS;
}

#define INT32_T_SIZE sizeof(int32_t) * 8

void decimalToBinary(int32_t n, int8_t binary[]) {
	for (size_t i = INT32_T_SIZE; i > 0; --i) {
		binary[i - 1] = n & 1;
		n >>= 1;
	}
}

void display_ex1_8(const int8_t binary[], size_t size) {
	for (size_t i = 0; i < size; ++i) {
		printf("%d", binary[i]);
	}
	printf("\n");
}

void test_ex1_8(int32_t n) {
	int8_t binary[INT32_T_SIZE];
	decimalToBinary(n, binary);
	display_ex1_8(binary, INT32_T_SIZE);
}

int ex1_8(void) {
	printf("12345678901234567890123456789012\n");
	printf("--------------------------------\n");
	test_ex1_8(0);
	test_ex1_8(1);
	test_ex1_8(10);
	test_ex1_8(-1);
	test_ex1_8(INT32_MIN);
	test_ex1_8(INT32_MAX);

	return EXIT_SUCCESS;
}

int ex1_10(void) {
	/* Résultat attendu:
	 * 0377
	 * * FF
    * +###255
    * 1.235e+001
	 * 12.345
    * 12.3450
	 */

	int n = 255;
	double x = 12.345;
	printf("%#o\n", n);
	printf("%X\n", n);
	printf("%s%d\n", "+###", n);
	printf("%.3e\n", x);
	printf("%g\n", x);  // ou printf("%.3f\n", x)
	printf("%#g\n", x); // ou printf("%.4f\n", x)

	return EXIT_SUCCESS;
}

#define PRINT_UNSIGNED(i) printf(#i " = %" PRIuMAX "\n", (uintmax_t) (i))

int ex1_11(void) {
	/* Résultat attendu:
	 * i = 1
	 * j = 4294967295
	 */

	size_t i = 1;
	uint32_t j = UINT32_MAX;

	PRINT_UNSIGNED(i);
	PRINT_UNSIGNED(j);

	return EXIT_SUCCESS;
}

int ex1_12(void) {
	int n;
	char c;

	printf("Donnez un nombre entier et un caractere :");
	if (scanf("%d %c", &n, &c) == 2) {
		printf("n = %d, c = %c\n", n, c);
	}
	fflush(stdin); // pas portable, only Windows

	return EXIT_SUCCESS;
}

#define TAILLE_NOM 20

int ex1_13(void) {
	char nom[TAILLE_NOM + 1];
	char format[10];

	sprintf(format, " %%%d[^\n]", TAILLE_NOM);
	printf("Entrez votre nom (%d caract. max) :", TAILLE_NOM);
	scanf(format, nom);
	fflush(stdin);

	printf("Votre nom est \"%s\"\n", nom);

	return EXIT_SUCCESS;
}
