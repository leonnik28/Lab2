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
