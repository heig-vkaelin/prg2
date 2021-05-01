//
// Created by Valentin on 20.04.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

typedef enum {
	BLEU, VERT, GRIS, MARRON, NOIR
} Couleur;

char* STR_COULEURS[5] = {"bleus", "verts", "gris", "marrons", "noirs"};

typedef struct personne {
	char nom[20];
	uint8_t taille;
	Couleur yeux;
} Personne;

void afficher_ex3_2_1(const Personne p) {
	printf("%s mesure %dcm et a les yeux %s.\n",
			 p.nom, p.taille, STR_COULEURS[p.yeux]);
}

void afficher_ex3_2_2(const Personne* p) {
	printf("%s mesure %dcm et a les yeux %s.\n",
			 p->nom, p->taille, STR_COULEURS[p->yeux]);
}

int ex3_2(void) {
	Personne toto = {.nom="Toto", .taille=180, .yeux=BLEU};
	afficher_ex3_2_1(toto);
	afficher_ex3_2_2(&toto);

	return EXIT_SUCCESS;
}

typedef struct personneV2 {
	char* nom;
	uint8_t taille;
	Couleur yeux;
} PersonneV2;

void afficher_ex3_3(const PersonneV2* p) {
	printf("Nom    : %s\n", p->nom);
	printf("Taille : %d\n", p->taille);
	printf("Yeux   : %s\n\n", STR_COULEURS[p->yeux]);
}

void afficher_personnes(const PersonneV2* personnes[], size_t n) {
	for (size_t i = 0; i < n; ++i) {
		afficher_ex3_3(personnes[i]);
	}
}

int ex3_3(void) {
	PersonneV2 paul = {.nom="Paul", .taille=180, .yeux=BLEU};
	PersonneV2 pierre = {.nom="Pierre", .taille=175, .yeux=VERT};
	PersonneV2 jean_jacques = {.nom="Jean-Jacques", .taille=182, .yeux=MARRON};
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
