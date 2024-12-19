#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>

void write_to_file(const char *filename, const char *data);
char* read_from_file(const char *filename);

#endif