#include "reader.h"

TST *read_dir_files(TST *t, TST *stopwords, char *dir, FILE *index){
    char *buffer = NULL;
    size_t len = 0;
    int nread = 0;

    while ((nread = getline(&buffer, &len, index)) != -1) {
        //\n
        int buffer_len = strlen(buffer);
        buffer[buffer_len - 1] = '\0'; 
        //printf("BUFFER: %s\n", buffer);

        int path_len = strlen(dir) + strlen(buffer) + 2;
        char *path = (char*)calloc(path_len, sizeof(char));
        strcpy(path, dir);
        strcat(path, "/");
        strcat(path, buffer);
        //printf("PATH: %s\n", path);

        FILE *f = fopen(path,"r");
        if(!f){
            printf("Arquivo %s inexistente\n", path);
            exit(1);
        }

        while ((nread = getline(&buffer, &len, f)) != -1) {
            char *str = strtok(buffer, " \n");

            while (str != NULL) {
                String *s = string_create(str);
                int val = TST_search(stopwords, s);
                if(!val) { t = TST_insert(t, s, 1); }
                    
                str = strtok(NULL, " \n");
                string_free(s);
            }
            //String *s = string_create(buffer);
            //printf("%s\n", buffer);
            //t = TST_insert(t,str, 1);
        }

        fclose(f);
        free(path);
    }
    free(buffer);
    return t;
}

TST *read_file(TST *t, FILE *f){
    char *buffer = NULL;
    size_t len = 0;
    int nread = 0;

    while ((nread = getline(&buffer, &len, f)) != -1) {
        String *s = string_create(buffer);
        t = TST_insert(t,s, 1);
        string_free(s);
    }

    free(buffer);
    return t;
}