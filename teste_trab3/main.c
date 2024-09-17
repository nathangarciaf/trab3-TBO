#include <string.h>

#include "tst.h"
#include "reader.h"

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
    TST *stopwords = NULL;
    stopwords = read_file(stopwords, stopword_file);

    String *s1 = string_create("laranja");
    Value *v1 = TST_search(stopwords, s1);
    if(v1){
        printf("ARISER\n");
    }
    else
        printf("CALABRESO\n");
    string_free(s1);

    FILE *index = fopen(argv[1], "r");
    if(!index) {
        printf("Erro no arquivo: %s\n", argv[1]);
        return 1;
    }

    /*TST *words = NULL;
    words = read_dir_files(words, stopwords, argv[4], index);

    String *s1 = string_create("abacate");
    Value d1 = TST_search(words, s1);
    printf("FREQ: %d\n", d1);
    string_free(s1);*/

    FILE *graph = fopen(argv[3], "r");
    fclose(graph);

    //TST_free(words);
    TST_free(stopwords);

    fclose(stopword_file);
    fclose(index);
    return 0;
}