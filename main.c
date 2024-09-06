#include <stdio.h>

int main(int argc, char *argv[]){

    if(argc < 4)
        return 0;

    FILE *index = fopen(argv[1], "w");
    FILE *stopwords = fopen(argv[2], "w");
    FILE *graph = fopen(argv[3], "w");
    print("%s\n%s\n%s\n",argv[1],argv[2],argv[3]);

    fclose(index);
    fclose(stopwords);
    fclose(graph);
    return 0;
}