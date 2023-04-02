#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Program.h"
#include "struct.h"

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
        strcat_s(temp, 1000, "\n");
    }
    if (token[strlen(token) - 1] != '\n') {
        strcat_s(temp, 1000, " ");
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
                strcat_s(tmp, 1000, words[i + 1]);
                transition_new_line(tmp, token);
                found = 1;
                break;
            }
            else if (strcmp(token, words[i + 1]) == 0) {
                strcat_s(tmp, 1000, words[i]);
                transition_new_line(tmp, token);
                found = 1;
                break;
            }
            i += 2;
        }
        if (found == 0) {
            strcat_s(tmp, 1000, token);
            transition_new_line(tmp, token);
        }
        token = strtok_s(NULL, " \t\n", &savePtr);
    }
}

int compress(NodeWord* node) {
    errno_t err, err_1;
    FILE* fp_in, *fp_out;
    err = fopen_s(&fp_in, "input.txt", "r");
    err_1 = fopen_s(&fp_out, "output.txt", "r+");
    file_open_all(err, err_1);

    char* min_word = NULL;
    char* max_word = NULL;

    char** word = calloc(1, sizeof(char*));
       
    while (1) {           
        int max_count = search_popular_max_int(node);           
        max_word = search_popular_max(node);           
        min_word = search_popular_min(node, max_count);           
        if (min_word == NULL) {               
            fprintf(fp_out, "\n");                
            break;            
        }          
        fprintf(fp_out, "%s %s ", max_word, min_word);    
    }      

    long int position = ftell(fp_out);           
    init_array(&word, fp_out);        
    char buffer[1000];       
    int count = init_array_int(word, fp_out);
    char** word_copy = calloc(count + 1, sizeof(char*));
    for (int i = 0; i < count; i++) {
        word_copy[i] = _strdup(word[i]);
    }
    fseek(fp_out, position, SEEK_SET);

    while (fgets(buffer, 1000, fp_in) != NULL) {          
        char* tmp = (char*)calloc(1000, sizeof(char));                    
        token(buffer, tmp, word_copy, count);
        delete_last_symbol(tmp);              
        strcat_s(tmp, 1000, "\n");     
        fprintf(fp_out, "%s", tmp);              
        free(tmp);       
    }        
    free(word_copy);
    free(min_word);
    free(max_word);
    fclose(fp_in); 
    fclose(fp_out);
    return 0;
}


int un_compress() {
    errno_t err, err_1;
    FILE* fp_in, * fp_out;
    err = fopen_s(&fp_in, "input.txt", "w");
    err_1 = fopen_s(&fp_out, "output.txt", "r");
    file_open_all(err, err_1);

    char* min_word = NULL;
    char* max_word = NULL;

    char** word = calloc(1, sizeof(char*));

    init_array(&word, fp_out);
    char buffer[1000];
    int count = init_array_int(word, fp_out);
    char** word_copy = calloc(count + 1, sizeof(char*));
    for (int i = 0; i < count; i++) {
        word_copy[i] = _strdup(word[i]);
    }


    while (fgets(buffer, 1000, fp_out) != NULL) {
        char* tmp = (char*)calloc(1000, sizeof(char));
        token(buffer, tmp, word_copy, count);
        delete_last_symbol(tmp);
        strcat_s(tmp, 1000, "\n");
        fprintf(fp_in, "%s", tmp);
        free(tmp);
    }

    free(word_copy);
    free(min_word);
    free(max_word);
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
