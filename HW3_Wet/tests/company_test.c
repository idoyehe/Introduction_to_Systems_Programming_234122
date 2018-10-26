#include "test_utilities.h"
#include "../set.h"
#include "../company.h"
#include <string.h>

#define GOOD_EMAIL1 "facebook@"
#define GOOD_EMAIL2 "mellanox@"
#define BAD_EMAIL1 "@@"
#define BAD_EMAIL2 "bad!!"
#define EQUAL 0

static bool testCompanyCreate() {
    Company company1=companyCreate();
    ASSERT_TEST(company1!= NULL);
    companyDestroy(company1);
    return true;
}


static Company buildCompanyFortTests(){
//create new company object with GOOD_EMAIL1 and faculty for tests
    Company company_Test=companyCreate();
    ASSERT_TEST(company_Test!=NULL);
    ASSERT_TEST(companySetEmail(company_Test,GOOD_EMAIL1)==COMPANY_SUCCESS);
    ASSERT_TEST(companySetFaculty(company_Test,BIOLOGY)==COMPANY_SUCCESS);
    return company_Test;
}

static bool testCompanyGetEmailByRef(){
    Company company_Test=buildCompanyFortTests();
    ASSERT_TEST(company_Test!= NULL);
    const  Email output=companyGetEmailR(company_Test);
    ASSERT_TEST(strcmp(output,GOOD_EMAIL1)==EQUAL);
    companyDestroy(company_Test);
    return true;
}

static bool testCompanySetEmail(){
    Company company_Test= buildCompanyFortTests();
    ASSERT_TEST(company_Test!= NULL);
    ASSERT_TEST(companySetEmail(company_Test,NULL)==COMPANY_NULL_PARAMETER);
    ASSERT_TEST(companySetEmail(company_Test,BAD_EMAIL1)==COMPANY_ILLEGAL_PARAMETERS);
    ASSERT_TEST(companySetEmail(company_Test,BAD_EMAIL2)==COMPANY_ILLEGAL_PARAMETERS);
    const  Email output1=companyGetEmailR(company_Test);
    ASSERT_TEST(strcmp(output1,GOOD_EMAIL1)==EQUAL);
    ASSERT_TEST(companySetEmail(company_Test,"google@")==COMPANY_SUCCESS);
    const Email output2=companyGetEmailR(company_Test);
    ASSERT_TEST(strcmp(output2,"google@")==EQUAL);
    ASSERT_TEST(companySetEmail(company_Test,GOOD_EMAIL2)==COMPANY_SUCCESS);
    const  Email output3=companyGetEmailR(company_Test);
    ASSERT_TEST(strcmp(output3,GOOD_EMAIL2)==EQUAL);
    companyDestroy(company_Test);
    return true;
}

static bool testCompanySetFaculty() {
    Company company_Test=buildCompanyFortTests();
    ASSERT_TEST(company_Test!= NULL);
    TechnionFaculty output=UNKNOWN;
    ASSERT_TEST(companySetFaculty(company_Test,UNKNOWN)==COMPANY_ILLEGAL_PARAMETERS);
    ASSERT_TEST(companySetFaculty(company_Test,-1)==COMPANY_ILLEGAL_PARAMETERS);
    ASSERT_TEST(companyGetFaculty(company_Test,&output)==COMPANY_SUCCESS);
    ASSERT_TEST(companySetFaculty(company_Test,CHEMISTRY) ==COMPANY_SUCCESS);
    ASSERT_TEST(companyGetFaculty(company_Test,&output)==COMPANY_SUCCESS);
    ASSERT_TEST(output==CHEMISTRY);
    companyDestroy(company_Test);
    return true;
}

static bool testCompanyGetFaculty() {
    Company company_Test=companyCreate();
    ASSERT_TEST(company_Test!= NULL);
    TechnionFaculty output;
    ASSERT_TEST(companyGetFaculty(company_Test,NULL)==COMPANY_NULL_PARAMETER);
    ASSERT_TEST(companyGetFaculty(company_Test,&output)==COMPANY_ILLEGAL_PARAMETERS);
    ASSERT_TEST(companySetFaculty(company_Test,ELECTRICAL_ENGINEERING) ==COMPANY_SUCCESS);
    ASSERT_TEST(companyGetFaculty(company_Test,&output)==COMPANY_SUCCESS);
    ASSERT_TEST(output==ELECTRICAL_ENGINEERING);
    ASSERT_TEST(companySetFaculty(company_Test,COMPUTER_SCIENCE)==COMPANY_SUCCESS);
    ASSERT_TEST(companyGetFaculty(company_Test,&output)==COMPANY_SUCCESS);
    ASSERT_TEST(output==COMPUTER_SCIENCE);
    companyDestroy(company_Test);
    return true;
}

static bool testCompanyCopy() {
    Company company1=companyCreate();
    ASSERT_TEST(company1!=NULL);
    Company company_copy= companyCopy(company1);
    ASSERT_TEST(company_copy==NULL);
    companyDestroy(company1);
    company1=buildCompanyFortTests();
    company_copy= companyCopy(company1);
    ASSERT_TEST(company_copy!=NULL);
    TechnionFaculty output;
    ASSERT_TEST(companyGetFaculty(company_copy,&output)==COMPANY_SUCCESS);
    ASSERT_TEST(output==BIOLOGY);
    const  Email output1=companyGetEmailR(company1);
    ASSERT_TEST(strcmp(output1,GOOD_EMAIL1)==EQUAL);
    companyDestroy(company1);
    companyDestroy(company_copy);
    return true;
}

static bool testCompanyDestroy() {
    companyDestroy(NULL);
    Company company1=companyCreate();
    companyDestroy(company1);
    company1=companyCreate();
    ASSERT_TEST(companySetEmail(company1,"ido@gmail.com")==COMPANY_SUCCESS);
    ASSERT_TEST(companySetFaculty(company1,ELECTRICAL_ENGINEERING)==COMPANY_SUCCESS);
    companyDestroy(company1);
    return true;
}

static bool testCompanyCompare(){
    Company facebook=buildCompanyFortTests();
    Company mellanox=buildCompanyFortTests();
    ASSERT_TEST(companySetEmail(mellanox,GOOD_EMAIL2) ==COMPANY_SUCCESS);
    ASSERT_TEST(companyCompare(facebook,mellanox)<EQUAL);
    ASSERT_TEST(companyCompare(mellanox,facebook)>EQUAL);
    ASSERT_TEST(companySetEmail(mellanox,GOOD_EMAIL1)==COMPANY_SUCCESS);
    ASSERT_TEST(companyCompare(facebook,mellanox)==EQUAL);
    companyDestroy(facebook);
    companyDestroy(mellanox);
    return true;
}


/********test behavior of company in set************/

static bool testCompanyInSet(){
    Company facebook=buildCompanyFortTests();
    ASSERT_TEST(companySetFaculty(facebook,COMPUTER_SCIENCE)==COMPANY_SUCCESS);
    Company mellanox=buildCompanyFortTests();
    ASSERT_TEST(companySetEmail(mellanox,GOOD_EMAIL2)==COMPANY_SUCCESS);
    Set two= setCreate(companyCopy, companyDestroy, companyCompare);
    ASSERT_TEST(two!=NULL);
    ASSERT_TEST(setAdd(two,facebook)==SET_SUCCESS);
    ASSERT_TEST(setAdd(two,mellanox)==SET_SUCCESS);
    companyDestroy(facebook);//make sure that copy of company inserted to set
    companyDestroy(mellanox);
    Company new_facebook=buildCompanyFortTests();
    ASSERT_TEST(setIsIn(two,new_facebook)==true);
    SET_FOREACH(Company,iterator,two){
        const Email find_email=companyGetEmailR(iterator);
        ASSERT_TEST(strcmp(GOOD_EMAIL1,find_email)==EQUAL||strcmp(GOOD_EMAIL2, find_email)==EQUAL);
    }
    ASSERT_TEST(setRemove(two,new_facebook)==SET_SUCCESS);
    companyDestroy(new_facebook);
    Company finder=(Company)setGetFirst(two);
    const Email find_email=companyGetEmailR(finder);;
    ASSERT_TEST(strcmp(GOOD_EMAIL2,find_email)==EQUAL);
    setDestroy(two);
    return true;
}

int main(int argv, char **arc) {
    RUN_TEST(testCompanyCreate);
    RUN_TEST(testCompanyGetEmailByRef);
    RUN_TEST(testCompanySetEmail);
    RUN_TEST(testCompanySetFaculty);
    RUN_TEST(testCompanyGetFaculty);
    RUN_TEST(testCompanyCopy);
    RUN_TEST(testCompanyDestroy);
    RUN_TEST(testCompanyCompare);
    RUN_TEST(testCompanyInSet);
    return 0;
}