//
// Created by Valentin on 24.03.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <float.h>
#include <assert.h>

// #define PRINT_ADDRESS(ADR) printf("0x%" PRIxPTR "\n", (intptr_t) (ADR))
#define PRINT_ADDRESS(ADR) printf("%#x\n", (unsigned) (intptr_t) (ADR))

int ex2_1(void) {
	int n = 1;
	int *ptr = &n;

	printf("Valeur pointée par ptr: %d\n", *ptr);
	printf("Adresse contenue dans ptr: %p\n", (void *) ptr);
	printf("Adresse de ptr: %p\n", (void *) &ptr);

	printf("\nSeconde option: \n");
	PRINT_ADDRESS(ptr);
	PRINT_ADDRESS(&ptr);

	return EXIT_SUCCESS;
}

void carre_et_cube(double x, double *carre, double *cube) {
	*carre = x * x;
	*cube = *carre * x;
}

void test_ex2_2(double x) {
	double carre, cube;
	carre_et_cube(x, &carre, &cube);
	printf("carre(%g) = %g, cube(%g) = %g\n", x, carre, x, cube);
}

int ex2_2(void) {
	test_ex2_2(-1);
	test_ex2_2(0);
	test_ex2_2(1);
	test_ex2_2(2);
	test_ex2_2(2.5);
	test_ex2_2(DBL_MAX);

	return EXIT_SUCCESS;
}

void afficher(const int tab[], size_t taille) {
	printf("[");
	if (tab) {
		for (size_t i = 0; i < taille; ++i) {
			if (i > 0) {
				printf(", ");
			}
			printf("%d", tab[i]);
		}
	}
	printf("]\n");
}

void inverser(int *debut, int *fin) {
	assert(debut != NULL);
	assert(fin != NULL);

	while (debut < fin) {
		int tampon = *debut;
		*debut++ = *fin;
		*fin-- = tampon;
	}
}

void test_ex2_12(int tab[], size_t taille) {
	printf("Avant inverser : \n");
	afficher(tab, taille);
	inverser(tab, tab + taille - 1);
	printf("Apres inverser : \n");
	afficher(tab, taille);
}

int ex2_12(void) {
	{
		// Erreur de compilation ?
//		int tab[] = {};
//		test_ex2_12(tab, sizeof(tab) / sizeof(int));
	}
	{
		int tab[] = {1};
		test_ex2_12(tab, sizeof(tab) / sizeof(int));
	}
	{
		int tab[] = {1, 2};
		test_ex2_12(tab, sizeof(tab) / sizeof(int));
	}
	{
		int tab[] = {1, 2, 3};
		test_ex2_12(tab, sizeof(tab) / sizeof(int));
	}

	return EXIT_SUCCESS;
}

void afficherMatrice(int *adr, size_t m, size_t n) {
	for (size_t i = 0; i < m * n; ++i) {
		printf("%d ", *(adr + i));
		if ((i + 1) % n == 0) {
			printf("\n");
		}
	}
}

void initialiserMatrice(int *adr, size_t m, size_t n) {
	assert(adr != NULL);

	for (size_t i = 0; i < m * n; ++i) {
		adr[i] = i < n || i >= (m - 1) * n || i % n == 0 || (i + 1) % n == 0 ? 1 : 4;
	}
}

int ex2_21(void) {
	int matrice[3][4];
	initialiserMatrice((int *) matrice, 3, 4);
	afficherMatrice((int *) matrice, 3, 4);
	return EXIT_SUCCESS;
}

double sommeMatrice(double *adr, size_t m, size_t n) {
	double somme = 0;
	for (size_t i = 0; i < m * n; ++i) {
		somme += adr[i];
	}
	return somme;
}

int ex2_22(void) {
	double matrice[3][4] = {{1,   2.5, 3,   4},
									{5,   6,   7.5, 8},
									{9.5, 10,  11,  12}};

	double somme = sommeMatrice(&matrice[0][0], 3, 4);
	printf("Somme de la matrice: %g", somme);

	return EXIT_SUCCESS;
}

int *diagonaleMatrice(int *adr, size_t n) {
	int *diag = (int *) malloc(n * sizeof(int));
	for (size_t i = 0; i < n; ++i) {
		diag[i] = *(adr + i * n + i);
	}
	return diag;
}

int ex2_23(void) {
	int matrice[3][3] = {{1, 2, 3},
								{4, 5, 6},
								{7, 8, 9}};

	int *diagonale = diagonaleMatrice(&matrice[0][0], 3);
	printf("Diagonale:\n");
	afficher(diagonale, 3);
	return EXIT_SUCCESS;
}
