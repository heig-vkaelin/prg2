//
// Created by Valentin on 20.04.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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
	ETRANGER, SUISSE
} Nationalite;
typedef enum {
	A, B, C
} TypePermis;
const char* const NATIONALITES[] = {"Etranger", "Suisse"};
const char* TYPES_PERMIS[] = {"A", "B", "C"};

typedef struct {
	uint8_t tauxActivite;
} Suisse;

typedef struct {
	TypePermis typePermis;
} Etranger;

typedef union {
	Suisse suisse;
	Etranger etranger;
} Specificites;

typedef struct {
	Nom nom;
	Nationalite nationalite;
	Specificites specificites;
} PersonneV3;

void afficher_ex3_6(const PersonneV3* p) {
	printf("Nom           : %s\n", p->nom);
	printf("Nationalite   : %s\n", NATIONALITES[p->nationalite]);
	if (p->nationalite == SUISSE) {
		printf("Taux activite : %" PRIu8 "%%\n", p->specificites.suisse.tauxActivite);
	} else {
		printf("Type permis   : %s\n",
				 TYPES_PERMIS[p->specificites.etranger.typePermis]);
	}
}

PersonneV3 suisse(const char* nom, uint8_t tauxActivite) {
	PersonneV3 p = {"", SUISSE, {.suisse={tauxActivite}}};
	strcpy(p.nom, nom);
	return p;
}

PersonneV3 etranger(const char* nom, TypePermis typePermis) {
	PersonneV3 p = {"", ETRANGER, {.etranger={typePermis}}};
	strcpy(p.nom, nom);
	return p;
}

int ex3_6(void) {
	PersonneV3 p1 = suisse("Toto", 80);
	PersonneV3 p2 = etranger("Titi", C);

	afficher_ex3_6(&p1);
	printf("\n");
	afficher_ex3_6(&p2);
	printf("\n");

	return EXIT_SUCCESS;
}

void toLower(char* s) {
	if (s != NULL) {
		const size_t TAILLE = strlen(s);
		for (size_t i = 0; i < TAILLE; ++i) {
			s[i] = (char) tolower(s[i]);
		}
	}
}

size_t lireChaine(const char* const tab[], size_t n,
						const char* msgInvite, const char* msgErreur) {
#define TAILLE_MAX_CHAINE 8
	char chaineControle[4];
	sprintf(chaineControle, "%%%ds", TAILLE_MAX_CHAINE);
	char chaine[TAILLE_MAX_CHAINE + 1];
	do {
		printf("%s", msgInvite);
		scanf(chaineControle, chaine);
		fflush(stdin); // version portable: fseek(stdin, 0, SEEK_END)
		toLower(chaine);

		for (size_t i = 0; i < n; ++i) {
			if (strcmp(chaine, tab[i]) == 0) {
				return i;
			}
		}
		puts(msgErreur);
	} while (true);
}

void afficher_ex3_9(const char* const tab[], size_t n, size_t pos) {
	for (size_t i = 0; i < n; ++i) {
		printf("%s\n", tab[(pos + i) % n]);
	}
}

int ex3_9(void) {
	typedef enum {
		LUNDI, MARDI, MERCREDI, JEUDI, VENDREDI, SAMEDI, DIMANCHE
	} Jour;
	const char* const JOURS[] =
		{"lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi", "dimanche"};
	const size_t NB_JOURS = sizeof(JOURS) / sizeof(const char*);

	const char* const MSG_INVITE = "Donnez un jour de la semaine en toutes lettres :";
	const char* const MSG_ERREUR = "Saisie incorrecte. Veuillez SVP recommencer.";

	Jour jour = (Jour) lireChaine(JOURS, NB_JOURS, MSG_INVITE, MSG_ERREUR);
	afficher_ex3_9(JOURS, NB_JOURS, jour);

	return EXIT_SUCCESS;
}
