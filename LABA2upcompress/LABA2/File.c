#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Program.h"
#include "struct.h"

void file_open(errno_t err) {

	if (err != 0) {
		printf("ERROR input");
		exit(1);
	}
}

void file_open_all(errno_t err, errno_t err_1) {

	if (err != 0) {
		printf("ERROR input");
		exit(1);
	}
	if (err_1 != 0) {
		printf("ERROR output");
		exit(1);
	}
}
