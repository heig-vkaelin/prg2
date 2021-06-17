//
// Created by Valentin Kaelin on 09.06.21.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int ex5_1(void) {
	FILE* f = fopen("../data/ex5_1.txt", "r");
	if (!f) {
		printf("Ouverture du fichier \"ex5_1.txt\" impossible.\n");
		return EXIT_FAILURE;
	}
	int n;
	while ((fscanf(f, "%d", &n)) != EOF)
		printf("%d\n", n);
	fclose(f);
	return EXIT_SUCCESS;
}

#define TAILLE_MAX_NOM 20
#define TAILLE_MAX_PRENOM 15

typedef char Nom[TAILLE_MAX_NOM + 1];
typedef char Prenom[TAILLE_MAX_PRENOM + 1];
typedef unsigned short Age;

typedef struct {
	Nom nom;
	Prenom prenom;
	Age age;
} Personne;

void saisie(char* chaine, size_t taille) {
	fgets(chaine, (int) taille + 1, stdin);
	fflush(stdin);
	for (size_t i = 0; i < taille; ++i) {
		if (chaine[i] == '\n') {
			chaine[i] = '\0';
			break;
		}
	}
}

int ex5_2(void) {
	FILE* fichier = fopen("../data/personnes.dat", "wb");
	if (!fichier) {
		printf("Desole! Le fichier \"personnes.dat\" n'a pas pu etre ouvert.");
		return EXIT_FAILURE;
	}

	Personne p;
	printf("--- Pour finir la saisie, donnez un nom 'vide' ---\n");
	do {
		printf("\nNom:");
		saisie(p.nom, TAILLE_MAX_NOM);
		if (strlen(p.nom) == 0) {
			break;
		}
		printf("Prenom:");
		saisie(p.prenom, TAILLE_MAX_PRENOM);
		printf("Age:");
		scanf("%hu", &p.age);
		fflush(stdin);
		fwrite(&p, sizeof(Personne), 1, fichier);
	} while (1);

	fclose(fichier);
	return EXIT_SUCCESS;
}
