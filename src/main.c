#include "include/parser.h"

int main(int argc, char *argv[]){
    argc--;
    argv++;

    if (argc < 1) return EXIT_FAILURE;
    char *filename = argv[0];
    //element_t element;
    line_t* line;
    FILE *file = fopen(filename, "r");
    token_t token;

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", filename);
        return 0;
    }
    
    line = read_lines(filename, file);
    const char* input = line->content;
    while(line->line_size > 0){
        printf("Content: %s\n", line->content);
        do {
            token = lexer(input);
            printf("Token type: %d, Token value: %.*s", token.type, token.length, token.start);
            putchar('\n');
            input = token.start + token.length;
        } while(token.type != TOKEN_TYPE_EOF);
        line = read_lines(filename, file);
        input = line->content;
        if(line->line_size == -1) break;
    }

    fclose(file);
    free(line);
    line = NULL;

    return 0;
}