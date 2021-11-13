#include "MouseCore/Utility.h"

int mouse_utility_getFileSize(FILE* file)
{
    int size = fseek(file, 0l, SEEK_END);
    rewind(file);

    return size;
}


static int mouse_utility_readBufferSize = 1024;
int mouse_utility_getFileLineCount(FILE* file)
{
    char buffer[mouse_utility_readBufferSize];
    int lineCount = 0;
    while(fgets(buffer, mouse_utility_readBufferSize, file) != NULL)
    {
        lineCount++;
    }
    rewind(file);

    return lineCount;
}

// allocates memory and returns it call free_lines later
char** mouse_utility_readFileLines(FILE* file, int lineCount)
{
    char buffer[mouse_utility_readBufferSize];
    char** fileLines = malloc(lineCount * sizeof(char*));
    size_t lineIndex = 0;
    memset(buffer, '\0', mouse_utility_readBufferSize);
    while(fgets(buffer, mouse_utility_readBufferSize, file))
    {
        fileLines[lineIndex] = malloc(mouse_utility_readBufferSize * sizeof(char));
        memcpy(fileLines[lineIndex], buffer, mouse_utility_readBufferSize);
        lineIndex++;
        memset(buffer, '\0', mouse_utility_readBufferSize);
    }

    return fileLines;
}

void mouse_utility_deleteFileLines(char** fileLines, int lineCount)
{
    for(size_t i = 0; i < lineCount; i++)
    {
        free(fileLines[i]);
        fileLines[i] = NULL;
    }
    free(fileLines);
    fileLines = NULL;
}

void mouse_utility_printCharArrays(char** charArrays, int lineCount)
{
    printf("\n");
    for(int i=0; i<lineCount; i++)
    {
        printf("%s\n", charArrays[i]);
    }
    printf("\n");
}

void mouse_utility_combinePath(const char* basePath, const char* path, char* dest)
{
    strcpy(dest, basePath);
    strcat(dest, path);
}