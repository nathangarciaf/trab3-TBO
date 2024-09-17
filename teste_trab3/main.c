#include <string.h>

#include "tst.h"
#include "reader.h"
#include <sys/types.h>

int main(int argc, char *argv[]){
    if(argc < 5){
        printf("ERRO\n");
        return 0; 
    }

    FILE *stopword_file = fopen(argv[2], "r");
    if(!stopword_file) {
        printf("Erro no arquivo: %s\n", argv[2]);
        return 1;
    }

    FILE *index = fopen(argv[1], "r");
    if(!index) {
        printf("Erro no arquivo: %s\n", argv[1]);
        return 1;
    }

    TST *stopwords = NULL;
    stopwords = read_file(stopwords, stopword_file);

    TST *words = NULL;
    words = read_dir_files(words, stopwords, argv[4], index);

    char *line = NULL;
    size_t size = 0;
    ssize_t nread = 0;

    while ((nread = getline(&line, &size, stdin)) != -1) {
        char *str = strtok(line, " \n");
        while (str != NULL) {
            printf("linha lida: %s\n", str);
            str = strtok(NULL, " \n");
        }
    }
    free(line);

    FILE *graph = fopen(argv[3], "r");
    fclose(graph);
    
    TST_free(stopwords);
    TST_free(words);

    fclose(stopword_file);
    fclose(index);
    return 0;
}