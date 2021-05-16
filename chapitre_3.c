//
// Created by Valentin on 20.04.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#define TAILLE_MAX_NOM 20
typedef char Nom[TAILLE_MAX_NOM + 1];
typedef uint8_t Taille;
typedef enum {
	BLEU, VERT, GRIS, MARRON, NOIR
} CouleurYeux;
const char* const COULEURS_YEUX[] = {"bleus", "verts", "gris", "marron", "noirs"};

typedef struct {
	Nom nom;
	Taille taille;
	CouleurYeux couleurYeux;
} Personne;

void afficher_ex3_2_2(const Personne* adr) {
	printf("Nom    : %s\n", adr->nom);
	printf("Taille : %" PRIu8 "\n", adr->taille); // ou alors %hu pour short unsigned
	printf("Yeux   : %s\n", COULEURS_YEUX[adr->couleurYeux]);
}

void afficher_ex3_2_1(Personne p) {
	afficher_ex3_2_2(&p);
}

int ex3_2(void) {
	Personne p = {.nom="Toto", .taille=180, .couleurYeux=BLEU};
	afficher_ex3_2_1(p);
	printf("\n");
	afficher_ex3_2_2(&p);
	printf("\n");

	return EXIT_SUCCESS;
}

typedef const char* NomV2;

typedef struct {
	NomV2 nom;
	Taille taille;
	CouleurYeux couleurYeux;
} PersonneV2;

void afficher_ex3_3(const PersonneV2* p) {
	printf("Nom    : %s\n", p->nom);
	printf("Taille : %" PRIu8 "\n", p->taille);
	printf("Yeux   : %s\n", COULEURS_YEUX[p->couleurYeux]);
}

void afficherPersonnes(const PersonneV2 tab[], size_t n) {
	for (size_t i = 0; i < n; ++i) {
		afficher_ex3_3(&tab[i]); // ou afficher_ex3_3(tab + i)
		printf("\n");
	}
}

int ex3_3(void) {
	const PersonneV2 PERSONNES[] = {
		{.nom="Paul", .taille=180, .couleurYeux=BLEU},
		{.nom="Pierre", .taille=175, .couleurYeux=VERT},
		{.nom="Jean-Jacques", .taille=182, .couleurYeux=MARRON}
	};
	const size_t TAILLE = sizeof(PERSONNES) / sizeof(PersonneV2);
	afficherPersonnes(PERSONNES, TAILLE);

	return EXIT_SUCCESS;
}

#define FORMAT_DATE "%02" PRIu8 ".%02" PRIu8 ".%04" PRIu16

typedef struct {
	uint8_t jour;
	uint8_t mois;
	uint16_t annee;
} Date;

bool estBissextile(uint16_t annee) {
	return annee % 400 == 0 || (annee % 4 == 0 && annee % 100);
}

uint8_t nbJoursDansMois(uint8_t mois, uint16_t annee) {
	// Version du prof: tableau static contenant le nbr de jour par mois + check
	// bissextile
	switch (mois) {
		case 2:
			return estBissextile(annee) ? 29 : 28;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		default:
			return 31;
	}
}

const char* toString(const Date* d) {
	char* str = (char*) calloc(11, sizeof(char));
	if (str) {
		sprintf(str, FORMAT_DATE, d->jour, d->mois, d->annee);
	}
	return str;
}

Date lendemain(const Date* d) {
	Date lendemain;
	if (d->jour != nbJoursDansMois(d->mois, d->annee)) {
		lendemain = (Date) {(uint8_t) (d->jour + 1), d->mois, d->annee};
	} else if (d->mois < 12) {
		lendemain = (Date) {1, (uint8_t) (d->mois + 1), d->annee};
	} else {
		lendemain = (Date) {1, 1, (uint16_t) (d->annee + 1)};
	}
	return lendemain;
}

void test_ex3_4(const Date* d) {
	Date leLendemain = lendemain(d);
	const char* str1 = toString(d);
	const char* str2 = toString(&leLendemain);
	printf("Le lendemain du %s est le %s\n", str1, str2);
	free((char*) str1);
	free((char*) str2);
}

int ex3_4(void) {
	test_ex3_4(&(Date) {28, 2, 2000});
	test_ex3_4(&(Date) {29, 2, 2000});
	test_ex3_4(&(Date) {30, 11, 2000});
	test_ex3_4(&(Date) {31, 12, 2000});

	return EXIT_SUCCESS;
}

typedef enum {
	A, B, C
} Permis;
const char PERMIS[] = {'A', 'B', 'C'};
const char* const NATIONALITES[] = {"Etranger", "Suisse"};

typedef struct {
	Nom nom;
	int swiss;
	union {
		double taux;
		Permis permis;
	};
} PersonneV3;

void afficher_ex3_6(const PersonneV3* p) {
	printf("Nom           : %s\n", p->nom);
	printf("Nationalite   : %s\n", NATIONALITES[p->swiss]);
	if (p->swiss) {
		printf("Taux activite : %g%%\n", p->taux);
	} else {
		printf("Type permis   : %c\n", PERMIS[p->permis]);
	}
	printf("\n");
}

int ex3_6(void) {
	PersonneV3 p1 = {.nom="Toto", .swiss=true, .taux=80};
	PersonneV3 p2 = {.nom="Titi", .swiss=false, .permis=C};

	afficher_ex3_6(&p1);
	afficher_ex3_6(&p2);

	return EXIT_SUCCESS;
}
