#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Program.h"
#include "struct.h"

#define STR_SIZE 2000

void create_struct(NodeWord* node, const char* wd) {
    struct Word* word = (struct Word*)calloc(1, sizeof(struct Word));
    word->word = (char*)malloc(strlen(wd));
    strcpy_s(word->word, strlen(wd)+1, wd);
    word->tmp = malloc(strlen(wd));
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

    char buffer[STR_SIZE];
    char* savePtr;
    int i = 0;

    fgets(buffer, STR_SIZE, fp_out);
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

    char buffer[STR_SIZE];
    char* savePtr;
    int i = 0;

    fgets(buffer, STR_SIZE, fp_out);
    char* token = strtok_s(buffer, " \t\n", &savePtr);
    while (token != NULL) {
        word[i] = token;
        i++;
        token = strtok_s(NULL, " \t\n", &savePtr);
    }
    return i;
}

void free_struct(NodeWord* node) {
    struct Word* word = node->first_word;
    while (word != NULL) {
        struct Word* next = word->next;
        free(word);
        word = next;
    }
    node->current = NULL;
    node->first_word = NULL;
}
