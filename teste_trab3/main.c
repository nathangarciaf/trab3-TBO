#include <string.h>

#include "tst.h"
#include "reader.h"
#include "index.h"
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

    Index *i = index_init();

    TST *words = NULL;
    words = read_dir_files(words, stopwords, argv[4], i, index);

    char *line = NULL;
    size_t size = 0;
    ssize_t nread = 0;

    while ((nread = getline(&line, &size, stdin)) != -1) {
        int len = strlen(line);
        char *og_line = (char*)calloc((len + 1), sizeof(char));
        strcpy(og_line, line);
        og_line[len-1] = '\0';
        
        char *str = strtok(line, " \n");
        Value *commom_files = NULL;

        while (str != NULL) {
            String *string = string_create(str);
            Value *v = TST_search(words, string);
            string_free(string);

            if(v){ commom_files = intersect_val(commom_files, v); }

            str = strtok(NULL, " \n");
        }

        print_results(og_line, commom_files);
        free(og_line);
        Value_free_reduced(commom_files);
    }
    
    free(line);

    FILE *graph = fopen(argv[3], "r");
    fclose(graph);
    
    index_free(i);
    TST_free(stopwords);
    TST_free(words);

    fclose(stopword_file);
    fclose(index);
    return 0;
}