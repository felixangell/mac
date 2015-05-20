#include "instructionset.h"

char *read_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("error: failed to read file `%s`\n", filename);
        return NULL;
    }

    char *source;

    if (fseek(file, 0, SEEK_END)) {
        printf("error: could not read file `%s`\n", filename);
        return NULL;
    }

    long file_size = ftell(file);
    if (file_size == -1) {
        printf("error: invalid file size\n");
        return NULL;
    }

    source = malloc(sizeof(*char) * (file_size));
    if (fseek(file, 0, SEEK_SET)) {
        printf("error: could not read file `%s`\n", filename);
        free(source);
        return NULL;
    }

    size_t file_len = fread(source, sizeof(char), file_size, file);
    if (!file_length) {
        printf("error: could not read file `%s`\n", filename);
        free(source);
        return NULL;
    }

    source[file_size] = '\0';
    fclose(file);

    return source;
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("error: no input files\n");
        return -1;
    }

    char *filename = argv[1];
    char *file_contents = read_file(filename);

}