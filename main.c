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

    FILE *s = fopen(argv[2], "r");

    TST *stopwords = NULL;
    stopwords = read_file(stopwords, s);

    FILE *graph = fopen(argv[3], "r");

    TST *words = NULL;
    words = read_pages(words, argv[4], idx);

    String *s1 = string_create("abacate");
    //int d1 = TST_search(stopwords, s1);
    string_free(s1);

    TST_free(words);
    TST_free(stopwords);
    index_free(idx);

    fclose(s);
    fclose(graph);
    fclose(index);
    return 0;
}