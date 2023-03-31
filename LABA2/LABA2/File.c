#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Program.h"
#include "struct.h"

void file_open_in(FILE* fp_in) {

	if ((fp_in = fopen("input.txt", "r")) == NULL) {
		printf("ERROR input");
		exit(1);
	}
}

void file_open_out(FILE* fp_out) {

	if ((fp_out = fopen("output.txt", "w")) == NULL) {
		printf("ERROR output");
		exit(1);
	}
}

void file_open_all(FILE* fp_in, FILE* fp_out) {

	if ((fp_in = fopen("input.txt", "r")) == NULL) {
		printf("ERROR input");
		exit(1);
	}
	if ((fp_out = fopen("output.txt", "w")) == NULL) {
		printf("ERROR output");
		exit(1);
	}
}
