#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Program.h"
#include "struct.h"

int main() {
	NodeWord* new = createArrayNode();
	searc_word(new);
	un_compress(new);
	free_struct(new);
	return 0;
}