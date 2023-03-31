#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Program.h"
#include "struct.h"

void searc_word(NodeWord* node) {
    errno_t err;
    FILE* fp_in;
    err = fopen_s(&fp_in, "input.txt", "r");
    file_open(err);

    char tmp[100];
    char* saveptr;
    char buffer[100];

    while (fgets(buffer, 100, fp_in) != NULL) {

        tmp[0] = '\0';
        unsigned char* token = strtok_s(buffer, " \t\n", &saveptr);

        while (token != NULL) {
            to_lower(buffer);
            struct  Word* next_w = node->first_word;
            while (next_w != NULL) {
                if (strcmp(next_w->word, token) == 0) {
                    next_w->count++;
                    break;
                }
                next_w = next_w->next;
            }
            if (next_w == NULL) {
                createArray(node, token);
            }
            token = strtok_s(NULL, " \t\n", &saveptr);

        }
    }

    fclose(fp_in);
}

char* search_popular_max(NodeWord* node) {
    int max_count = 0;
    char* tmp = NULL;
    struct Word* word = node->first_word;
    while (word != NULL) {
        if (strlen(word->word) > 4 && word->count > max_count && strcmp(word->word, word->tmp) != 0) {
            max_count = word->count;
            tmp = word->word;
        }
        word = word->next;
    }
    if (tmp == NULL) {
        return NULL;
    }
    word = node->first_word;
    while (word != NULL) {
        if (strcmp(word->word, tmp) == 0) strcpy_s(word->tmp, _countof(word->tmp), tmp);
        word = word->next;
    }

    return tmp;
}

int search_popular_max_int(NodeWord* node) {
    int max_count = 0;
    char* tmp = NULL;
    struct Word* word = node->first_word;
    while (word != NULL) {
        if (strlen(word->word) > 4 && word->count > max_count && strcmp(word->word, word->tmp) != 0) {
            max_count = word->count;
            tmp = word->word;
        }
        word = word->next;
    }
    return max_count;
}

char* search_popular_min(NodeWord* node, int count_max) {
    int min_count = count_max;
    char* tmp = NULL;
    struct Word* word = node->first_word;
    while (word != NULL) {
        if (strlen(word->word) < 3 && word->count < min_count && strcmp(word->word, word->tmp) != 0) {
            min_count = word->count;
            tmp = word->word;
        }
        word = word->next;
    }
    word = node->first_word;

    if (tmp == NULL) {
        return NULL;
    }
    while (word != NULL) {
        if (strcmp(word->word, tmp) == 0) strcpy_s(word->tmp, _countof(word->tmp), tmp);
        word = word->next;
    }
    return tmp;
}
