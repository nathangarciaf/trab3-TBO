#include "tst.h"
#include "reader.h"
#include "index.h"

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("ERRO\n");
        return 0; 
    }

    char *input_directory = argv[1];

    char *index_path = calloc(strlen(input_directory) + strlen("index.txt") + 1, sizeof(char));
    char *stopwords_path = calloc(strlen(input_directory) + strlen("stopwords.txt") + 1, sizeof(char));
    char *graph_path = calloc(strlen(input_directory) + strlen("graph.txt") + 1, sizeof(char));
    char *pages_path = calloc(strlen(input_directory) + strlen("pages") + 1, sizeof(char));

    sprintf(index_path, "%sindex.txt", input_directory);
    sprintf(stopwords_path, "%sstopwords.txt", input_directory);
    sprintf(graph_path, "%sgraph.txt", input_directory);
    sprintf(pages_path, "%spages", input_directory);


    FILE *stopword_file = fopen(stopwords_path, "r");
    if(!stopword_file) {
        printf("Erro no arquivo: %s\n", stopwords_path);
        return 1;
    }

    FILE *index = fopen(index_path, "r");
    if(!index) {
        printf("Erro no arquivo: %s\n", index_path);
        return 1;
    }

    TST *stopwords = NULL;
    stopwords = read_stopwords(stopwords, stopword_file);
    fclose(stopword_file);

    Index *i = index_init();
    TST *words = NULL;
    words = read_dir_files(words, stopwords, pages_path, i, index);
    fclose(index);

    FILE *graph = fopen(graph_path, "r");
    if(!graph) {
        printf("Erro no arquivo: %s\n", graph_path);
        return 1;
    }

    read_graph(i, graph);
    fclose(graph);

    index_pageranks(i);
    //index_print(i);

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

        print_results(og_line, commom_files, i);
        free(og_line);
        Value_free_reduced(commom_files);
    }
    
    free(line);
    
    index_free(i);
    TST_free(stopwords);
    TST_free(words);

    free(index_path);
    free(stopwords_path);
    free(graph_path);
    free(pages_path);

    return 0;
}