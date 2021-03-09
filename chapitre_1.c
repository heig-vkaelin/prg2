//
// Created by Valentin on 23.02.2021.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

unsigned short getBit(unsigned short pos, int n) {
	return ((unsigned) n >> pos) & 1u;
}

int ex1_5() {
	printf("Pos: 0, n: 5 => %hu\n", getBit(0, 5));
	printf("Pos: 1, n: 5 => %hu\n", getBit(1, 5));
	printf("Pos: 2, n: 5 => %hu\n", getBit(2, 5));

	return EXIT_SUCCESS;
}

int *setBit(unsigned short pos, unsigned short bitValue, int *n) {
	int yolo = (int) (((unsigned) *n & ~(1u << pos)) | ((unsigned) bitValue << pos));
	n = &yolo;
	return n;
}

int ex1_6() {
	// TODO: wtf is this
	int n = 7;
	n = setBit(1, 0, &n);
	printf("Valeur de n: %d", n);

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
