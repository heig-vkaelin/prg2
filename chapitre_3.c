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

typedef struct personneV2 {
	char* nom;
	uint8_t taille;
	CouleurYeux couleurYeux;
} PersonneV2;

void afficher_ex3_3(const PersonneV2* p) {
	printf("Nom    : %s\n", p->nom);
	printf("Taille : %d\n", p->taille);
	printf("Yeux   : %s\n\n", COULEURS_YEUX[p->couleurYeux]);
}

void afficher_personnes(const PersonneV2* personnes[], size_t n) {
	for (size_t i = 0; i < n; ++i) {
		afficher_ex3_3(personnes[i]);
	}
}

int ex3_3(void) {
	PersonneV2 paul = {.nom="Paul", .taille=180, .couleurYeux=BLEU};
	PersonneV2 pierre = {.nom="Pierre", .taille=175, .couleurYeux=VERT};
	PersonneV2 jean_jacques = {.nom="Jean-Jacques", .taille=182, .couleurYeux=MARRON};
//	afficher_ex3_3(&paul);

	const PersonneV2* personnes[] = {&paul, &pierre, &jean_jacques};
	afficher_personnes(personnes, 3);

	return EXIT_SUCCESS;
}

typedef struct date {
	uint8_t jour;
	uint8_t mois;
	uint16_t annee;
} Date;

bool estBissextile(uint16_t annee) {
	return annee % 400 == 0 || (annee % 4 == 0 && annee % 100 != 0);
}

uint8_t nbJoursParMois(uint8_t noMois, uint16_t annee) {
	switch (noMois) {
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

void afficherDate(const Date* date) {
	printf("%02d.%02d.%04d", date->jour, date->mois, date->annee);
}

Date lendemain(Date date) {
//	Date* nouvelleDate = (Date*) malloc(sizeof(Date));
	if (++date.jour > nbJoursParMois(date.mois, date.annee)) {
		date.jour = 1;
		++date.mois;
	}
	if (date.mois > 12) {
		date.mois = 1;
		++date.annee;
	}
	return date;
}

void afficher_lendemain(const Date* date) {
	printf("Le lendemain du ");
	afficherDate(date);
	Date prochainJour = lendemain(*date);
	printf(" est le ");
	afficherDate(&prochainJour);
	printf("\n");
}

int ex3_4(void) {
	Date date = {30, 4, 2016};
	afficher_lendemain(&date);

	return EXIT_SUCCESS;
}
