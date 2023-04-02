#ifndef LAB2_STRUCT
#define LAB2_STRUCT

struct Word
{
	char word[100];
	char tmp[100];
	int count;
	struct Word* next;
	struct Word* pre;
	
} ;

typedef struct
{
	struct Word* current;
	struct Word* first_word;	
} NodeWord;

#endif