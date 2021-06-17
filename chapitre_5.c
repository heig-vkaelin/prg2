//
// Created by Valentin Kaelin on 09.06.21.
//

#include <stdlib.h>
#include <stdio.h>

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
