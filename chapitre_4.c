//
// Created by Valentin on 25.05.2021.
//

#include <stdlib.h>
#include <stdio.h>

#define PRINT(STR) printf(#STR " = %s\n", STR)

char* strcpy(char* to, const char* from) {
	char* tmp = to;
	while ((*to++ = *from++) != '\0');
	return tmp;
}

int ex4_2(void) {
	char s1[10];
	char* s2;
	const char* s3;

	s2 = strcpy(s1, "");
	PRINT(s1);
	PRINT(s2);

	strcpy(s1, "ABC");
	PRINT(s1);
	PRINT(s2);

	s3 = "DEF";
	strcpy(s1, s3);
	PRINT(s1);

	strcpy(s1, strcpy(s1, "ABC"));
	PRINT(s1);

	return EXIT_SUCCESS;
}

char* strncpy(char* to, const char* from, size_t size) {
	size_t i;
	for (i = 0; i < size && from[i] != '\0'; ++i)
		to[i] = from[i];
	for (; i < size; ++i)
		to[i] = '\0';
	return to;
}

int ex4_3(void) {
	{
		const char* from = "AB";
		char to[] = "XXXXXX";
		for (size_t i = 0; i <= 3; ++i) {
			strncpy(to, from, i);
			PRINT(to);
		}
	}

	{
		const char* from = "AB";
		char to[] = "XXXXXX";
		const size_t TAILLE = 6;
		strncpy(to, from, 4);
		for (size_t i = 0; i <= TAILLE; ++i)
			printf("%d ", (int) to[i]);
	}

	return EXIT_SUCCESS;
}

char* strcat(char* to, const char* from) {
	char* tmp = to;
	while (*to) to++;
	while ((*to++ = *from++) != '\0');
	return tmp;
}

int ex4_4(void) {
	char to[10] = ""; // A besoin de contenir un '\0'
	const char* from = "ABC";
	char* s;

	strcat(to, from);
	PRINT(to);

	s = strcat(to, "DEF");
	PRINT(to);
	PRINT(s);

	return EXIT_SUCCESS;
}

char* strncat(char* to, const char* from, size_t size) {
	size_t i = 0;
	char* tmp = to;
	while (*to)
		to++;
	while (i++ != size && (*to++ = *from++));
	*to = 0;
	return tmp;
}

int ex4_5(void) {
	char from[] = "test je te jure";
	char to[] = "Ceci est un ";

	printf("From: %s To: %s \n", from, to);
	strncat(to, from, 4);
	printf("From: %s To: %s \n", from, to);

	return EXIT_SUCCESS;
}
