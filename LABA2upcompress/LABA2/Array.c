#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Program.h"
#include "struct.h"

void create_struct(NodeWord* node, const char* wd) {
    struct Word* word = (struct Word*)calloc(1, sizeof(struct Word));
    strcpy_s(word->word, _countof(word->word), wd);
    word->count = 1;
    word->next = NULL;
    word->pre = node->current;
    if (node->first_word == NULL) {
        node->first_word = word;
        node->current = word;
    }
    else {
        node->current->next = word;
        node->current = word;
    }
}

NodeWord* createArrayNode() {
    return (NodeWord*)calloc(1, sizeof(NodeWord));
}

void init_array(char*** word, FILE* fp_out) {

    fseek(fp_out, 0L, SEEK_SET);

    char buffer[2000];
    char* savePtr;
    int i = 0;

    fgets(buffer, 2000, fp_out);
    const char* token = strtok_s(buffer, " \t\n", &savePtr);
    while (token != NULL) {
        *word = (char*)realloc(*word, (i + 1) * sizeof(char*));
        (*word)[i] = _strdup(token);
        i++;
        token = strtok_s(NULL, " \t\n", &savePtr);
    }
}

int init_array_int(char** word, FILE* fp_out) {

    fseek(fp_out, 0L, SEEK_SET);

    char buffer[2000];
    char* savePtr;
    int i = 0;

    fgets(buffer, 2000, fp_out);
    char* token = strtok_s(buffer, " \t\n", &savePtr);
    while (token != NULL) {
        word[i] = token;
        i++;
        token = strtok_s(NULL, " \t\n", &savePtr);
    }
    return i;
}