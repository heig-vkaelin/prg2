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

typedef struct element {
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
