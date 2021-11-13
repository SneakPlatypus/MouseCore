#pragma once

// takes a function pointer and its arguments
// checks that the pointer is not null before calling the function
#define CallFnPtr(fn, ...)  if(fn != NULL) { fn(__VA_ARGS__); }

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int mouse_utility_getFileSize(FILE* file);
int mouse_utility_getFileLineCount(FILE* file);

char** mouse_utility_readFileLines(FILE* file, int lineCount); // allocates memory and returns it call free_lines later
void mouse_utility_deleteFileLines(char** fileLines, int lineCount);

void mouse_utility_printCharArrays(char** charArrays, int lineCount);

void mouse_utility_combinePath(const char* basePath, const char* path, char* dest);