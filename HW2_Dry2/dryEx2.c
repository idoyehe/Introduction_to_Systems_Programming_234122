#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

#define SIZE_CHAR sizeof(char)
char* flat_text(char **words,int n) {
/*gets an array of strings and return all the strings chained to one string*/
    assert(words != NULL);
    char *word =NULL;//initializing char pointer
    int curr_length = 0;//initializing current length
    for (int i = 0; i < n; ++i) {
        int add_length = strlen(words[i]);//gets the length of the new string
        char *temp = (char*)malloc(SIZE_CHAR*(curr_length + add_length + 1));
        //new allocation of new array  with bigger size
            if (temp == NULL){
                free(word);//free the chained word so far
                return NULL;
            }
        if (word!=NULL){//excepting the first iteration
            strcpy(temp, word);
        }
        free(word);//free the chained word so far
        word = temp;//change word to point temp
        strcpy(word + curr_length, words[i]);//chaining the next word
        curr_length=strlen(word);//updating length
        }
        return word;
}
int main(){
    char *words[] = {"Hello","To","234122","MATAM",};
    char *p=flat_text(words,4);
    if(p!=NULL){
        printf("\n%s\n", p);
    }
    free(p);
    return 0;
}