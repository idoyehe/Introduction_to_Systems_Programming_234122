#include "test_utilities.h"
#include "../set.h"
#include "../client.h"
#include <string.h>

#define EQUAL 0
#define BAD_EMAIL1 "@@"
#define BAD_EMAIL2 "bad!!"
#define GOOD_EMAIL1 "ido@gmail.com"
#define GOOD_EMAIL2 "shlomi@gmail.com"
#define BAD_LEVEL1 -5
#define BAD_LEVEL2 11
#define GOOD_LEVEL 5
#define BAD_FACULTY -1


static bool testclientCreate() {
    Client client=clientCreate();
    ASSERT_TEST(client!= NULL);
    clientDestroy(client);
    return true;
}

static Client buildclientForTests(){
    Client my_client=clientCreate();
    ASSERT_TEST(my_client!=NULL);
    ASSERT_TEST(clientSetEmail(my_client,GOOD_EMAIL1)==CLIENT_SUCCESS);
    ASSERT_TEST(clientSetFaculty(my_client,ELECTRICAL_ENGINEERING)==CLIENT_SUCCESS);
    ASSERT_TEST(clientSetLevel(my_client,GOOD_LEVEL)==CLIENT_SUCCESS);
    return my_client;
}

static bool testclientSetEmail(){
    Client ido=buildclientForTests();
    ASSERT_TEST(ido!= NULL);
    ASSERT_TEST(clientSetEmail(ido,NULL)==CLIENT_NULL_PARAMETER);
    ASSERT_TEST(clientSetEmail(ido,BAD_EMAIL1)==CLIENT_ILLEGAL_PARAMETERS);
    ASSERT_TEST(clientSetEmail(ido,BAD_EMAIL2)==CLIENT_ILLEGAL_PARAMETERS);
    const Email output1=clientGetEmailR(ido);
    ASSERT_TEST(strcmp(output1,GOOD_EMAIL1)==EQUAL);
    ASSERT_TEST(clientSetEmail(ido,GOOD_EMAIL2)==CLIENT_SUCCESS);
    const Email output2=clientGetEmailR(ido);
    ASSERT_TEST(strcmp(output2,GOOD_EMAIL2)==EQUAL);
    clientDestroy(ido);
    return true;
}

static bool testclientSetFaculty() {
    Client ido=buildclientForTests();
    ASSERT_TEST(ido!= NULL);
    TechnionFaculty output;
    ASSERT_TEST(clientSetFaculty(ido,BAD_FACULTY)==CLIENT_ILLEGAL_PARAMETERS);
    ASSERT_TEST(clientSetFaculty(ido,UNKNOWN)==CLIENT_ILLEGAL_PARAMETERS);
    ASSERT_TEST(clientGetFaculty(ido,&output)==CLIENT_SUCCESS);
    ASSERT_TEST(output==ELECTRICAL_ENGINEERING);
    ASSERT_TEST(clientSetFaculty(ido, CHEMISTRY)==CLIENT_SUCCESS);
    ASSERT_TEST(clientGetFaculty(ido,&output)==CLIENT_SUCCESS);
    ASSERT_TEST(output==CHEMISTRY);
    clientDestroy(ido);
    return true;
}

static bool testclientGetEmailR() {
    Client ido=buildclientForTests();
    ASSERT_TEST(ido!= NULL);
    const Email output1=clientGetEmailR(ido);
    ASSERT_TEST(strcmp(output1,GOOD_EMAIL1)==EQUAL);
    clientDestroy(ido);
    return true;
}

static bool testclientGetFaculty() {
    Client ido=clientCreate();
    ASSERT_TEST(ido!= NULL);
    TechnionFaculty output;
    ASSERT_TEST(clientGetFaculty(ido,NULL)==CLIENT_NULL_PARAMETER);
    ASSERT_TEST(clientGetFaculty(ido,&output)==CLIENT_ILLEGAL_PARAMETERS);
    ASSERT_TEST(clientSetFaculty(ido,CHEMISTRY) ==CLIENT_SUCCESS);
    ASSERT_TEST(clientGetFaculty(ido,&output)==CLIENT_SUCCESS);
    ASSERT_TEST(output==CHEMISTRY);
    ASSERT_TEST(clientSetFaculty(ido,COMPUTER_SCIENCE)==CLIENT_SUCCESS);
    ASSERT_TEST(clientGetFaculty(ido,&output)==CLIENT_SUCCESS);
    ASSERT_TEST(output==COMPUTER_SCIENCE);
    clientDestroy(ido);
    return true;
}

static bool testclientSetLevel(){
    Client ido=clientCreate();
    ASSERT_TEST(ido!= NULL);
    ASSERT_TEST(clientSetLevel(ido,BAD_LEVEL1)==CLIENT_ILLEGAL_PARAMETERS);
    ASSERT_TEST(clientSetLevel(ido,BAD_LEVEL2)==CLIENT_ILLEGAL_PARAMETERS);
    ASSERT_TEST(clientSetLevel(ido,GOOD_LEVEL)==CLIENT_SUCCESS);
    Skill output;
    ASSERT_TEST(clientGetLevel(ido,&output)==CLIENT_SUCCESS);
    ASSERT_TEST(output==GOOD_LEVEL);
    ASSERT_TEST(clientSetLevel(ido,GOOD_LEVEL+1)==CLIENT_SUCCESS);
    ASSERT_TEST(clientGetLevel(ido,&output)==CLIENT_SUCCESS);
    ASSERT_TEST(output==GOOD_LEVEL+1);
    clientDestroy(ido);
    return true;
}

static bool testclientGetLevel(){
    Client ido=buildclientForTests();
    ASSERT_TEST(ido!= NULL);
    Skill output;
    ASSERT_TEST(clientGetLevel(ido,NULL)==CLIENT_NULL_PARAMETER);
    ASSERT_TEST(clientGetLevel(ido,&output)==CLIENT_SUCCESS);
    ASSERT_TEST(output==GOOD_LEVEL);
    clientDestroy(ido);
    return true;
}

static bool testclientCopy() {
    Client ido=clientCreate();
    ASSERT_TEST(ido!=NULL);
    Client client_copy=clientCopy(ido);
    ASSERT_TEST(client_copy==NULL);
    client_copy=clientCopy(ido);
    ASSERT_TEST(client_copy==NULL);
    ASSERT_TEST(clientSetFaculty(ido,ELECTRICAL_ENGINEERING)==CLIENT_SUCCESS);
    client_copy=clientCopy(ido);
    ASSERT_TEST(client_copy==NULL);
    clientDestroy(ido);
    ido=buildclientForTests();
    client_copy=clientCopy(ido);
    ASSERT_TEST(client_copy!=NULL);
    TechnionFaculty output_f;
    Skill output_l;
    ASSERT_TEST(clientGetFaculty(client_copy,&output_f)==CLIENT_SUCCESS);
    ASSERT_TEST(output_f==ELECTRICAL_ENGINEERING);
    ASSERT_TEST(clientGetLevel(ido,&output_l)==CLIENT_SUCCESS);
    ASSERT_TEST(output_l==GOOD_LEVEL);
    const Email output=clientGetEmailR(client_copy);
    ASSERT_TEST(strcmp(output,GOOD_EMAIL1)==EQUAL);
    clientDestroy(ido);
    clientDestroy(client_copy);
    return true;
}

static bool testclientDestroy() {
    clientDestroy(NULL);
    Client ido=clientCreate();
    clientDestroy(ido);
    ido=buildclientForTests();
    clientDestroy(ido);
    return true;
}

static bool testclientCompare(){
    Client ido=buildclientForTests();
    Client shlomi=buildclientForTests();
    ASSERT_TEST(clientSetEmail(shlomi,GOOD_EMAIL2)==CLIENT_SUCCESS);
    ASSERT_TEST(clientCompare(ido,shlomi)<EQUAL);
    ASSERT_TEST(clientCompare(shlomi,ido)>EQUAL);
    ASSERT_TEST(clientSetEmail(shlomi,GOOD_EMAIL1)==CLIENT_SUCCESS);
    ASSERT_TEST(clientCompare(ido,shlomi)==EQUAL);
    clientDestroy(ido);
    clientDestroy(shlomi);
    return true;
}

/*******testing behaviour of client in set*********/
static bool testclientInSet(){
    Client ido=buildclientForTests();
    Client shlomi=buildclientForTests();
    Set two= setCreate(clientCopy, clientDestroy, clientCompare);
    ASSERT_TEST(two!=NULL);
    ASSERT_TEST(clientSetEmail(shlomi,GOOD_EMAIL2)==CLIENT_SUCCESS);
    ASSERT_TEST(clientSetFaculty(ido,COMPUTER_SCIENCE)==CLIENT_SUCCESS);
    ASSERT_TEST(setAdd(two,ido)==SET_SUCCESS);
    ASSERT_TEST(setAdd(two,shlomi)==SET_SUCCESS);
    ASSERT_TEST(setAdd(two,shlomi)==SET_ITEM_ALREADY_EXISTS);
    clientDestroy(ido);//make sure client inserted by copy to set
    clientDestroy(shlomi);
    Client new_ido=buildclientForTests();
    ASSERT_TEST(setIsIn(two,new_ido)==true);
    SET_FOREACH(Client,iterator,two){
        const Email find_email=clientGetEmailR(iterator);
        ASSERT_TEST(strcmp(GOOD_EMAIL1,find_email)==EQUAL||strcmp
                (GOOD_EMAIL2,find_email)==EQUAL);
    }
    ASSERT_TEST(setRemove(two,new_ido)==SET_SUCCESS);
    Client iterator=(Client)setGetFirst(two);
    const Email find_email=clientGetEmailR(iterator);
    ASSERT_TEST(strcmp(GOOD_EMAIL2,find_email)==EQUAL);
    clientDestroy(new_ido);
    setDestroy(two);
    return true;
}

int main(int argv, char **arc) {
    RUN_TEST(testclientCreate);
    RUN_TEST(testclientSetEmail);
    RUN_TEST(testclientSetFaculty);
    RUN_TEST(testclientGetEmailR);
    RUN_TEST(testclientGetFaculty);
    RUN_TEST(testclientSetLevel);
    RUN_TEST(testclientGetLevel);
    RUN_TEST(testclientCopy);
    RUN_TEST(testclientDestroy);
    RUN_TEST(testclientCompare);
    RUN_TEST(testclientInSet);
    return 0;
}