#include "test_utilities.h"
#include "../list_mtm/list_mtm1.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define N 5

static ListElement copyString(ListElement str) {
    assert(str);
    char *copy=malloc(strlen(str) + 1);
    return copy != NULL ? strcpy(copy, str) : NULL;
}

static void freeString(ListElement str) {
    free(str);
}

static bool isLongerThan(ListElement element, ListFilterKey number) {
    char *string=element;
    return strlen(string) > *(int *) number;
}

static int compareStrings(ListElement str1, ListElement str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);
    return strcmp((char *) str1, (char *) str2);
}

static bool testListStringCreate() {
    ASSERT_TEST(listCreate(NULL, NULL) == NULL);
    ASSERT_TEST(listCreate(NULL, NULL) == NULL);
    ASSERT_TEST(listCreate(copyString, NULL) == NULL);
    ASSERT_TEST(listCreate(NULL, freeString) == NULL);
    List list=listCreate(copyString, freeString);
    ASSERT_TEST(list != NULL);
    listDestroy(list);
    return true;
}

static List buildListForTests(char **a){
    List new_list=listCreate(copyString, freeString);
    if(!new_list){
        return NULL;
    }
    for(int i=0; i < N; ++i){
        ASSERT_TEST(listInsertFirst(new_list, a[i]) == LIST_SUCCESS);
    }
    return new_list;
}

static bool testListStringFilter(){
    char *a[N]={"aaa", "bbb", "NI", "hello mister fish", "I"};
    List list=buildListForTests(a);
    int key=2;
    List filtered=listFilter(list, isLongerThan, &key);
    ASSERT_TEST(listGetSize(filtered) == 3);
    ASSERT_TEST(strcmp(listGetFirst(filtered), a[3]) == 0);
    ASSERT_TEST(strcmp(listGetNext(filtered), a[1]) == 0);
    ASSERT_TEST(strcmp(listGetNext(filtered), a[0]) == 0);
    listDestroy(list);
    listDestroy(filtered);
    return true;
}

static bool testListStringCopy() {
    ASSERT_TEST(listCopy(NULL) == NULL);
    List source=listCreate(copyString, freeString);
    ASSERT_TEST(source!=NULL);
    List temp=listCopy(source);
    ASSERT_TEST(listGetFirst(temp) == NULL);
    listDestroy(temp);
    listDestroy(source);
    char *a[N]={"aaa", "bbb", "NI", "hello mister fish", "I"};
    source=buildListForTests(a);
    ASSERT_TEST(strcmp(listGetFirst(source), a[4]) == 0);
    ASSERT_TEST(strcmp(listGetNext(source), a[3]) == 0);
    ASSERT_TEST(strcmp(listGetNext(source), a[2]) == 0);
    ASSERT_TEST(strcmp(listGetCurrent(source), a[2]) == 0);
    List destination=listCopy(source);
    ASSERT_TEST(strcmp(listGetCurrent(destination), a[2]) == 0);
    ASSERT_TEST(listGetCurrent(destination) != listGetCurrent(source));
    listGetFirst(destination);
    listGetFirst(source);
    while(listGetCurrent(destination)){
        ASSERT_TEST(!strcmp(listGetCurrent(destination), listGetCurrent
                (source)));
        listGetNext(destination);
        listGetNext(source);
    }
    listDestroy(source);
    listDestroy(destination);
    return true;
}

static bool testListStringGetSize() {
    char *a[N]={"aaa", "bbb", "NI", "hello mister fish", "I"};
    List list=buildListForTests(a);
    ASSERT_TEST(listGetSize(list) == 5);
    listDestroy(list);
    return true;
}

static bool testListStringGetFirst() {
    char *a[N]={"aaa", "bbb", "NI", "hello mister fish", "I"};
    List list=buildListForTests(a);
    ASSERT_TEST(strcmp(listGetFirst(list), a[4]) == 0);
    ASSERT_TEST(listRemoveCurrent(list) == LIST_SUCCESS);
    ASSERT_TEST(strcmp(listGetFirst(list), a[3]) == 0);
    listDestroy(list);
    return true;
}

static bool testListStringGetNext() {
    char *a[5]={"aaa", "bbb", "NI", "hello mister fish", "I"};
    List list=buildListForTests(a);
    listGetFirst(list);
    int i=4;
    while(listGetCurrent(list)){
        ASSERT_TEST(strcmp(listGetCurrent(list), a[i--]) == 0);
        listGetNext(list);
    }
    listDestroy(list);
    return true;
}

static bool testListInsertStringFirst() {
    char *a[N]={"aaa", "bbb", "NI", "hello mister fish", "I"};
    List list=buildListForTests(a);
    ASSERT_TEST(listInsertFirst(list,NULL)==LIST_NULL_ARGUMENT);
    ASSERT_TEST(listInsertFirst(NULL,"IDO")==LIST_NULL_ARGUMENT);
    listGetFirst(list);
    int i=4;
    while(listGetCurrent(list)){
        ASSERT_TEST(strcmp(listGetCurrent(list), a[i--]) == 0);
        listGetNext(list);
    }
    ASSERT_TEST(i == -1);
    listDestroy(list);
    return true;
}

static bool testListStringInsertLast() {
    char *a[N]={"aaa", "bbb", "NI", "hello mister fish", "I"};
    List list=listCreate(copyString, freeString);
    ASSERT_TEST(listInsertLast(list,NULL)==LIST_NULL_ARGUMENT);
    ASSERT_TEST(listInsertFirst(NULL,"IDO")==LIST_NULL_ARGUMENT);
    ASSERT_TEST(list!=NULL);
    for(int i=0; i < N; ++i){
        listInsertLast(list, a[i]);
    }
    listGetFirst(list);
    int i=0;
    while(listGetCurrent(list)){
        ASSERT_TEST(strcmp(listGetCurrent(list), a[i++]) == 0);
        listGetNext(list);
    }
    ASSERT_TEST(i == 5);
    listDestroy(list);
    return true;
}

static bool testListStringInsertBeforeCurrent() {
    char *a[N]={"aaa", "bbb", "NI", "hello mister fish", "I"};
    List list=listCreate(copyString, freeString);
    ASSERT_TEST(list!=NULL);
    ASSERT_TEST(listInsertBeforeCurrent(list,NULL)==LIST_NULL_ARGUMENT);
    ASSERT_TEST(listInsertBeforeCurrent(NULL, a[4]) == LIST_NULL_ARGUMENT);
    listInsertLast(list, a[4]);
    ASSERT_TEST(!strcmp(listGetFirst(list), a[4]));
    for(int i=0; i < 4; ++i){
        listInsertBeforeCurrent(list, a[i]);
    }
    ASSERT_TEST(strcmp(listGetCurrent(list), a[4]) == 0);
    int i=0;
    listGetFirst(list);
    while(listGetCurrent(list)){
        ASSERT_TEST(strcmp(listGetCurrent(list), a[i++]) == 0);
        listGetNext(list);
    }
    ASSERT_TEST(i == 5);
    listDestroy(list);
    return true;
}

static bool testListStringInsertAfterCurrent() {
    char *a[N]={"aaa", "bbb", "NI", "hello mister fish", "I"};
    List list=listCreate(copyString, freeString);
    ASSERT_TEST(list!=NULL);
    ASSERT_TEST(listInsertAfterCurrent(list,NULL)==LIST_NULL_ARGUMENT);
    ASSERT_TEST(listInsertAfterCurrent(NULL, a[0]) == LIST_NULL_ARGUMENT);
    listInsertLast(list, a[0]);
    ASSERT_TEST(!strcmp(listGetFirst(list), a[0]));
    for(int i=4; i > 0; --i){
        listInsertAfterCurrent(list, a[i]);
    }
    ASSERT_TEST(strcmp(listGetCurrent(list), a[0]) == 0);
    int i=0;
    listGetFirst(list);
    while(listGetCurrent(list)){
        ASSERT_TEST(strcmp(listGetCurrent(list), a[i++]) == 0);
        listGetNext(list);
    }
    ASSERT_TEST(i == 5);
    listDestroy(list);
    return true;
}

static bool testListStringRemoveCurrent() {
    char *a[5]={"aaa", "bbb", "NI", "hello mister fish", "I"};
    List list=listCreate(copyString, freeString);
    ASSERT_TEST(list!=NULL);
    ASSERT_TEST(listRemoveCurrent(NULL) == LIST_NULL_ARGUMENT);
    listInsertLast(list, a[0]);
    ASSERT_TEST(listRemoveCurrent(list) == LIST_INVALID_CURRENT);
    listGetFirst(list);
    listRemoveCurrent(list);
    ASSERT_TEST(listRemoveCurrent(list) == LIST_INVALID_CURRENT);
    for(int i=0; i < 5; ++i){
        listInsertLast(list, a[i]);
    }
    listGetFirst(list);
    for(int i=0; i < 3; i++){
        listGetNext(list);
    }
    ASSERT_TEST(listRemoveCurrent(list) == LIST_SUCCESS);
    ASSERT_TEST(strcmp(listGetFirst(list), a[0]) == 0);
    ASSERT_TEST(strcmp(listGetNext(list), a[1]) == 0);
    ASSERT_TEST(strcmp(listGetNext(list), a[2]) == 0);
    ASSERT_TEST(strcmp(listGetNext(list), a[4]) == 0);
    ASSERT_TEST(listGetSize(list) == 4);
    ASSERT_TEST(strcmp(listGetCurrent(list), a[4]) == 0);
    ASSERT_TEST(listGetNext(list) == NULL);
    listDestroy(list);
    return true;
}

static bool testListStringSort() {
    char *a[N]={"I", "NI", "aaa", "bbb", "hello mister fish"};
    List list=buildListForTests(a);
    ASSERT_TEST(strcmp(listGetFirst(list), a[4]) == 0);
    ASSERT_TEST(strcmp(listGetNext(list), a[3]) == 0);
    ASSERT_TEST(listSort(NULL, compareStrings) == LIST_NULL_ARGUMENT);
    ASSERT_TEST(listSort(list, NULL) == LIST_NULL_ARGUMENT);
    ASSERT_TEST(listSort(list, compareStrings) == LIST_SUCCESS);
    ASSERT_TEST(strcmp(listGetCurrent(list),a[1])==0);
    listGetFirst(list);
    int i=0;
    while(listGetCurrent(list)){
        ASSERT_TEST(strcmp(listGetCurrent(list), a[i++]) == 0);
        listGetNext(list);
    }
    listDestroy(list);
    return true;
}

static bool testListStringClear() {
    char *a[N]={"I", "NI", "aaa", "bbb", "hello mister fish"};
    List list=buildListForTests(a);
    ASSERT_TEST(listClear(NULL) == LIST_NULL_ARGUMENT);
    ASSERT_TEST(listClear(list) == LIST_SUCCESS);
    ASSERT_TEST(listGetFirst(list) == NULL);
    ASSERT_TEST(listGetCurrent(list) == NULL);
    listDestroy(list);
    return true;
}

static bool testListStringDestroy() {
    listDestroy(NULL);
    List list=listCreate(copyString, freeString);
    ASSERT_TEST(list!=NULL);
    listDestroy(list);
    list=listCreate(copyString, freeString);
    ASSERT_TEST(list!=NULL);
    char *a[5]={"I", "NI", "aaa", "bbb", "hello mister fish"};
    for(int i=0; i < 5; i++){
        ASSERT_TEST(listInsertFirst(list, a[i]) == LIST_SUCCESS);
    }
    listDestroy(list);
    return true;
}

int main(int argv, char **arc) {
    RUN_TEST(testListStringCreate);
    RUN_TEST(testListStringFilter);
    RUN_TEST(testListStringCopy);
    RUN_TEST(testListStringGetSize);
    RUN_TEST(testListStringGetFirst);
    RUN_TEST(testListStringGetNext);
    RUN_TEST(testListInsertStringFirst);
    RUN_TEST(testListStringInsertLast);
    RUN_TEST(testListStringInsertBeforeCurrent);
    RUN_TEST(testListStringInsertAfterCurrent);
    RUN_TEST(testListStringRemoveCurrent);
    RUN_TEST(testListStringSort);
    RUN_TEST(testListStringClear);
    RUN_TEST(testListStringDestroy);
    return 0;
}