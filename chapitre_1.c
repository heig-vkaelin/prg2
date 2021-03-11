//
// Created by Valentin on 23.02.2021.
//

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define INT_SIZE sizeof(int) * 8

typedef unsigned short ushort;

ushort getBit(ushort pos, int n) {
	assert(pos < INT_SIZE);
	return n >> pos & 1;
}

int ex1_5() {
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

int ex1_6() {
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
	unsigned short pos = 0;
	while (pos < sizeof(n) * CHAR_BIT) {
		if (getBit(pos, n)) {
			return (short) pos;
		}
		pos++;
	}
	return -1;
}

int ex1_7() {
	printf("%d", lowestOderSetBit(256));

	return EXIT_SUCCESS;
}

void decimalToBinary(int32_t n, int8_t binary[]) {
	int index = 32 - 1;

	while (index >= 0) {
		binary[index] = (unsigned) n & 1u;
		index--;
		n = (unsigned) n >> 1u;
	}
}

int ex1_8() {
	int8_t binary[32];

	decimalToBinary(7, binary);

	return EXIT_SUCCESS;
}
