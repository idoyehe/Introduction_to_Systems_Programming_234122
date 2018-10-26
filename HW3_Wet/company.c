#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "company.h"

#define FIRST 0
#define POSITIVE 1
#define STRLEN(e) strlen((e))+1


struct company_t{
    char* email;
    TechnionFaculty faculty_id;
};

/**
* check if given faculty id is valid
*
* @param
* id to check
* @return
* TRUE if given Id is in [0,UNKNOWN)
* else FALSE
*/
static inline bool validFacultyId(TechnionFaculty id){
    return (id>=FIRST)&&(id<UNKNOWN);
}

/**
* check if given Email is valid
*
* @param
* Email to check
* @return
* TRUE if given Email contains only 1 '@'
* else FALSE
*/
static inline bool validEmail(const Email email) {
    if(email==NULL) return false;
    char *c_ptr = email;
    int at_counter = 0;
    while (*c_ptr) {
        at_counter += *c_ptr == '@';
        c_ptr++;
    }
    return (at_counter == 1);
}


Company companyCreate(){
    Company new_company=(Company)malloc(sizeof(*new_company));
    if (!new_company){
        return NULL;
    }
    new_company->email=NULL;
    new_company->faculty_id=UNKNOWN;
    return new_company;
}

CompanyResult companySetEmail(Company company,const Email email){
    assert(company!=NULL);
    if (!email) return COMPANY_NULL_PARAMETER;

    if(!validEmail(email)) return COMPANY_ILLEGAL_PARAMETERS;

    Email new_email=(Email)malloc(STRLEN(email));
    if (!new_email){
        return COMPANY_MEMORY_PROBLEM;
    }
    free(company->email);
    company->email=strcpy(new_email,email);
    return COMPANY_SUCCESS;
}

CompanyResult companySetFaculty(Company company, TechnionFaculty id){
    assert(company!=NULL);
    if(!validFacultyId(id)){
        return COMPANY_ILLEGAL_PARAMETERS;
    }
    company->faculty_id=id;
    return COMPANY_SUCCESS;
}

const Email companyGetEmailR(Company company){
    assert(company!=NULL);
    return  company->email;
}

CompanyResult companyGetFaculty(Company company, TechnionFaculty *output_id){
    assert(company!=NULL);
    if(!output_id){
        return COMPANY_NULL_PARAMETER;
    }

    if(!validFacultyId(company->faculty_id)){
        return COMPANY_ILLEGAL_PARAMETERS;
    }
    *output_id=company->faculty_id;
    return COMPANY_SUCCESS;
}

void companyDestroy(SetElement company_element){
    if(!company_element){
        return;
    }
    Company company=(Company)company_element;
    free(company->email);
    free(company);
}

SetElement companyCopy(SetElement company_element){
    assert(company_element!=NULL);
    Company company=(Company)company_element;
    if(!validEmail(companyGetEmailR(company))||
            !validFacultyId(company->faculty_id)){
        return NULL;//preventing copy illegal company
    }
    Company copy=companyCreate();
    if (!copy){
        return NULL;
    }
    if(companySetEmail(copy,company->email)!=COMPANY_SUCCESS){
        companyDestroy(copy);
        return NULL;
    }
    if (companySetFaculty(copy, company->faculty_id)!=COMPANY_SUCCESS){
        companyDestroy(copy);
        return NULL;
    }
    return copy;
}

int companyCompare(SetElement company_element1, SetElement company_element2){
    assert(company_element1!=NULL);
    assert(company_element2!=NULL);
    Company company1=(Company)company_element1;
    Company company2=(Company)company_element2;
    assert(company1->email!=NULL);
    assert(company2->email!=NULL);
    return strcmp(company1->email,company2->email);
}