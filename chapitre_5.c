//
// Created by Valentin Kaelin on 09.06.21.
//

#include <stdlib.h>
#include <stdio.h>

int ex5_1(void) {
	FILE* fichier;
	fichier = fopen("../data/ex5_1.txt", "r");
	if (fichier == NULL) {
		perror("Error");
		return EXIT_FAILURE;
	}
	int c;
	while ((c = getc(fichier)) != EOF)
		putchar(c);
	fclose(fichier);

	return EXIT_SUCCESS;
}
