//
// Created by Valentin on 24.03.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <float.h>
#include <assert.h>
#include <math.h>
#include <string.h>

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

int *initialiser(size_t taille, int val) {
	int *tab = (int *) calloc(taille, sizeof(int));
	if (tab) {
//		for (size_t i = 0; i < taille; ++i)
//			tab[i] = val;
		for (int *tmp = tab; tmp < tab + taille; *tmp++ = val);
	}
	return tab;
}

void test_ex2_15(size_t taille, int val) {
	int *vecteur = initialiser(taille, val);
	afficher(vecteur, taille);
	free(vecteur);
}

int ex2_15(void) {
	test_ex2_15(5, 2);
	test_ex2_15(1, 42);
	test_ex2_15(0, 42);
	test_ex2_15(10, 3);

	return EXIT_SUCCESS;
}

int *inverse_v2(const int *debut, const int *fin) {
	assert(debut != NULL);
	assert(fin != NULL);
	assert(fin == debut - 1 || debut <= fin);

	const size_t TAILLE = (size_t) (fin - debut + 1);
	int *tab = (int *) calloc(TAILLE, sizeof(int));
	if (tab) {
		for (size_t i = 0; i < TAILLE; ++i) {
			tab[i] = *fin--;
		}
	}
	return tab;
}

void test_ex2_16(int tab[], size_t taille) {
	printf("Avant inverser : \n");
	afficher(tab, taille);
	int *tab_inverse = inverse_v2(tab, tab + taille - 1);
	printf("Apres inverser : \n");
	afficher(tab_inverse, taille);
	free(tab_inverse);
	tab_inverse = NULL;
	printf("\n");
}

int ex2_16(void) {
	{
		int tab[] = {1};
		test_ex2_16(tab, sizeof(tab) / sizeof(int));
	}
	{
		int tab[] = {1, 2};
		test_ex2_16(tab, sizeof(tab) / sizeof(int));
	}
	{
		int tab[] = {1, 2, 3};
		test_ex2_16(tab, sizeof(tab) / sizeof(int));
	}

	return EXIT_SUCCESS;
}

void afficherMatrice(const int *adr, size_t m, size_t n) {
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

int ex2_18(void) {
	int tab1[] = {1, 2, 3, 4, 5};
	const size_t SIZE = sizeof(tab1) / sizeof(int);
	int *tab2 = (int *) calloc(SIZE, sizeof(int));

	memcpy(tab2, tab1, sizeof(tab1));
	afficher(tab1, SIZE);
	afficher(tab2, SIZE);
	free(tab2);
	tab2 = NULL;

	return EXIT_SUCCESS;
}

#define SIZE_EX219 3

int ex2_19(void) {
	int tab[SIZE_EX219] = {0};
	afficher(tab, SIZE_EX219);
	for (size_t i = 0; i < SIZE_EX219; ++i) tab[i]++;
	afficher(tab, SIZE_EX219);

	memset(tab, 0, sizeof(tab));

	for (size_t i = 0; i < SIZE_EX219; ++i) tab[i] += 2;
	afficher(tab, SIZE_EX219);
	return EXIT_SUCCESS;
}

int ex2_20(void) {
	char str[] = "memmove est tres utile......";
	memmove(str + 17, str + 12, 10);
	printf("%s\n", str);
	return EXIT_SUCCESS;
}

int ex2_21(void) {
	int matrice[3][4];
	initialiserMatrice((int *) matrice, 3, 4);
	afficherMatrice((int *) matrice, 3, 4);
	return EXIT_SUCCESS;
}

double sommeMatrice(const double *adr, size_t m, size_t n) {
	assert(adr != NULL);
	double somme = 0.0;
	for (size_t i = 0; i < m * n; ++i) {
		somme += adr[i];
	}
	return somme;
}

int ex2_22(void) {
	const double M[3][4] = {{1,   2.5, 3,   4},
									{5,   6,   7.5, 8},
									{9.5, 10,  11,  12}};

	printf("Somme de la matrice: %g\n", sommeMatrice((double *) M, 3, 4));

	return EXIT_SUCCESS;
}

int *diagonaleMatrice(const int *adr, size_t n) {
	assert(adr != NULL);
	int *vecteur = (int *) calloc(n, sizeof(int));
	if (vecteur) {
		for (size_t i = 0; i < n; ++i) {
			vecteur[i] = adr[i * (n + 1)];
		}
	}
	return vecteur;
}

void test_ex2_23(int *(*f)(const int *, size_t), const int *adr, size_t n) {
	assert(f != NULL);
	int *vecteur = f(adr, n);
	printf("Diagonale = ");
	afficher(vecteur, n);
	free(vecteur);
}

int ex2_23(void) {
	const int M[3][3] = {{1, 2, 3},
								{4, 5, 6},
								{7, 8, 9}};

	test_ex2_23(diagonaleMatrice, (int *) M, 3);

	return EXIT_SUCCESS;
}

#define PI 3.141592654

double integrale(double (*f)(double), double a, double b, unsigned nbPas) {
	assert(f != NULL);
	assert(a < b);
	assert(nbPas > 0);


	const double PAS = (b - a) / nbPas;
	double x = a;
	double surface = 0.0;
	for (unsigned i = 0; i < nbPas; x += PAS, ++i) {
		surface += 0.5 * PAS * (f(x) + f(x + PAS));
	}
	return surface;
}

double exponentiel(double x) {
	return exp(-x * x);
}

int ex2_24(void) {
	printf("integrale de exp(-x*x) entre 0 et infini: %g\n",
			 integrale(exponentiel, 0, 20, 1000));
	printf("integrale de sin(x) entre 0 et pi/2: %g\n",
			 integrale(sin, 0, PI / 2, 1000));

	return EXIT_SUCCESS;
}
