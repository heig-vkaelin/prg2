//
// Created by Valentin on 25.05.2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	char* tmp = to;
	if (!size) return tmp;

	while (*to) to++;
	while ((*to++ = *from++) != '\0') {
		if (--size == 0) {
			*to = '\0';
			break;
		}
	}
	return tmp;
}

int ex4_5(void) {
	char to[10] = "";
	const char* from = "ABC";

	for (size_t i = 1; i <= 4; ++i) {
		strncat(to, from, i);
		PRINT(to);
	}

	return EXIT_SUCCESS;
}

char* strchr(const char* s, int c) {
	for (; *s != '\0'; ++s)
		if (*s == c)
			return (char*) s;

	return NULL;
}

int ex4_7(void) {
	char test[10] = "abcdEFghij";
	char aTrouver = 'd';

	char* pos = strchr(test, aTrouver);

	printf("Char après %c: %c", aTrouver, *++pos);


	return EXIT_SUCCESS;
}

char* concatNom(const char* prenom, const char* nom) {
	char* resultat = (char*) calloc(strlen(prenom) + strlen(nom) + 2, sizeof(char));
	if (resultat) {
		strcpy(resultat, prenom);
		strcat(resultat, " ");
		strcat(resultat, nom);
	}
	return resultat;
}

#define TAILLE_MAX_PRENOM 20
#define TAILLE_MAX_NOM 30
#define TAILLE_MAX_CHAINE_CONTROLE 15

int ex4_8(void) {
	char prenom[TAILLE_MAX_PRENOM + 1];
	char nom[TAILLE_MAX_NOM + 1];

	char chaineControlePrenom[TAILLE_MAX_CHAINE_CONTROLE + 1];
	char chaineControleNom[TAILLE_MAX_CHAINE_CONTROLE + 1];

	const char* const MOTIF = " %%%d[^\n]";
	sprintf(chaineControlePrenom, MOTIF, TAILLE_MAX_PRENOM);
	sprintf(chaineControleNom, MOTIF, TAILLE_MAX_NOM);

	printf("Entrez le prenom (max %u caract.) :", TAILLE_MAX_PRENOM);
	scanf(chaineControlePrenom, prenom);
	fflush(stdin);

	printf("Entrez le nom (max %u caract.) :", TAILLE_MAX_NOM);
	scanf(chaineControleNom, nom);
	fflush(stdin);

	char* prenom_nom = concatNom(prenom, nom);
	if (prenom_nom) {
		printf("La chaine \"%s\" comporte %u caracteres.\n",
				 prenom_nom, (unsigned) strlen(prenom_nom));
		free(prenom_nom);
	}

	return EXIT_SUCCESS;
}

void inverser_1(char* s) {
	char* begin = s;
	char* end = s + strlen(s) - 1;
	char tmp;
	while (begin < end) {
		tmp = *end;
		*end-- = *begin;
		*begin++ = tmp;
	}
}

char* inverser_2(const char* s) {
	size_t len = strlen(s);
	char* chaine = (char*) calloc(len + 1, sizeof(char));
	if (!chaine) {
		return (char*) s;
	}

	for (size_t i = 0; i < len / 2; ++i) {
		chaine[i] = s[len - 1 - i];
		chaine[len - 1 - i] = s[i];
	}

	return chaine;
}

int ex4_9(void) {
	char str[] = "Valentin";
	printf("%s\n", str);
	inverser_1(str);
	printf("%s\n\n", str);

	char str2[] = "Valentin";
	printf("%s\n", str2);
	char* str2_inv = inverser_2(str2);
	printf("%s\n", str2);
	printf("%s\n", str2_inv);

	return EXIT_SUCCESS;
}
