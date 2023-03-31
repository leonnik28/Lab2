#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Program.h"
#include "struct.h"

int main() {
	NodeWord* new = createArrayNode();
	searc_word(new);
	compress(new);		
	return 0;
}