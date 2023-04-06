#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Program.h"
#include "struct.h"

#define TEMP_SIZE 1000
#define BUFFER_SIZE 1000

void to_lower(char* str) {
    if (str != NULL) {
        for (int i = 0; i < strlen(str); i++) {
            str[i] = (char)tolower(str[i]);
        }
    }
}

void delete_last_symbol(unsigned char* temp) {
    while (strlen(temp) > 0 && !isalnum(temp[strlen(temp) - 1]) && !ispunct(temp[strlen(temp) - 1])) {
        temp[strlen(temp) - 1] = '\0';
    }
}

void transition_new_line(char* temp, const char* token) {

    if (token == NULL) {
        strcat_s(temp, TEMP_SIZE, "\n");
    }
    if (token[strlen(token) - 1] != '\n') {
        strcat_s(temp, TEMP_SIZE, " ");
    }
    else {
        temp[strlen(temp) - 1] = '\0';
    }
}

void token(char* buffer, char* tmp, char** words, int end) {
    char* savePtr;
    const char* token = strtok_s(buffer, " \t\n", &savePtr);


    while (token != NULL) {
        unsigned long len = strlen(token);
        if (len == 0) {
            continue;
        }
        int i = 0;
        int found = 0;
        while (i < end) {
            if (strcmp(token, words[i]) == 0) {
                strcat_s(tmp, TEMP_SIZE, words[i + 1]);
                transition_new_line(tmp, token);
                found = 1;
                break;
            }
            else if (strcmp(token, words[i + 1]) == 0) {
                strcat_s(tmp, TEMP_SIZE, words[i]);
                transition_new_line(tmp, token);
                found = 1;
                break;
            }
            i += 2;
        }
        if (found == 0) {
            strcat_s(tmp, TEMP_SIZE, token);
            transition_new_line(tmp, token);
        }
        token = strtok_s(NULL, " \t\n", &savePtr);
    }
}

int un_compress() {
    errno_t err, err_1;
    FILE* fp_in, * fp_out;
    err = fopen_s(&fp_in, "input.txt", "w");
    err_1 = fopen_s(&fp_out, "output.txt", "r");
    file_open_all(err, err_1);

    char** word = calloc(1, sizeof(char*));
 
    init_array(&word, fp_out);
    char buffer[BUFFER_SIZE];
    int count = init_array_int(word, fp_out);
    char** word_copy = calloc(count + 1, sizeof(char*));

    for (int i = 0; i < count; i++) {
        word_copy[i] = _strdup(word[i]);
    }

    while (fgets(buffer, BUFFER_SIZE, fp_out) != NULL) {
        char* tmp = (char*)calloc(TEMP_SIZE, sizeof(char));
        token(buffer, tmp, word_copy, count);
        delete_last_symbol(tmp);
        strcat_s(tmp, TEMP_SIZE, "\n");
        fprintf(fp_in, "%s", tmp);
        free(tmp);
    }

    free(word_copy);
    free(word);
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
