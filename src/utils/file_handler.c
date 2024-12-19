#include "file_handler.h"
#include <stdlib.h>
#include <string.h>

void write_to_file(const char *filename, const char *data) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        return;
    }
    fprintf(file, "%s\n", data);
    fclose(file);
}

char* read_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *content = (char*)malloc(size + 1);
    if (content == NULL) {
        fclose(file);
        return NULL;
    }
    
    fread(content, 1, size, file);
    content[size] = '\0';
    
    fclose(file);
    return content;
}