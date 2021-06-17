//
// Created by Valentin Kaelin on 09.06.21.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

int ex5_3(void) {
	FILE* fichierBinaire = fopen("../data/personnes.dat", "rb");
	if (!fichierBinaire) {
		printf("Desole! Le fichier \"personnes.dat\" n'a pas pu etre ouvert.");
		return EXIT_FAILURE;
	}
	FILE* fichierTexte = fopen("../data/personnes.txt", "w");
	if (!fichierTexte) {
		printf("Desole! Le fichier \"personnes.txt\" n'a pas pu etre ouvert.");
		fclose(fichierBinaire);
		return EXIT_FAILURE;
	}
	Personne p;
	fprintf(fichierTexte, "%-*s %-*s %s\n",
			  TAILLE_MAX_NOM, "Nom", TAILLE_MAX_PRENOM, "Prenom", "Age");
	while (fread(&p, sizeof(Personne), 1, fichierBinaire)) {
		fprintf(fichierTexte, "%-*s %-*s %3hu\n",
				  TAILLE_MAX_NOM, p.nom, TAILLE_MAX_PRENOM, p.prenom, p.age);
	}
	fclose(fichierBinaire);
	fclose(fichierTexte);
	return EXIT_SUCCESS;
}

int ex5_4(void) {
	FILE* fichier = fopen("../data/personnes.dat", "rb");
	if (!fichier) {
		printf("Desole! Le fichier \"personnes.dat\" n'a pas pu etre ouvert.");
		return EXIT_FAILURE;
	}
	Personne p;
	Nom nomRecherche;
	printf("Quel nom recherchez-vous ? :");
	saisie(nomRecherche, TAILLE_MAX_NOM);
	bool trouve = false;
	while (!trouve && fread(&p, sizeof(Personne), 1, fichier)) {
		trouve = strcmp(p.nom, nomRecherche) == 0;
	}
	if (trouve)
		printf("%s %s, %hu ans\n", p.prenom, p.nom, p.age);
	else
		printf("Desole! Le nom \"%s\" ne figure pas dans le fichier.\n", nomRecherche);
	fclose(fichier);
	return EXIT_SUCCESS;
}
