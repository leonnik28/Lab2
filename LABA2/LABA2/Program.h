#ifndef LAB2_Program_HEADER
#define LAB2_Program_HEADER
#include "struct.h"

int search_popular_max_int(NodeWord* node);
void file_open_all(errno_t err, errno_t err_1);
void file_open(errno_t err);
void createArray(NodeWord* pack, char* wd);
NodeWord* createArrayNode();
void searc_word(NodeWord* node);
void to_lower(char* str);
char* search_popular_min(NodeWord* node, int count_max);
char* search_popular_max(NodeWord* node);
void inputSpaces(unsigned const char* buffer, char* temp, int i);
void transition_new_line(char* temp, const char* token);
void delete_last_symbol(unsigned char* temp);
void token(char* buffer, char* tmp, char** words, int end);
int compress(NodeWord* node);
void init_array(NodeWord* node, char*** word, FILE* fp_out);
int init_array_int(NodeWord* node, char** word, FILE* fp_out);
#endif
