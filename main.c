#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("ERRO\n");
        return 0;
    }

    DIR *diretorio;
    struct dirent *entrada;

    diretorio = opendir(argv[4]);
    if (diretorio == NULL) {
        perror("Erro ao abrir o diretório");
        return 0;
    }

    while ((entrada = readdir(diretorio)) != NULL) {
        // Ignorar os diretórios "." e ".."
        if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
            // Monta o caminho completo do arquivo
            char caminho_completo[512];
            snprintf(caminho_completo, sizeof(caminho_completo), "%s/%s", argv[4], entrada->d_name);
            printf("%s\n",entrada->d_name);
            // Ler o arquivo
            //ler_arquivo(caminho_completo);
        }
    }

    closedir(diretorio);

    FILE *index = fopen(argv[1], "r");
    FILE *stopwords = fopen(argv[2], "r");
    FILE *graph = fopen(argv[3], "r");
    printf("%s\n%s\n%s\n",argv[1],argv[2],argv[3]);

    fclose(index);
    fclose(stopwords);
    fclose(graph);
    return 0;
}