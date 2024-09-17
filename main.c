#include <string.h>

#include "tst.h"
#include "reader.h"

int main(int argc, char *argv[]){
    if(argc < 5){
        printf("ERRO\n");
        return 0; 
    }

    FILE *index = fopen(argv[1], "r");
    if(!index) {
        printf("Erro no arquivo: %s\n", argv[1]);
        return 1;
    }
    Index *idx = index_init();
    index_read(idx, index);

    FILE *stopword_file = fopen(argv[2], "r");
    if(!stopword_file) {
        printf("Erro no arquivo: %s\n", argv[2]);
        return 1;
    }
    TST *stopwords = NULL;
    stopwords = read_file(stopwords, stopword_file);

    TST *words = NULL;
    words = read_pages(words, stopwords, argv[4], idx);

    /*String *s1 = string_create("fruta");
    int d1 = TST_search(words, s1);
    printf("D1: %d",d1);
    string_free(s1);*/

    FILE *graph = fopen(argv[3], "r");

    TST_free(words);
    TST_free(stopwords);
    index_free(idx);

    fclose(stopword_file);
    fclose(graph);
    fclose(index);
    return 0;
}