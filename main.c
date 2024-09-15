#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define INDEX_ALLOC 8
#define INDEX_LINE_LENGTH 128

struct index {
    char **docs;
    int size, alloc;
};

typedef struct index Index;

Index *index_init(){
    Index *i = (Index*)calloc(1,sizeof(Index));
    i->docs = (char**)calloc(INDEX_ALLOC, sizeof(char*));
    i->size = 0;
    i->alloc = INDEX_ALLOC;
    return i;
}

void index_read(Index *i, FILE *f){
    char buffer[INDEX_LINE_LENGTH];
    while (fgets(buffer, INDEX_LINE_LENGTH, f)){
        if(i->size == i->alloc){
            i->alloc *= 2;
            i->docs = (char**)realloc(i->docs, i->alloc);
        }
        printf("AQUI");
        i->docs[i->size] = buffer;
        printf("AQUI");
        i->size++;
    }
        
}

void index_free(Index *index){
    for(int i = 0; i < index->size; i++){
        free(index->docs[i]);
    }
    free(index->docs);
    free(index);
}

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
    index_free(idx);

    FILE *stopwords = fopen(argv[2], "r");
    FILE *graph = fopen(argv[3], "r");
    printf("%s\n%s\n%s\n",argv[1],argv[2],argv[3]);

    fclose(stopwords);
    fclose(graph);

    DIR *diretorio;
    struct dirent *entrada;

    diretorio = opendir(argv[4]);
    if (diretorio == NULL) {
        perror("Erro ao abrir o diretório");
        return 0;
    }

    printf("\n");
    while ((entrada = readdir(diretorio)) != NULL) {
        // Ignorar os diretórios "." e ".."
        if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
            char caminho_completo[512];
            snprintf(caminho_completo, sizeof(caminho_completo), "%s/%s", argv[4], entrada->d_name);
            printf("%s\n",entrada->d_name);
            //ler_arquivo(caminho_completo);
        }
    }

    closedir(diretorio);
    return 0;
}