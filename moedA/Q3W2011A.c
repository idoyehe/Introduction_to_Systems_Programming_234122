#include <stdio.h>

int main (int argc, char** argv){
    if(argc < 2){
        printf("Error\n");
        return 0;
    }
    char * str=argv[1];
    for(int i=2;i<argc;++i){
        FILE *to=fopen(argv[i],"w");
        if(to==NULL){
            printf("Error printing to %s\n",argv[i]);
            continue;
        }
        fprintf(to,"%s",str);
        fclose(to);
    }
    return 0;
}
