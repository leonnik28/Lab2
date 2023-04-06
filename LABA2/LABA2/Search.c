#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Program.h"
#include "struct.h"

#define BUFF_SIZE 100

void searc_word(NodeWord* node) {
    errno_t err;
    FILE* fp_in;
    err = fopen_s(&fp_in, "input.txt", "r");
    file_open(err);

    char* saveptr;
    char buffer[BUFF_SIZE];

    while (fgets(buffer, BUFF_SIZE, fp_in) != NULL) {

        unsigned char* token = strtok_s(buffer, " \t\n", &saveptr);

        while (token != NULL) {
            to_lower(buffer);
            init_struct(node, token);
            token = strtok_s(NULL, " \t\n", &saveptr);
        }
    }
    fclose(fp_in);
}

void init_struct(NodeWord* node, const char* token) {
    struct Word* next_w = node->first_word;
    while (next_w != NULL) {
        if (strcmp(next_w->word, token) == 0) {
            next_w->count++;
            break;
        }
        next_w = next_w->next;
    }
    if (next_w == NULL) {
        create_struct(node, token);
    }
}

char* search_popular_max(NodeWord* node) {
    int max_count = 0;
    char* tmp = NULL;
    struct Word* word = node->first_word;
    while (word != NULL) {
        if (strlen(word->word) >= 4 && word->count > max_count && strcmp(word->word, word->tmp) != 0) {
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
        if (strcmp(word->word, tmp) == 0) {
            strcpy_s(word->tmp, strlen(tmp)+1, tmp);
        }
        word = word->next;
    }
    return tmp;
}

int search_popular_max_int(NodeWord* node) {
    int max_count = 0;
    struct Word* word = node->first_word;
    while (word != NULL) {
        if (strlen(word->word) >= 4 && word->count > max_count && strcmp(word->word, word->tmp) != 0) {
            max_count = word->count;
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
        if (strlen(word->word) <= 3 && word->count < min_count && strcmp(word->word, word->tmp) != 0) {
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
        if (strcmp(word->word, tmp) == 0) {
            strcpy_s(word->tmp, strlen(tmp) + 1, tmp);
        }
        word = word->next;
    }
    return tmp;
}

int search_popular_min_int(NodeWord* node, int count_max) {
    int min_count = count_max;
    struct Word* word = node->first_word;
    while (word != NULL) {
        if (strlen(word->word) <= 3 && word->count < min_count && strcmp(word->word, word->tmp) != 0) {
            min_count = word->count;
        }
        word = word->next;
    }
    return word;
}

void completing_dictionary(NodeWord* node, FILE* fp_out, char* max_word, char* min_word) {
    while (1) {
        max_word = search_popular_max(node);
        int max_count = search_popular_max_int(node);
        min_word = search_popular_min(node, max_count);
        int min_count = search_popular_min_int(node, max_count);
        if (min_word == NULL) {
            fprintf(fp_out, "\n");
            break;
        }
        if (((strlen(max_word) * min_count) + (strlen(min_word) * max_count)) > ((strlen(min_word) * min_count) + (strlen(max_word) * max_count) + strlen(max_word) + strlen(min_word) + 2)) {
            continue;
        }
        fprintf(fp_out, "%s %s ", max_word, min_word);
    }
    max_word = NULL;
    free(max_word);
    free(min_word);
}