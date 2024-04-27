#ifndef GDEXTENSION_CREATOR_H
#define GDEXTENSION_CREATOR_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define endl printf("\n")

void floor_to(unsigned const short rounder, float* number);

int is_directory_exists(const char *path);

int has_forbidden_symbols(char *folder_name);

void fprint_double_quote(FILE *file);

void fwrap_in_double_quotes(FILE *file, char* text);

#endif