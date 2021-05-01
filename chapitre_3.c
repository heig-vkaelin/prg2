//
// Created by Valentin on 20.04.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

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

void afficher_personnes(PersonneV2* personnes[], size_t n) {
	for (size_t i = 0; i < n; ++i) {
		afficher_ex3_3(personnes[i]);
	}
}

int ex3_3(void) {
	PersonneV2 paul = {.nom="Paul", .taille=180, .yeux=BLEU};
	PersonneV2 pierre = {.nom="Pierre", .taille=175, .yeux=VERT};
	PersonneV2 jean_jacques = {.nom="Jean-Jacques", .taille=182, .yeux=MARRON};
//	afficher_ex3_3(&paul);

	PersonneV2* personnes[] = {&paul, &pierre, &jean_jacques};
	afficher_personnes(personnes, 3);

	return EXIT_SUCCESS;
}
